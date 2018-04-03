
#include "Robot.h"
#include "Astar.h"

Robot::Robot() : position_(Point3(0, 0, 0)), radius_(0.5), pathIndex_(0) {

}

Robot::Robot(Point3 position, Point3 target, float radius, int id) {
    position_ = position;
    radius_ = radius;
    target_ = target;
    pathIndex_ = 0;
    id_ = id;
}

Robot::~Robot() {

}

Point3 Robot::GetPosition() {
    return position_;
}

Point3 Robot::GetTarget() {
    return target_;
}

void Robot::SetPath(std::vector<Node> path) {
    path_ = path;
    targetNode_ = path_[0];
    furthestNode_ = path_[1];
}

void Robot::SetObstacles(std::vector<Obstacle> obstacles) {
    obstacleList_ = obstacles;
}

void Robot::UpdatePosition(float dt) {
    // move towards furthest node in path that you can reach
    // tracking that node with targetNode_

    if (!finishedPathing) {
        targetNode_ = NextNode();
    }

    Vector3 dir = (targetNode_.GetLocation() - position_).ToUnit();
    velocity_ = velocity_ + totalForce_ * dt;
    position_ = Point3(position_.x() + velocity_.x() * dt, 
                       position_.y() + velocity_.y() * dt,
                       position_.z() + velocity_.z() * dt);

    float distance = (position_ - targetNode_.GetLocation()).Length();
    if (distance < 0.01) {
        position_ = targetNode_.GetLocation();
    }
}

void Robot::ComputeForces(std::vector<Robot>* robotList) {
    totalForce_ = Vector3(0, 0, 0);
    for (Robot r : *robotList) {
        if (r.GetPosition() == position_) {
            continue;
        }
        Vector3 avoidForce_ = AvoidForce(r.GetPosition(), r.GetVelocity(), r.GetRadius());
        Vector3 goalVelocity_ = ((targetNode_.GetLocation() - position_).ToUnit()) * speed_;
        Vector3 goalForce_ = 2 * (goalVelocity_ - velocity_);
        totalForce_ = totalForce_ + avoidForce_ + goalForce_;
    }

    for (Obstacle o : obstacleList_) {
        Vector3 avoidForce_ = AvoidForce(o.GetPosition(), Vector3(0, 0, 0), o.GetRadius());
        Vector3 goalVelocity_ = ((targetNode_.GetLocation() - position_).ToUnit()) * speed_;
        Vector3 goalForce_ = 2 * (goalVelocity_ - velocity_);
        totalForce_ = totalForce_ + avoidForce_ + goalForce_;
    }

}

Vector3 Robot::AvoidForce(Point3 rPos, Vector3 rVel, float rRad) {
    float tau = TimeToCollision(rPos, rVel, rRad);
    if (tau > timeHorizon_) {
        return Vector3(0, 0, 0);
    }
    Vector3 dir =
        Vector3((position_[0] + velocity_[0] * tau) - (rPos[0] + rVel[0] * tau),
                (position_[1] + velocity_[1] * tau) - (rPos[1] + rVel[1] * tau),
                (position_[2] + velocity_[2] * tau) - (rPos[2] + rVel[2] * tau));

    Vector3 fAvoid = (timeHorizon_ - tau) / (tau + 0.001) * dir.ToUnit();
    return fAvoid;
}

float Robot::TimeToCollision(Point3 rPos, Vector3 rVel, float r) {
    float rad = radius_ + r;
    Vector3 positionDif = Vector3(rPos[0] - position_[0], rPos[1] - position_[1], rPos[2] - position_[2]);
    float c = positionDif.Dot(positionDif) - pow(rad, 2);
    if (c < 0) {
        return 0;
    }
    Vector3 v = velocity_ - rVel;
    float a = v.Dot(v);
    float b = positionDif.Dot(v);
    float discr = b * b - a * c;
    if (discr <= 0) {
        return timeHorizon_ + 1;
    }
    float tau = (b - sqrt(discr)) / a;
    if (tau < 0 || std::isnan(tau)) {
        return timeHorizon_ + 1;
    }
    return tau;
}

Vector3 Robot::GetSize() {
    return Vector3(radius_, radius_, radius_);
}

float Robot::GetRadius() {
    return radius_;
}

std::vector<Node> Robot::GetPath() {
    return path_;
}

Vector3 Robot::GetVelocity() const {
    return velocity_;
}

bool Robot::CanTravelTo(Node target) {
    for (Obstacle o : obstacleList_) {
        Vector3 nodeVec = target.GetLocation() - position_;
        Vector3 nodeCirc = o.GetPosition() - position_;

        float scalConV = nodeCirc.Dot(nodeVec.ToUnit());

        if (scalConV > 0 && nodeCirc.Length() < nodeVec.Length() + o.GetRadius() + radius_) {

            Vector3 ConV = scalConV * nodeVec.ToUnit();

            Vector3 distFromCircCenter = nodeCirc - ConV;

            float distance = distFromCircCenter.Length();

            if (distance < o.GetRadius() + radius_) {
                return false;
            }
        }
    }
    return true;
}

Node Robot::NextNode() {
    if (furthestNode_.GetLocation() == path_.back().GetLocation() && CanTravelTo(furthestNode_)) {
        targetNode_ = furthestNode_;
        finishedPathing = true;
        return targetNode_;
    }

    if (targetNode_.GetLocation() != path_.back().GetLocation() && CanTravelTo(furthestNode_)) {
        targetNode_ = furthestNode_;
        pathIndex_++;
        furthestNode_ = path_[pathIndex_];
         return NextNode();
    }
    return targetNode_;
}

void Robot::SetAstar(Astar* astar) {
    astar_ = astar;
    path_ = astar_->CalculatePath(radius_, id_);
    targetNode_ = path_[0];
    furthestNode_ = path_[1];
}

#include "Robot.h"
#include "Astar.h"

Robot::Robot() : position_(Point3(0, 0, 0)), radius_(0.5), pathIndex_(0) {

}

Robot::Robot(Point3 position, Point3 target, float radius, int id) {
    position_ = position;
    radius_ = radius;
    target_ = target;
    pathIndex_ = 0;
    finishedPathing = false;
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

    position_ = Point3(position_.x() + dir.x() * speed_ * dt, 
                       position_.y() + dir.y() * speed_ * dt,
                       position_.z() + dir.z() * speed_ * dt);

    float distance = (position_ - targetNode_.GetLocation()).Length();
    if (distance < 0.01) {
        position_ = targetNode_.GetLocation();
    }
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

bool Robot::CanTravelTo(Node target) {
    for (Obstacle o : obstacleList_) {
        Vector3 nodeVec = target.GetLocation() - position_;
        Vector3 nodeCirc = o.GetPosition() - position_;

        float scalConV = nodeCirc.Dot(nodeVec.ToUnit());
        Vector3 ConV = scalConV * nodeVec.ToUnit();

        Vector3 distFromCircCenter = nodeCirc - ConV;

        float distance = distFromCircCenter.Length();

        if (distance < o.GetRadius() + radius_) {
            return false;
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
        NextNode();
    }
    return targetNode_;
}

void Robot::SetAstar(Astar* astar) {
    astar_ = astar;
    path_ = astar_->CalculatePath(radius_, id_);
    targetNode_ = path_[0];
    furthestNode_ = path_[1];
}
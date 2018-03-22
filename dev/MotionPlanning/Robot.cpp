
#include "Robot.h"

Robot::Robot() : position_(Point3(0, 0, 0)), size_(Vector3(0.5, 0.5, 0.5)),
           radius_(0.5) {

}

Robot::~Robot() {

}

Point3 Robot::GetPosition() {
    return position_;
}

void Robot::SetPath(std::vector<Node> path) {
    path_ = path;
    targetNode_ = &path_[0];
    furthestNode_ = &path_[0];
}

void Robot::SetObstacles(std::vector<Obstacle> obstacles) {
    obstacleList_ = obstacles;
}

void Robot::UpdatePosition(double dt) {
    // move towards furthest node in path that you can reach
    // tracking that node with targetNode_
    if (targetNode_->GetLocation() != path_.back().GetLocation()) {
        *targetNode_ = NextNode();
    }

    Vector3 dir = (targetNode_->GetLocation() - position_).ToUnit();

    position_ = Point3(position_.x() + dir.x() * velocity_ * dt, 
                       position_.y() + dir.y() * velocity_ * dt, 
                       position_.z() + dir.z() * velocity_ * dt);

    double distance = (position_ - targetNode_->GetLocation()).Length();
    if (distance < 0.01) {
        position_ = targetNode_->GetLocation();
    }
}

Vector3 Robot::GetSize() {
    return size_;
}

double Robot::GetRadius() {
    return radius_;
}

bool Robot::CanTravelTo(Node target) {
    for (Obstacle o : obstacleList_) {
        Vector3 nodeVec = position_ - target.GetLocation();
        Vector3 nodeCirc = position_ - o.GetPosition();

        double scalConV = nodeCirc.Dot(nodeVec.ToUnit());
        Vector3 ConV = scalConV * nodeVec.ToUnit();

        Vector3 distFromCircCenter = nodeCirc - ConV;

        double distance = distFromCircCenter.Length();

        if (distance < o.GetRadius() + radius_) {
            return false;
        }
    }
    return true;
}

Node Robot::NextNode() {
    if (targetNode_->GetLocation() != path_.back().GetLocation() && CanTravelTo(*furthestNode_)) {
        *targetNode_ = *furthestNode_;
        furthestNode_++;
        NextNode();
    }
    return *targetNode_;
}
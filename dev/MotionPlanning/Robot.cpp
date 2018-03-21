
#include "Robot.h"

Robot::Robot() : position_(Point3(0, 0, 0)), targetNode_(NULL) {

}

Robot::~Robot() {
    delete prm_;
    delete targetNode_;
}

Point3 Robot::GetPosition() {
    return position_;
}

void Robot::SetPath(std::vector<Node> path) {
    path_ = path;
}

void Robot::SetObstacles(std::vector<Obstacle> obstacles) {
    obstacleList_ = obstacles;
}

void Robot::UpdatePosition(double dt) {

}
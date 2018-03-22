
#include "Obstacle.h"

Obstacle::Obstacle() : radius_(2), position_(Point3(5, 5, 0)) {

}

Obstacle::Obstacle(double radius, Point3 position) {
    radius_ = radius;
    position_ = position;
}

void Obstacle::Position(Point3 position) {
    position_ = position;
}

Point3 Obstacle::GetPosition() {
    return position_;
}

void Obstacle::Radius(double radius) {
    radius_ = radius;
}

double Obstacle::GetRadius() {
    return radius_;
}
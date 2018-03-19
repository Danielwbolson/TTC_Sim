
#include "Robot.h"

Robot::Robot() {
    position_ = Point2(0, 0);
}

Point2 Robot::GetPosition() {
    return position_;
}
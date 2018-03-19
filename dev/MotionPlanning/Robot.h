
#ifndef ROBOT_H_
#define ROBOT_H_

#include <mingfx.h>

class Robot {
public:
    Robot();

    Point2 GetPosition();

private:
    Point2 position_;

};

#endif // ROBOT_H_

#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "mingfx.h"

class Obstacle {
public:
    Obstacle();
    Obstacle(double radius, Point3 position);

    void Radius(double radius);
    double GetRadius();

    void Position(Point3 position);
    Point3 GetPosition();

    //std::vector<Obstacle> MakeObstacles();

private:
    double radius_;
    Point3 position_;
};

#endif // OBSTACLE_H_
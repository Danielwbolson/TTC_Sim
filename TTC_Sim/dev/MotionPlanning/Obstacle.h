
#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "mingfx.h"

class Obstacle {
public:
    Obstacle();
    Obstacle(float radius, Point3 position);

    void Radius(float radius);
    float GetRadius();

    void Position(Point3 position);
    Point3 GetPosition();

    //std::vector<Obstacle> MakeObstacles();

private:
    float radius_;
    Point3 position_;
};

#endif // OBSTACLE_H_
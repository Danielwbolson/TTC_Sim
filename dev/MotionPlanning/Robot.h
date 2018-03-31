
#ifndef ROBOT_H_
#define ROBOT_H_

#include <mingfx.h>

#include "Node.h"
#include "Obstacle.h"

class Robot {
public:
    Robot();
    Robot(Point3 position, Point3 target, double radius);
    ~Robot();

    Point3 GetPosition();
    Point3 GetTarget();

    void SetPath(std::vector<Node>);

    void SetObstacles(std::vector<Obstacle>);

    void UpdatePosition(double dt);

    Vector3 GetSize();
    double GetRadius();
    std::vector<Node> Robot::GetPath();

    bool CanTravelTo(Node target);

    Node NextNode();

private:
    Point3 position_;
    Point3 target_;
    double radius_;

    std::vector<Node> path_;
    std::vector<Obstacle> obstacleList_;

    Node* targetNode_;
    Node* furthestNode_;

    double velocity_ = 1;
};

#endif // ROBOT_H_
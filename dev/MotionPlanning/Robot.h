
#ifndef ROBOT_H_
#define ROBOT_H_

#include <mingfx.h>
#include <future>

#include "Node.h"
#include "Obstacle.h"

class PRM;
class Astar;

class Robot {
public:
    Robot();
    Robot(Point3 position, Point3 target, float radius, int id);
    ~Robot();

    Point3 GetPosition();
    Point3 GetTarget();

    void SetPath(std::vector<Node>);

    void SetObstacles(std::vector<Obstacle>);

    void UpdatePosition(float dt);

    Vector3 GetSize();
    float GetRadius();
    std::vector<Node> Robot::GetPath();

    bool CanTravelTo(Node target);

    Node NextNode();

    void SetAstar(Astar* astar);

private:
    Point3 position_;
    Point3 target_;
    float radius_;
    int pathIndex_;
    bool finishedPathing;

    int id_;

    Astar* astar_;

    std::vector<Node>* nodeList_;
    std::vector<Node> path_;
    std::vector<Obstacle> obstacleList_;

    Node targetNode_;
    Node furthestNode_;

    float speed_ = 1;
};

#endif // ROBOT_H_
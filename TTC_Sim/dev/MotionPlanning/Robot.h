
#ifndef ROBOT_H_
#define ROBOT_H_

#include <mingfx.h>
#include <future>
#include <time.h>
#include <random>

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
    void ComputeForces(std::vector<Robot>* robotList);
    float TimeToCollision(Point3, Vector3, float);
    Vector3 AvoidForce(Point3 rPos, Vector3 rVel, float rRad);


    Vector3 GetSize();
    float GetRadius();
    std::vector<Node> Robot::GetPath();
    Vector3 GetVelocity() const;

    bool CanTravelTo(Node target);

    Node NextNode();

    void SetAstar(Astar* astar);

    float RandomNum();

private:
    Point3 position_;
    Vector3 goalVelocity_;
    Vector3 velocity_ = Vector3(0, 0, 0);
    float speed_ = 1;

    Point3 target_;
    float radius_;
    int pathIndex_;
    bool finishedPathing = false;

    float timeHorizon_ = 5;

    Vector3 totalForce_;
    Vector3 goalForce_;
    Vector3 avoidForce_;

    int id_;

    Astar* astar_;

    std::vector<Node>* nodeList_;
    std::vector<Node> path_;
    std::vector<Obstacle> obstacleList_;

    Node targetNode_;
    Node furthestNode_;
};

#endif // ROBOT_H_

#ifndef PRM_H_
#define PRM_H_

#include "Obstacle.h"
#include "Node.h"
#include "Robot.h"

#include <cmath>
#include <time.h>
#include <utility>
#include <random>

class PRM {
public:
    PRM(std::vector<Robot> &robotList, std::vector<Obstacle> obstacles);
    ~PRM();

    double DistanceBetween(Point3 a, Point3 b);

    bool WithinObstacle(Point3 x);

    bool CanConnect(Node x, Node y);

    std::vector<Node> const & GetNodeList() const;

private:
    bool WithinDistance(Node x, Node y);

    bool NoObstacleInbetween(Node x, Node y);

    int const SCENE_X_SIZE_ = 10;
    int const SCENE_Y_SIZE_ = 10;
    int const PRM_SIZE_ = 200;
    int const DISTANCE_ = 4;

    Point3 start_;
    Point3 target_;
    std::vector<Obstacle> obstacles_;
    std::vector<Node> nodeList_;
};

#endif // PRM_H_
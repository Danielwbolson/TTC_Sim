
#ifndef PRM_H_
#define PRM_H_

#include "Graph.h"
#include "Obstacle.h"
#include "Node.h"
#include "Edge.h"
#include <cmath>

class PRM {
public:
    PRM(Point2 start, Point2 target, std::vector<Obstacle> obstacles);
    ~PRM();

    double DistanceBetween(Node x, Node y);

    bool WithinObstacle(Point2 x);

    bool CanConnect(Node x, Node y);

    std::vector<Node> GetNodeList();

    std::vector<Edge> GetEdgeList();

private:
    bool WithinDistance(Node x, Node y);

    bool NoObstacleInbetween(Node x, Node y);

    int const SCENE_X_SIZE_ = 10;
    int const SCENE_Y_SIZE_ = 10;
    double const PRM_SIZE_ = 100;
    double const DISTANCE_ = 0.5;

    Graph* graph_;
    Point2 start_;
    Point2 target_;
    std::vector<Obstacle> obstacles_;
    std::vector<Node> nodeList_;
    std::vector<Edge> edgeList_;
};

#endif // PRM_H_
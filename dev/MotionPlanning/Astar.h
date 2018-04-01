
#ifndef ASTAR_H_
#define ASTAR_H_

#include "Node.h"
#include "Robot.h"
#include "Obstacle.h"

#include <queue>
#include <limits>
#include <algorithm>

using std::vector;
using std::pair;

struct CompareNodesByDistance;

class Astar {
public:
    Astar() {}
    Astar(vector<Node> nodeList, vector<Robot> &robotList, vector<Obstacle> &obstacleList);

    bool ObstacleInbetween(double rad, Node curr, Node nbr);

    double CalculateHeuristic(int i, int j);
    double DistanceInbetween(int i, int j);

    ~Astar();

private:
    vector<Node> nodeList_;
    vector<Obstacle> obstacles_;
};

#endif // ASTAR_H_

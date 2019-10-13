
#ifndef ASTAR_H_
#define ASTAR_H_

#include "Node.h"
#include "Obstacle.h"

using std::vector;
using std::pair;
using namespace mingfx;

struct CompareNodesByDistance;

class Astar {
public:
    Astar(vector<Node>* nodeList, vector<Obstacle>* obstacleList);

    vector<Node> CalculatePath(float rad, int id);

    bool ObstacleInbetween(float rad, Node curr, Node nbr);

    float CalculateHeuristic(int i, int j);
    float DistanceInbetween(int i, int j);

    ~Astar();

private:
    vector<Node>* nodeList_;
    vector<Obstacle>* obstacles_;
};

#endif // ASTAR_H_

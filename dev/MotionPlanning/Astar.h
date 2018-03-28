
#ifndef ASTAR_H_
#define ASTAR_H_

#include "Node.h"
#include <queue>
#include <limits>
#include <algorithm>

using std::vector;
using std::pair;

struct CompareNodesByDistance;

class Astar {
public:
    Astar() {}
    Astar(vector<Node> nodeList);

    vector<Node> GetPath();

    double CalculateHeuristic(int i, int j);
    double DistanceInbetween(int i, int j);

    ~Astar();

private:
    vector<Node> path_;
    vector<Node> nodeList_;

    vector<double> gcost;
    vector<double> heur;
    vector<double> fcost;
};

#endif // ASTAR_H_

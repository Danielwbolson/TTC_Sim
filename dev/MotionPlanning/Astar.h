
#ifndef ASTAR_H_
#define ASTAR_H_

#include "Node.h"
#include <queue>
#include <limits>
#include <algorithm>

struct CompareNodesByDistance;

class Astar {
public:
    Astar() {}
    Astar(std::vector<Node> nodeList);

    std::vector<Node> GetPath();

    ~Astar();

private:
    std::vector<Node> path_;
    std::vector<Node> nodeList_;
};

#endif // ASTAR_H_

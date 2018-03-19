
#ifndef EDGE_H_
#define EDGE_H_

#include "Node.h"

class Edge {
public:
    Edge() {}
    Edge(double weight, Node startNode, Node targetNode);

    ~Edge();

    double GetWeight() const;
    void Weight(double weight);

private:
    double weight_;
    Node* startNode_;
    Node* targetNode_;
};

#endif // EDGE_H_

#include "Edge.h"

Edge::Edge(double weight, Node startNode, Node targetNode) {
    weight_ = weight;
    *startNode_ = startNode;
    *targetNode_ = targetNode;
}

Edge::~Edge() {
    delete startNode_;
    delete targetNode_;
}

double Edge::GetWeight() const { 
    return weight_; 
}

void Edge::Weight(double weight) { 
    weight_ = weight; 
}

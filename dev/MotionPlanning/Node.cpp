
#include "Node.h"

Node::Node(Point2 location, std::vector<Node> neighborList) {
    location_ = location;
    neighborList_ = neighborList;
}

Point2 Node::GetLocation() const {
    return location_;
}

void Node::Location(Point2 location) {
    location_ = location;
}

std::vector<Node> Node::GetNeighborList() const {
    return neighborList_;
}

void Node::NeighborList(std::vector<Node> neighborList) {
    neighborList_ = neighborList;
}

void Node::AddToNeighborList(Node x) {
    neighborList_.push_back(x);
}
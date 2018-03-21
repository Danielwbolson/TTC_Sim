
#include "Node.h"

Node::Node() {}

Node::Node(int id, Point3 location, std::vector<std::pair<Node, double>> neighborList) {
    id_ = id;
    location_ = location;
    neighborList_ = neighborList;
}

int Node::GetID() const {
    return id_;
}

Point3 Node::GetLocation() const {
    return location_;
}

void Node::Location(Point3 location) {
    location_ = location;
}

std::vector<std::pair<Node, double>> Node::GetNeighborList() const {
    return neighborList_;
}

void Node::NeighborList(std::vector<std::pair<Node, double>> neighborList) {
    neighborList_ = neighborList;
}

void Node::AddToNeighborList(std::pair<Node, double> n) {
    neighborList_.push_back(n);
}

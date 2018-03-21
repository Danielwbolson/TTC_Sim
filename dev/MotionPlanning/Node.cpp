
#include "Node.h"

Node::Node() : parent_(nullptr){}

Node::Node(int id, Point3 location, std::vector<std::pair<int, double>> neighborList) {
    id_ = id;
    location_ = location;
    neighborList_ = neighborList;
    parent_ = nullptr;
}

//Node::~Node() {
   // delete parent_;
  //  neighborList_.clear();
//}

int Node::GetID() const {
    return id_;
}

Point3 Node::GetLocation() const {
    return location_;
}

void Node::Location(Point3 location) {
    location_ = location;
}

std::vector<std::pair<int, double>> Node::GetNeighborList() const {
    return neighborList_;
}

void Node::NeighborList(std::vector<std::pair<int, double>> neighborList) {
    neighborList_ = neighborList;
}

void Node::AddToNeighborList(std::pair<int, double> n) {
    neighborList_.push_back(n);
}

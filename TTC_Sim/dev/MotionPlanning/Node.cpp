
#include "Node.h"

Node::Node() : parent_(NULL){}

Node::Node(int id, Point3 location, std::vector<std::pair<int, float>> neighborList) {
    id_ = id;
    location_ = location;
    neighborList_ = neighborList;
    parent_ = NULL;
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

std::vector<std::pair<int, float>> Node::GetNeighborList() const {
    return neighborList_;
}

void Node::NeighborList(std::vector<std::pair<int, float>> neighborList) {
    neighborList_ = neighborList;
}

void Node::AddToNeighborList(std::pair<int, float> n) {
    neighborList_.push_back(n);
}

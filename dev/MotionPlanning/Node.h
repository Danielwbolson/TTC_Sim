
#ifndef NODE_H_
#define NODE_H_

#include <mingfx.h>

#include <utility>

class Node {
public:
    Node();
    Node(int id, Point3 location, std::vector<std::pair<Node, double>> neighborList);

    int GetID() const;

    Point3 GetLocation() const;
    void Location(Point3 location);

    std::vector<std::pair<Node, double>> GetNeighborList() const;
    void NeighborList(std::vector<std::pair<Node, double>> neighborList);
    void AddToNeighborList(std::pair<Node, double>);

    Node* parent_;

private:
    int id_;
    Point3 location_;
    std::vector<std::pair<Node, double>> neighborList_;
};

#endif // NODE_H_
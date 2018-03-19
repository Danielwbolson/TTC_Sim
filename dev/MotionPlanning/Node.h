
#ifndef NODE_H_
#define NODE_H_

#include <mingfx.h>

class Node {
public:
    Node() {}
    Node(Point2 location, std::vector<Node> neighborList);

    Point2 GetLocation() const;
    void Location(Point2 location);

    std::vector<Node> GetNeighborList() const;
    void NeighborList(std::vector<Node> neighborList);
    void AddToNeighborList(Node x);

private:
    Point2 location_;
    std::vector<Node> neighborList_;
    
};

#endif // NODE_H_
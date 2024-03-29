
#ifndef NODE_H_
#define NODE_H_

#include <mingfx.h>

using namespace mingfx;

class Node {
public:

    typedef std::shared_ptr<Node> NodePtr;

    Node();
    Node(int id, Point3 location, std::vector<std::pair<int, float>> neighborList);
   // ~Node();

    int GetID() const;

    Point3 GetLocation() const;
    void Location(Point3 location);

    std::vector<std::pair<int, float>> GetNeighborList() const;
    void NeighborList(std::vector<std::pair<int, float>> neighborList);
    void AddToNeighborList(std::pair<int, float>);

    int parent_;

private:
    int id_;
    Point3 location_;
    std::vector<std::pair<int, float>> neighborList_;
};

#endif // NODE_H_
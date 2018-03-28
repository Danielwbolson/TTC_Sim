
#ifndef NODE_H_
#define NODE_H_

#include <mingfx.h>
#include <utility>
#include <memory>

class Node {
public:

    typedef std::shared_ptr<Node> NodePtr;

    Node();
    Node(int id, Point3 location, std::vector<std::pair<int, double>> neighborList);
   // ~Node();

    int GetID() const;

    Point3 GetLocation() const;
    void Location(Point3 location);

    std::vector<std::pair<int, double>> GetNeighborList() const;
    void NeighborList(std::vector<std::pair<int, double>> neighborList);
    void AddToNeighborList(std::pair<int, double>);

    int parent_;

private:
    int id_;
    Point3 location_;
    std::vector<std::pair<int, double>> neighborList_;
};

#endif // NODE_H_
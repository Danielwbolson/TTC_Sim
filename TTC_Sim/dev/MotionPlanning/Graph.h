
#ifndef GRAPH_H_
#define GRAPH_H_

#include "Node.h"
#include "Edge.h"

// In this class, we are going to create a Graph which will be
// utilized by our Probablistic Roadmap (PRM)

class Graph {
public:
    Graph() {}
    Graph(std::vector<Node> nodeList, std::vector<Edge> edgeList);

    ~Graph();
    
    std::vector<Node> GetNodeList() const;
    void NodeList(std::vector<Node> nodeList);

    std::vector<Edge> GetEdgeList() const;
    void EdgeList(std::vector<Edge> edgeList);



private:
    std::vector<Node> nodeList_;
    std::vector<Edge> edgeList_;

};

#endif // GRAPH_H
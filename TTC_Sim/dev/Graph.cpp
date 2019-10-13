
#include "Graph.h"

Graph::Graph(std::vector<Node> nodeList, std::vector<Edge> edgeList) {
    nodeList_ = nodeList;
    edgeList_ = edgeList;
}

Graph::~Graph() {
    nodeList_.clear();
    edgeList_.clear();
}

std::vector<Node> Graph::GetNodeList() const { 
    return nodeList_; 
}

void Graph::NodeList(std::vector<Node> nodeList) { 
    nodeList_ = nodeList; 
}

std::vector<Edge> Graph::GetEdgeList() const { 
    return edgeList_; 
}

void Graph::EdgeList(std::vector<Edge> edgeList) { 
    edgeList_ = edgeList; 
}

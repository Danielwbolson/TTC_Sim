
#include "Astar.h"

struct CompareNodesByDistance {
    bool operator()(const std::pair<Node, double>& a, const std::pair<Node, double>& b) const {
        return a.second < b.second;
    }
};

Astar::Astar(std::vector<Node> nodeList) {
    nodeList_ = nodeList;

    Node startNode = nodeList_[0];
    Node targetNode = nodeList_[1];

    std::priority_queue<std::pair<Node, double>, std::vector<std::pair<Node, double>>, CompareNodesByDistance> pq;

    std::vector<double> dist;
    for (int i = 0; i < nodeList_.size(); i++) {
        dist.push_back(std::numeric_limits<double>::max());
    }

    pq.push(std::make_pair(startNode, 0));
    dist[0] = 0;

    while (!pq.empty()) {

        // The nodes in U's adjacency list are not what they should be
        // empty and null when they should be holding data
        Node u = pq.top().first;
        pq.pop();

        std::vector<std::pair<Node, double>> adj_list = u.GetNeighborList();
        std::vector<int> completedNodes;

        for (int i = 0; i < u.GetNeighborList().size(); i++) {
            // Node u is our parent node
            // Node v is our adjacent node
            Node v = adj_list[i].first;
            double weight = adj_list[i].second;

            if (std::find(completedNodes.begin(), completedNodes.end(), v.GetID()) != completedNodes.end()) {
                continue;
            }

            if (dist[v.GetID()] > dist[u.GetID()] + weight) {
                dist[v.GetID()] = dist[u.GetID()] + weight;
                nodeList_[v.GetID()].parent_ = &u;
                completedNodes.push_back(v.GetID());
                pq.push(std::make_pair(nodeList_[v.GetID()], dist[v.GetID()]));
            }
        }
    }

    while (nodeList_[targetNode.GetID()].parent_ != NULL) {
        path_.push_back(nodeList_[targetNode.GetID()]);
        targetNode = *nodeList_[targetNode.GetID()].parent_;
    }
}

Astar::~Astar() {}

std::vector<Node> Astar::GetPath() {
    return path_;
}
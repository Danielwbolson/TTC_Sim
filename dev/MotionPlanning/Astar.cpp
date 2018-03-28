
#include "Astar.h"

struct CompareNodesByDistance {
    bool operator()(const pair<int, double>& a, const pair<int, double>& b) const {
        return a.second > b.second;
    }
};

Astar::Astar(vector<Node> nodeList) {
    nodeList_ = nodeList;

    // starting point
    int startNode = nodeList_[0].GetID();

    // target point
    int targetNode = nodeList_[1].GetID();

    // setting up our priority queue to sort by fcost
    std::priority_queue<pair<int, double>, vector<pair<int, double>>, CompareNodesByDistance> pq;

    // two sets which will contain completed and currently enqueued nodes
    vector<int> closedSet;
    vector<int> openSet;

    for (int i = 0; i < nodeList_.size(); i++) {
        gcost.push_back(std::numeric_limits<double>::max());
        heur.push_back(0);
        fcost.push_back(std::numeric_limits<double>::max());
    }

    // our first node has a graph cost of 0 and a heuristic cost
    // of its distance from the goal
    gcost[startNode] = 0;
    heur[startNode] = CalculateHeuristic(startNode, targetNode);
    fcost[startNode] = heur[startNode];

    // put our starting node into the enqueued nodes
    pq.push(std::make_pair(startNode, fcost[startNode]));
    openSet.push_back(startNode);

    while (!pq.empty()) {

       // curr is our node with the smallest fcost
        int curr = std::get<0>(pq.top());

        // if we have dequeued the targetnode, we are done
        if (curr == targetNode) {
            break;
        }

        // pop curr out of the priority queue, add it to our closed set and 
        // remember to get it out of our open set
        pq.pop();
        closedSet.push_back(curr);
        openSet.erase(std::remove(openSet.begin(), openSet.end(), curr), openSet.end());

        // get our current nodes adjacency list
        vector<pair<int, double>> adj_list = nodeList_[curr].GetNeighborList();

        for (int i = 0; i < adj_list.size(); i++) {

            // Node curr is our current dequeued node
            // Node nbr is our neighbor node
            int nbr = std::get<0>(adj_list[i]);

            // weight is the value of the edge between curr and nbr
            double weight = DistanceInbetween(nbr, curr);

            // if we have already completed this node
            if (std::find(closedSet.begin(), closedSet.end(), nbr) != closedSet.end()) {
                continue;
            }

            // Discover a new node
            if (std::find(openSet.begin(), openSet.end(), nbr) == openSet.end()) {
                openSet.push_back(nbr);
            }

            double tentative_gcost = gcost[curr] + weight;
            if (tentative_gcost >= gcost[nbr]) {
                continue; // this is not a better path
            }

            nodeList_[nbr].parent_ = curr;
            gcost[nbr] = tentative_gcost;
            heur[nbr] = CalculateHeuristic(nbr, targetNode);
            fcost[nbr] = gcost[nbr] + heur[nbr];
            pq.push(std::make_pair(nbr, fcost[nbr]));
        }
    }
    
    while (nodeList_[targetNode].parent_ != startNode) {
        path_.push_back(nodeList_[targetNode]);
        targetNode = nodeList_[targetNode].parent_;
    }

    path_.push_back(nodeList_[startNode]);
}

Astar::~Astar() {}

vector<Node> Astar::GetPath() {
    return path_;
}

double Astar::CalculateHeuristic(int i, int j) {
    Point3 uLoc = nodeList_[i].GetLocation();
    Point3 vLoc = nodeList_[j].GetLocation();
    return ((double)sqrt(pow(uLoc.x() - vLoc.x(), 2) + pow(uLoc.y() - vLoc.y(), 2) + pow(uLoc.z() - vLoc.z(), 2)));
}

double Astar::DistanceInbetween(int i, int j) {
    Point3 uLoc = nodeList_[i].GetLocation();
    Point3 vLoc = nodeList_[j].GetLocation();
    return ((double)sqrt(pow(uLoc.x() - vLoc.x(), 2) + pow(uLoc.y() - vLoc.y(), 2) + pow(uLoc.z() - vLoc.z(), 2)));
}
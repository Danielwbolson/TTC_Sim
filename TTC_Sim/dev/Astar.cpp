
#include "Astar.h"

#include <queue>
#include <limits>
#include <algorithm>

struct CompareNodesByDistance {
    bool operator()(const pair<int, float>& a, const pair<int, float>& b) const {
        return a.second > b.second;
    }
};

Astar::Astar(vector<Node>* nodeList, vector<Obstacle>* obstacleList) : 
    obstacles_(obstacleList), nodeList_(nodeList) {}

Astar::~Astar() {}

vector<Node> Astar::CalculatePath(float rad, int id) {
    vector<float> gcost;
    vector<float> heur;
    vector<float> fcost;

    vector<Node> path_;

    // starting point
    int startNode = id;

    // target point
    int targetNode = id + 1;

    // setting up our priority queue to sort by fcost
    std::priority_queue<pair<int, float>, vector<pair<int, float>>, CompareNodesByDistance> pq;

    // two sets which will contain completed and currently enqueued nodes
    vector<int> closedSet;
    vector<int> openSet;

    for (int i = 0; i < (*nodeList_).size(); i++) {
        gcost.push_back(std::numeric_limits<float>::max());
        heur.push_back(0);
        fcost.push_back(std::numeric_limits<float>::max());
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
        int curr = pq.top().first;

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
        vector<pair<int, float>> adj_list = (*nodeList_)[curr].GetNeighborList();

        for (int j = 0; j < adj_list.size(); j++) {

            // Node curr is our current dequeued node
            // Node nbr is our neighbor node
            int nbr = adj_list[j].first;

            // if the line inbetween nodes is too close to obstacles
            if (ObstacleInbetween(rad, (*nodeList_)[curr], (*nodeList_)[nbr])) {
                continue;
            }

            // if we have already completed this node
            if (std::find(closedSet.begin(), closedSet.end(), nbr) != closedSet.end()) {
                continue;
            }

            // Discover a new node
            if (std::find(openSet.begin(), openSet.end(), nbr) == openSet.end()) {
                openSet.push_back(nbr);
            }

            // weight is the value of the edge between curr and nbr
            float weight = DistanceInbetween(nbr, curr);

            float tentative_gcost = gcost[curr] + weight;
            if (tentative_gcost >= gcost[nbr]) {
                continue; // this is not a better path
            }

            (*nodeList_)[nbr].parent_ = curr;
            gcost[nbr] = tentative_gcost;
            heur[nbr] = CalculateHeuristic(nbr, targetNode);
            fcost[nbr] = gcost[nbr] + heur[nbr];
            pq.push(std::make_pair(nbr, fcost[nbr]));
        }
    }

    while (targetNode != startNode) {
        path_.push_back((*nodeList_)[targetNode]);
        targetNode = (*nodeList_)[targetNode].parent_;
    }

    path_.push_back((*nodeList_)[startNode]);

    // Reverse the path to get it starting from the robot's position
    std::reverse(path_.begin(), path_.end());
    return path_;
}

float Astar::CalculateHeuristic(int i, int j) {
    Point3 uLoc = (*nodeList_)[i].GetLocation();
    Point3 vLoc = (*nodeList_)[j].GetLocation();
    return (sqrt(pow(uLoc.x() - vLoc.x(), 2) + pow(uLoc.y() - vLoc.y(), 2) + pow(uLoc.z() - vLoc.z(), 2)));
}

float Astar::DistanceInbetween(int i, int j) {
    Point3 uLoc = (*nodeList_)[i].GetLocation();
    Point3 vLoc = (*nodeList_)[j].GetLocation();
    return (sqrt(pow(uLoc.x() - vLoc.x(), 2) + pow(uLoc.y() - vLoc.y(), 2) + pow(uLoc.z() - vLoc.z(), 2)));
}

bool Astar::ObstacleInbetween(float rad, Node curr, Node nbr) {
    for (Obstacle o : *obstacles_) {
        Vector3 nodeVec = nbr.GetLocation() - curr.GetLocation();
        Vector3 nodeCirc = o.GetPosition() - curr.GetLocation();

        float scalConV = nodeCirc.Dot(nodeVec.ToUnit());

        if (scalConV > 0 && nodeCirc.Length() < nodeVec.Length() + o.GetRadius() + rad) {
            Vector3 ConV = scalConV * nodeVec.ToUnit();
            Vector3 distFromCircCenter = nodeCirc - ConV;
            float distance = distFromCircCenter.Length();

            if (distance < o.GetRadius() + rad) {
                return true;
            }
        }
    }
    return false;
}
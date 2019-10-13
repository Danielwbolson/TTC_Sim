
#include "PRM.h"

#include <cmath>
#include <time.h>
#include <utility>
#include <random>

PRM::PRM(std::vector<Robot> &robotList, std::vector<Obstacle> obstacles) {
    obstacles_ = obstacles;
    srand(time(NULL));

    for (int i = 0; i < robotList.size(); i++) {
        Robot &robot = robotList[i];
        // Initialize first item as start with an empty neighbor list
        nodeList_.push_back(Node(2*i, robot.GetPosition(), std::vector<std::pair<int, float>>()));

        // Initialize second item as target with an empty neighbor list
        nodeList_.push_back(Node(2*i+1, robot.GetTarget(), std::vector<std::pair<int, float>>()));
    }

    int startingIndex = 2 * robotList.size();

    // create all of the rest of our nodes
    for (int i = startingIndex; i < PRM_SIZE_; i++) {
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_real_distribution<float> distr(0, 10);
        Point3 loc = Point3(distr(eng), distr(eng), 0);
        if (!WithinObstacle(loc)) {
            nodeList_.push_back(Node(i, loc, std::vector<std::pair<int, float>>()));
        }
        else {
            i--;
        }
    }

    // connect neighboring nodes that do not intersect with an obstacle
    for (int i = 0; i < nodeList_.size(); i++) {
        Node n_i = nodeList_[i];
        for (int j = 0; j < nodeList_.size(); j++) {
            if (i == j) { continue; }
            Node n_j = nodeList_[j];
            if (CanConnect(n_i, n_j)) {
                float distance = DistanceBetween(n_i.GetLocation(), n_j.GetLocation());
                nodeList_[i].AddToNeighborList(std::make_pair(n_j.GetID(), 0));
            }
        }
    }
}

PRM::~PRM() {

}

std::vector<Node>* PRM::GetNodeList() {
    return &nodeList_;
}

float PRM::DistanceBetween(Point3 a, Point3 b) {
    float distance = sqrt(pow(a.x() - b.x(), 2) + pow(a.y() - b.y(), 2) + pow(a.z() - b.z(), 2));
    return distance;
}

bool PRM::CanConnect(Node x, Node y) {
    if (WithinDistance(x, y) && NoObstacleInbetween(x, y)) {
        return true;
    }
    else {
        return false;
    }
}

bool PRM::WithinObstacle(Point3 x) {
    for (Obstacle o : obstacles_) {
        Point3 o_loc = o.GetPosition();

        float distance = sqrt(pow(x[0] - o_loc[0], 2) + pow(x[1] - o_loc[1], 2)
            + pow(x[2] - o_loc[2], 2));

        if (distance < o.GetRadius()) {
            return true;
        }
    }
    return false;
}

bool PRM::WithinDistance(Node x, Node y) {
    float distance = DistanceBetween(x.GetLocation(), y.GetLocation());
    return (distance < DISTANCE_);
}

bool PRM::NoObstacleInbetween(Node x, Node y) {
    for (Obstacle o : obstacles_) {
        Vector3 nodeVec = x.GetLocation() - y.GetLocation();
        Vector3 nodeCirc = x.GetLocation() - o.GetPosition();

        float scalConV = nodeCirc.Dot(nodeVec.ToUnit());
        Vector3 ConV = scalConV * nodeVec.ToUnit();

        Vector3 distFromCircCenter = nodeCirc - ConV;

        float distance = distFromCircCenter.Length();

        if (distance < o.GetRadius()) {
            return false;
        }
    }
    return true;
}

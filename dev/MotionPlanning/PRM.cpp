
#include "PRM.h"

PRM::PRM(Point3 start, Point3 target, std::vector<Obstacle> obstacles) {
    srand(time(NULL));
    start_ = start;
    target_ = target;
    obstacles_ = obstacles;

    // Initialize first item as start with an empty neighbor list
    nodeList_.push_back(Node(0, start_, std::vector<std::pair<Node, double>>()));

    // Initialize second item as target with an empty neighbor list
    nodeList_.push_back(Node(1, target_, std::vector<std::pair<Node, double>>()));

    // create all of the rest of our nodes
    for (int i = 2; i < PRM_SIZE_; i++) {
        Point3 loc = Point3((float)rand() / RAND_MAX * SCENE_X_SIZE_, (float)rand() / RAND_MAX * SCENE_Y_SIZE_, 0);
        if (!WithinObstacle(loc)) {
            nodeList_.push_back(Node(i, loc, std::vector<std::pair<Node, double>>()));
        }
        else {
            i--;
        }
    }

    // connect neighboring nodes that do not intersect with an obstacle
    for (int i = 0; i < nodeList_.size(); i++) {
        for (int j = 0; j < nodeList_.size(); j++) {
            if (i == j) { continue; }
            if (CanConnect(nodeList_[i], nodeList_[j])) {
                double distance = DistanceBetween(nodeList_[i], nodeList_[j]);
                nodeList_[i].AddToNeighborList(std::make_pair(nodeList_[j], distance));
            }
        }
    }
}

PRM::~PRM() {

}

std::vector<Node> PRM::GetNodeList() const {
    return nodeList_;
}

double PRM::DistanceBetween(Node x, Node y) {
    Point3 loc_1 = x.GetLocation();
    Point3 loc_2 = y.GetLocation();

    double distance = sqrt(pow(loc_1.x() - loc_2.x(), 2) + pow(loc_1.y() - loc_2.y(), 2));

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
    return false;
}

bool PRM::WithinDistance(Node x, Node y) {
    double distance = DistanceBetween(x, y);

    return (distance < DISTANCE_);
}

bool PRM::NoObstacleInbetween(Node x, Node y) {
    return true;
}

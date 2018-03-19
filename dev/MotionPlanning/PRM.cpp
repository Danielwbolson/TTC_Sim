
#include "PRM.h"

PRM::PRM(Point2 start, Point2 target, std::vector<Obstacle> obstacles) {
    start_ = start;
    target_ = target;
    obstacles_ = obstacles;

    // Initialize first item as start with an empty neighbor list
    nodeList_.push_back(Node(start_, std::vector<Node>()));

    // Initialize second item as target with an empty neighbor list
    nodeList_.push_back(Node(target_, std::vector<Node>()));

    // create all of our nodes
    for (int i = 0; i < PRM_SIZE_; i++) {
        Point2 loc = Point2(rand()%SCENE_X_SIZE_, rand()%SCENE_Y_SIZE_);
        if (!WithinObstacle(loc)) {
            nodeList_.push_back(Node(loc, std::vector<Node>()));
        }
    }

    // connect neighboring nodes that do not intersect with an obstacle
    // we only need to check for all j > i to avoid getting double edges
    for (int i = 0; i < PRM_SIZE_; i++) {
        for (int j = i; j < PRM_SIZE_; j++) {
            if (i == j) { continue; }
            if (CanConnect(nodeList_[i], nodeList_[j])) {
                nodeList_[i].AddToNeighborList(nodeList_[j]);
                nodeList_[j].AddToNeighborList(nodeList_[i]);

                edgeList_.push_back(Edge(DistanceBetween(nodeList_[i], nodeList_[j]), nodeList_[i], nodeList_[j]));
            }
        }
    }

    graph_ = new Graph(nodeList_, edgeList_);
}

PRM::~PRM() {

}

std::vector<Node> PRM::GetNodeList() {
    return nodeList_;
}

std::vector<Edge> PRM::GetEdgeList() {
    return edgeList_;
}

double PRM::DistanceBetween(Node x, Node y) {
    Point2 loc_1 = x.GetLocation();
    Point2 loc_2 = y.GetLocation();

    double distance = sqrt(pow(loc_1.x() - loc_2.x(), 2) + pow(loc_1.y() - loc_2.y(), 2));

    return distance;
}

bool PRM::CanConnect(Node x, Node y) {
    if (WithinDistance(x, y) && NoObstacleInbetween(x, y)) {
        return true;
    }
}

bool PRM::WithinObstacle(Point2 x) {
    return false;
}

bool PRM::WithinDistance(Node x, Node y) {
    double distance = DistanceBetween(x, y);

    return (distance < DISTANCE_);
}

bool PRM::NoObstacleInbetween(Node x, Node y) {
    return true;
}
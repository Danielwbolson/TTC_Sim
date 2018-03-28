
#include "PRM.h"

PRM::PRM(Robot robot, Point3 start, Point3 target, std::vector<Obstacle> obstacles) {
    srand(time(NULL));
    robot_ = &robot;
    start_ = start;
    target_ = target;
    obstacles_ = obstacles;

    // Initialize first item as start with an empty neighbor list
    nodeList_.push_back(Node(0, start_, std::vector<std::pair<int, double>>()));

    // Initialize second item as target with an empty neighbor list
    nodeList_.push_back(Node(1, target_, std::vector<std::pair<int, double>>()));

    // create all of the rest of our nodes
    for (int i = 2; i < PRM_SIZE_; i++) {
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_real_distribution<float> distr(0, 10);
        Point3 loc = Point3(distr(eng), distr(eng), 0);
        if (!WithinObstacle(loc)) {
            nodeList_.push_back(Node(i, loc, std::vector<std::pair<int, double>>()));
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
                double distance = DistanceBetween(n_i.GetLocation(), n_j.GetLocation());
                nodeList_[i].AddToNeighborList(std::make_pair(n_j.GetID(), 0));
            }
        }
    }
}

PRM::~PRM() {

}

std::vector<Node> const & PRM::GetNodeList() const {
    return nodeList_;
}

double PRM::DistanceBetween(Point3 a, Point3 b) {
    double distance = sqrt(pow(a.x() - b.x(), 2) + pow(a.y() - b.y(), 2));
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

        double distance = sqrt(pow(x[0] - o_loc[0], 2) + pow(x[1] - o_loc[1], 2)
            + pow(x[2] + o_loc[2], 2));

        if (distance < o.GetRadius() + robot_->GetRadius()) {
            return true;
        }
    }
    return false;
}

bool PRM::WithinDistance(Node x, Node y) {
    double distance = DistanceBetween(x.GetLocation(), y.GetLocation());
    return (distance < DISTANCE_);
}

bool PRM::NoObstacleInbetween(Node x, Node y) {
    for (Obstacle o : obstacles_) {
        Vector3 nodeVec = x.GetLocation() - y.GetLocation();
        Vector3 nodeCirc = x.GetLocation() - o.GetPosition();

        double scalConV = nodeCirc.Dot(nodeVec.ToUnit());
        Vector3 ConV = scalConV * nodeVec.ToUnit();

        Vector3 distFromCircCenter = nodeCirc - ConV;

        double distance = distFromCircCenter.Length();

        if (distance < o.GetRadius() + robot_->GetRadius()) {
            return false;
        }
    }
    return true;
}

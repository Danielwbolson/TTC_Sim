
#include "GraphicsViewer.h"

#include <nanogui/nanogui.h>
#include <iostream>

GraphicsViewer::GraphicsViewer() : GraphicsApp(1024,768, "Motion Planning",false), 
        target_(Point3(10, 10, 0)) {
    paused_ = false;

    // Instantiate our Robot
    robot_ = new Robot();

    // Instantiate our Obstacle List
    obstacleList_.push_back(Obstacle(2, Point3(5, 5, 0)));

    // Instantiate our PRM using our robots position, target position
    // and obstacles along the way
    prm_ = new PRM(*robot_, robot_->GetPosition(), target_, obstacleList_);

    // Using our PRM, create a shortest path using Astar
    // Currently using Djikstra
    astar_ = new Astar(prm_->GetNodeList());
    path_ = astar_->GetPath();

    for (int i = 0; i < path_.size(); i++) {
        point_path_.push_back(path_[i].GetLocation());
    }

    // Reverse the path to get it starting from the robot's position
    std::reverse(path_.begin(), path_.end());

    robot_->SetPath(path_);
    robot_->SetObstacles(obstacleList_);
}


GraphicsViewer::~GraphicsViewer() {
    delete robot_;
    obstacleList_.clear();
    delete prm_;
    delete astar_;
    path_.clear();
}

void GraphicsViewer::InitNanoGUI() {
    nanogui::FormHelper *gui = new nanogui::FormHelper(screen());
    nanogui::ref<nanogui::Window> window = gui->addWindow(Eigen::Vector2i(10, 10), "Simulation Controls");    
    pauseBtn_ = gui->addButton("Pause", std::bind(&GraphicsViewer::OnPauseBtnPressed, this));

    screen()->performLayout();
}

void GraphicsViewer::InitOpenGL() {
    // Set up the camera in a good position to see the entire simulation
    projMatrix_ = Matrix4::Perspective(90, aspect_ratio(), 1, 1000);
    viewMatrix_ = Matrix4::LookAt(Point3(5, 5, 10), Point3(5, 6, 0), Vector3(0, 0, 1));

    // Set a background color for screen
    glClearColor(0.8f, 0.8f, 0.8f, 1);
}

void GraphicsViewer::UpdateSimulation(double dt) {
    if (!paused_) {
        robot_->UpdatePosition(dt);
    }
}

void GraphicsViewer::OnPauseBtnPressed() {
    paused_ = !paused_;
    if (paused_) {
        pauseBtn_->setCaption("Play");
    }
    else {
        pauseBtn_->setCaption("Pause");
    }
}


void GraphicsViewer::DrawUsingNanoVG(NVGcontext *ctx) {
    // example of drawing some circles

    /*nvgBeginPath(ctx);
    nvgCircle(ctx, 512+50.0*cos(simTime_), 350+200.0*sin(simTime_), 50);
    nvgFillColor(ctx, nvgRGBA(100,100,255,200));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(0,0,0,255));
    nvgStroke(ctx);

    nvgBeginPath(ctx);
    nvgCircle(ctx, 512+200.0*cos(simTime_), 350+50.0*sin(simTime_), 50);
    nvgFillColor(ctx, nvgRGBA(255,100,100,200));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(0,0,0,255));
    nvgStroke(ctx);*/
}

void GraphicsViewer::DrawUsingOpenGL() {
    DrawObstacles();
    DrawPRM();
    DrawPath();
    DrawRobot();
}

void GraphicsViewer::DrawRobot() {
    Color robotcol(0, 0, 1);
    Matrix4 Mrobot =
        Matrix4::Translation(robot_->GetPosition() - Point3(0, 0, 0)) *
        Matrix4::Scale(Vector3(robot_->GetSize())) *
        Matrix4::RotationX(GfxMath::ToRadians(90));
    quick_shapes_.DrawCylinder(modelMatrix_ * Mrobot, viewMatrix_, projMatrix_, robotcol);
}

void GraphicsViewer::DrawObstacles() {
    Color obstaclecol(0, 0, 0, 0.1);
    for (Obstacle o : obstacleList_) {
        Matrix4 Mobstacle =
            Matrix4::Translation(o.GetPosition() - Point3(0, 0, 0)) *
            Matrix4::Scale(Vector3(o.GetRadius(), o.GetRadius(), 0.1)) *
            Matrix4::RotationX(GfxMath::ToRadians(90));
        quick_shapes_.DrawCylinder(modelMatrix_ * Mobstacle, viewMatrix_, projMatrix_, obstaclecol);
    }
}

void GraphicsViewer::DrawPRM() {
    Color nodecol(1, 0, 0);
    for (Node n : prm_->GetNodeList()) {
        Matrix4 Mnode =
            Matrix4::Translation(n.GetLocation() - Point3(0, 0, 0)) *
            Matrix4::Scale(Vector3(0.05f, 0.05f, 0.05f)) *
            Matrix4::RotationX(GfxMath::ToRadians(90));
        quick_shapes_.DrawSquare(modelMatrix_ * Mnode, viewMatrix_, projMatrix_, nodecol);
    }
}

void GraphicsViewer::DrawPath() {
    Color pathcol(0, 1, 0);
    for (int i = 0; i < point_path_.size() - 1; i++) {
        quick_shapes_.DrawLineSegment(modelMatrix_, viewMatrix_, projMatrix_, pathcol, point_path_[i], point_path_[i+1], 0.02f);
    }
}

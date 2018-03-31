
#include "GraphicsViewer.h"

#include <nanogui/nanogui.h>
#include <iostream>

GraphicsViewer::GraphicsViewer() : GraphicsApp(1024,768, "Motion Planning",false), paused_(false) {

    // Instantiate our Robots
    robotList_.push_back(Robot(Point3(0, 0, 0), Point3(10, 10, 0), 0.5));
    robotList_.push_back(Robot(Point3(10, 10, 0), Point3(0, 0, 0), 0.5));
    robotList_.push_back(Robot(Point3(10, 0, 0), Point3(0, 10, 0), 1));
    robotList_.push_back(Robot(Point3(0, 10, 0), Point3(10, 0, 0), 1));

    // Instantiate our Obstacle List
    obstacleList_.push_back(Obstacle(2, Point3(5, 5, 0)));

    // Instantiate our PRM using our robots position, target position
    // and obstacles along the way
    prm_ = new PRM(robotList_, obstacleList_);

    // Using our PRM, create a shortest path using Astar
    // Currently using Djikstra
    astar_ = new Astar(prm_->GetNodeList(), robotList_);

    for (Robot r : robotList_) {
        r.SetObstacles(obstacleList_);
    }
}


GraphicsViewer::~GraphicsViewer() {
    obstacleList_.clear();
    delete prm_;
    delete astar_;
    robotList_.clear();
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
        for (Robot r : robotList_) {
            r.UpdatePosition(dt);
        }
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
    DrawRobots();
}

void GraphicsViewer::DrawRobots() {
    for (Robot r : robotList_) {
        Color robotcol(0, 0, 1);
        Matrix4 Mrobot =
            Matrix4::Translation(r.GetPosition() - Point3(0, 0, 0)) *
            Matrix4::Scale(Vector3(r.GetSize())) *
            Matrix4::RotationX(GfxMath::ToRadians(90));
        quick_shapes_.DrawCylinder(modelMatrix_ * Mrobot, viewMatrix_, projMatrix_, robotcol);
    }
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
    for (Robot r : robotList_) {
        std::vector<Node> robotPath = r.GetPath();
        Color pathcol(0, 1, 0);
        for (int i = 0; i < robotPath.size() - 1; i++) {
            quick_shapes_.DrawLineSegment(modelMatrix_, viewMatrix_, projMatrix_, pathcol, robotPath[i].GetLocation(), robotPath[i+1].GetLocation(), 0.02f);
        }
    }
}

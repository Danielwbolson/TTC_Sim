
#include "GraphicsViewer.h"

#include <nanogui/nanogui.h>
#include <iostream>

GraphicsViewer::GraphicsViewer() : GraphicsApp(1024,768, "Motion Planning", false), 
        target_(Point3(10, 10, 0)) {
    simTime_ = 0.0;
    paused_ = false;

    // Instantiate our Robot
    robot_ = new Robot();

    // Instantiate our Obstacle List
    //obstacleList_ = obstacle_->MakeObstacles();

    // Instantiate our PRM using our robots position, target position
    // and obstacles along the way
    prm_ = new PRM(robot_->GetPosition(), target_, obstacleList_);

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
    gui->addButton("Restart", std::bind(&GraphicsViewer::OnRestartBtnPressed, this));

    screen()->performLayout();
}

void GraphicsViewer::InitOpenGL() {
    // Set up the camera in a good position to see the entire simulation
    projMatrix_ = Matrix4::Perspective(90, aspect_ratio(), 1, 1000);
    viewMatrix_ = Matrix4::LookAt(Point3(5, 5, 10), Point3(5, 6, 0), Vector3(0, 0, 1));

    // Set a background color for screen
    glClearColor(0.8, 0.8, 0.8, 1);
}

void GraphicsViewer::UpdateSimulation(double dt) {
    if (!paused_) {
        robot_->UpdatePosition(dt);
    }
}


void GraphicsViewer::OnRestartBtnPressed() {
    simTime_ = 0.0;
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


void GraphicsViewer::OnMouseMove(const Point2 &pos, const Vector2 &delta) {
    std::cout << "Mouse moved by " << delta << " to reach " << pos << std::endl;
}


void GraphicsViewer::OnLeftMouseDown(const Point2 &pos) {
    std::cout << "Left mouse button DOWN at " << pos << std::endl;
}

void GraphicsViewer::OnLeftMouseDrag(const Point2 &pos, const Vector2 &delta) {
    std::cout << "Mouse dragged (left button) by " << delta << " to reach " << pos << std::endl;
}

void GraphicsViewer::OnLeftMouseUp(const Point2 &pos) {
    std::cout << "Left mouse button UP at " << pos << std::endl;
}


void GraphicsViewer::OnRightMouseDown(const Point2 &pos) {
    std::cout << "Right mouse button DOWN at " << pos << std::endl;
}

void GraphicsViewer::OnRightMouseDrag(const Point2 &pos, const Vector2 &delta) {
    std::cout << "Mouse dragged (right button) by " << delta << " to reach " << pos << std::endl;
}

void GraphicsViewer::OnRightMouseUp(const Point2 &pos) {
    std::cout << "Right mouse button UP at " << pos << std::endl;
}


void GraphicsViewer::OnKeyDown(const char *c, int modifiers) {
    std::cout << "Key DOWN (" << c << ") modifiers=" << modifiers << std::endl; 
}

void GraphicsViewer::OnKeyUp(const char *c, int modifiers) {
    std::cout << "Key UP (" << c << ") modifiers=" << modifiers << std::endl; 
}


void GraphicsViewer::OnSpecialKeyDown(int key, int scancode, int modifiers) {
    std::cout << "Special Key DOWN key=" << key << " scancode=" << scancode << " modifiers=" << modifiers << std::endl; 
}

void GraphicsViewer::OnSpecialKeyUp(int key, int scancode, int modifiers) {
    std::cout << "Special Key UP key=" << key << " scancode=" << scancode << " modifiers=" << modifiers << std::endl; 
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
    DrawRobot();
    DrawObstacles();
    DrawPRM();
   // DrawPath();
}

void GraphicsViewer::DrawRobot() {

}

void GraphicsViewer::DrawObstacles() {

}

void GraphicsViewer::DrawPRM() {
    Color nodecol(1, 0, 0);
    for (Node n : prm_->GetNodeList()) {
        Matrix4 Mnode =
            Matrix4::Translation(n.GetLocation() - Point3(0, 0, 0)) *
            Matrix4::Scale(Vector3(0.2, 0.2, 0.2)) *
            Matrix4::RotationX(GfxMath::ToRadians(90));
        quick_shapes_.DrawSphere(modelMatrix_ * Mnode, viewMatrix_, projMatrix_, nodecol);
    }
}

void GraphicsViewer::DrawPath() {
    Color pathcol(0, 1, 0);
    quick_shapes_.DrawLines(modelMatrix_, viewMatrix_, projMatrix_, pathcol, point_path_, quick_shapes_.LINES, 1);
}

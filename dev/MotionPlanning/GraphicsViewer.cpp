
#include "GraphicsViewer.h"

#include <nanogui/nanogui.h>
#include <iostream>

GraphicsViewer::GraphicsViewer() : GraphicsApp(1024,768, "Circle Simulation",false), target_(Point2(10, 10)) {
    simTime_ = 0.0;
    paused_ = false;

    robot_ = new Robot();
    //obstacleList_.push_back()
    prm_ = new PRM(robot_->GetPosition(), target_, obstacleList_);
}


GraphicsViewer::~GraphicsViewer() {
    delete robot_;
    obstacleList_.clear();
    delete prm_;
}

void GraphicsViewer::InitNanoGUI() {
    nanogui::FormHelper *gui = new nanogui::FormHelper(screen());
    nanogui::ref<nanogui::Window> window = gui->addWindow(Eigen::Vector2i(10, 10), "Simulation Controls");    
    pauseBtn_ = gui->addButton("Pause", std::bind(&GraphicsViewer::OnPauseBtnPressed, this));
    gui->addButton("Restart", std::bind(&GraphicsViewer::OnRestartBtnPressed, this));

    screen()->performLayout();
}

void GraphicsViewer::UpdateSimulation(double dt) {
    if (!paused_) {
        simTime_ += dt;
        std::cout << "Update Simulation " << simTime_ << std::endl;
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
}

void GraphicsViewer::DrawRobot() {

}

void GraphicsViewer::DrawObstacles() {

}

void GraphicsViewer::DrawPRM() {
    for (Node n : prm_->GetNodeList()) {

    }
}


#include "GraphicsViewer.h"

#include <nanogui/nanogui.h>
#include <iostream>

GraphicsViewer::GraphicsViewer() : GraphicsApp(1024,768, "Motion Planning",false), paused_(false) {

    DefaultShader::LightProperties light;
    light.position = Point3(5, 5, 20);
    light.diffuse_intensity = Color(0, 0, 0);
    s_.AddLight(light);

    std::vector<std::string> search_path;
    search_path.push_back(".");
    search_path.push_back("./data");
    search_path.push_back("C:/Users/Daniel/Desktop/Spring2018/5611/Assignment3/dev/MotionPlanning/data");
    //m_.LoadFromOBJ(Platform::FindFile("box.obj", search_path));
    m_.LoadFromOBJ(Platform::FindMinGfxDataFile("teapot.obj"));

    // Instantiate our Robots
    robotList_.push_back(Robot(Point3(0, 0, 0), Point3(10, 10, 0), 0.5));
    robotList_.push_back(Robot(Point3(0, 5, 0), Point3(10, 5, 0), 0.5));
    robotList_.push_back(Robot(Point3(0, 10, 0), Point3(10, 0, 0), 1));
    robotList_.push_back(Robot(Point3(5, 10, 0), Point3(5, 0, 0), 1));

    // Instantiate our Obstacle List
    obstacleList_.push_back(Obstacle(2, Point3(5, 5, 0)));

    // Instantiate our PRM using our robots position, target position
    // and obstacles along the way
    prm_ = new PRM(robotList_, obstacleList_);

    ConstructIndexes(prm_->GetNodeList());

    // Using our PRM, create a shortest path using Astar
    // Currently using Djikstra
    astar_ = new Astar(prm_->GetNodeList(), robotList_, obstacleList_);

    for (Robot &r : robotList_) {
        r.SetObstacles(obstacleList_);
    }
}


GraphicsViewer::~GraphicsViewer() {
    obstacleList_.clear();
    delete prm_;
    delete astar_;
    robotList_.clear();
}

void GraphicsViewer::ConstructIndexes(std::vector<Node> nodes) {
    double rad = 0.05;
    for (int i = 0; i < nodes.size(); i++) {
        Point3 loc = nodes[i].GetLocation();

        if (loc[0] - rad > 0 && loc[1] - rad > 0) {
            vertices.push_back(Point3(loc[0] - rad, loc[1] - rad, 0)); // bottom left
            vertices.push_back(Point3(loc[0] + rad, loc[1] - rad, 0)); // bottom right
            vertices.push_back(Point3(loc[0] - rad, loc[1] + rad, 0)); // top left
            vertices.push_back(Point3(loc[0] + rad, loc[1] + rad, 0)); // top right
        }
        else {
            vertices.push_back(Point3(loc[0], loc[1], 0)); // bottom left
            vertices.push_back(Point3(loc[0] + rad, loc[1], 0)); // bottom right
            vertices.push_back(Point3(loc[0], loc[1] + rad, 0)); // top left
            vertices.push_back(Point3(loc[0] + rad, loc[1] + rad, 0)); // top right
        }

        normals.push_back(Vector3(0, 0, 1));
        normals.push_back(Vector3(0, 0, 1));
        normals.push_back(Vector3(0, 0, 1));
        normals.push_back(Vector3(0, 0, 1));

        texcoords.push_back(Point2(0, 1));
        texcoords.push_back(Point2(1, 1));
        texcoords.push_back(Point2(0, 0));
        texcoords.push_back(Point2(1, 0));
    }

    for (int i = 0; i < 4 * nodes.size(); i+=4) {
        indices.push_back(i);
        indices.push_back(i+1);
        indices.push_back(i+3);

        indices.push_back(i);
        indices.push_back(i+3);
        indices.push_back(i+2);
    }

    m_.SetVertices(vertices);
    m_.SetNormals(normals);
    m_.SetTexCoords(0, texcoords);
    m_.SetIndices(indices);
    m_.UpdateGPUMemory();
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
        for (Robot &r : robotList_) {
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
    for (Robot &r : robotList_) {
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
    /*Color nodecol(1, 0, 0);
    for (Node n : prm_->GetNodeList()) {
        Matrix4 Mnode =
            Matrix4::Translation(n.GetLocation() - Point3(0, 0, 0)) *
            Matrix4::Scale(Vector3(0.05f, 0.05f, 0.05f)) *
            Matrix4::RotationX(GfxMath::ToRadians(90));
        quick_shapes_.DrawSquare(modelMatrix_ * Mnode, viewMatrix_, projMatrix_, nodecol);
    }*/
    s_.Draw(modelMatrix_, viewMatrix_, projMatrix_, &m_, mat);
}

void GraphicsViewer::DrawPath() {
    for (Robot &r : robotList_) {
        std::vector<Node> robotPath = r.GetPath();
        Color pathcol(0, 1, 0);
        for (int i = 0; i < robotPath.size() - 1; i++) {
            quick_shapes_.DrawLineSegment(modelMatrix_, viewMatrix_, projMatrix_, pathcol, robotPath[i].GetLocation(), robotPath[i+1].GetLocation(), 0.02f);
        }
    }
}

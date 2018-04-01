
#ifndef GRAPHICS_VIEWER_H_
#define GRAPHICS_VIEWER_H_

#include <mingfx.h>
#include <string>
#include <vector>

#include "PRM.h"
#include "Robot.h"
#include "Obstacle.h"
#include "Node.h"
#include "Astar.h"


class GraphicsViewer : public GraphicsApp {
public:
    GraphicsViewer();
    ~GraphicsViewer();

    void ConstructIndexes(std::vector<Node>);

    void InitNanoGUI();

    void InitOpenGL();

    void UpdateSimulation(double dt);

    void OnPauseBtnPressed();

    void DrawUsingNanoVG(NVGcontext *ctx);

    void DrawUsingOpenGL();

    void DrawRobots();
    void DrawObstacles();
    void DrawPRM();
    void DrawPath();

protected:
    bool paused_;
    nanogui::Button *pauseBtn_;

    Matrix4 projMatrix_;
    Matrix4 viewMatrix_;
    Matrix4 modelMatrix_;

    std::vector<Point3> vertices;
    std::vector<Vector3> normals;
    std::vector<Point2> texcoords;
    std::vector<unsigned int> indices;

    // reference to robot class and our main entity
    std::vector<Robot> robotList_;

    // collection of obstacles and a reference to obstacle class
    std::vector<Obstacle> obstacleList_;

    // reference to our PRM
    PRM* prm_;

    // reference to our algorithm
    Astar* astar_;

    // reference to quick_shapes to draw 3d objects
    QuickShapes quick_shapes_;

    Mesh m_;

    Texture2D boxTex;

    DefaultShader s_;

    DefaultShader::MaterialProperties mat;
};

#endif // GRAPHICS_VIEWER_H_
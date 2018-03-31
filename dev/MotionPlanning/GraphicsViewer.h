
#ifndef GRAPHICS_VIEWER_H_
#define GRAPHICS_VIEWER_H_

#include <mingfx.h>
#include "PRM.h"
#include "Robot.h"
#include "Obstacle.h"
#include "Node.h"
#include "Astar.h"


/** An application that opens up a window that includes a few buttons 
    for controlling the simulation and can be used to draw circles and 
    other computer graphics.

    After constructing a new GraphicsViewer, call Run() to start and
    run the application.  Run() will not return until the application
    window is closed.  Make sure that you call cs3081::InitGraphics()
    before creating the RobotViewer app.  Example:

    ```
    int main(int argc, char **argv) {
        cs3081::InitGraphics();
        cs3081::GraphicsViewer *app = new cs3081::GraphicsViewer();
        app->Run();
        cs3081::ShutdownGraphics();
        return 0;
    }
    ```

    While the window is open UpdateSimulation() will be called
    repeatedly, once per frame.  Fill this in to update your simulation
    or perform any other processing that should happen over time as the
    simulation progresses.

    Fill in the On*() methods as desired to respond to user input events.

    Fill in the Draw*() methods to draw graphics to the screen using
    either the nanovg library or raw OpenGL.
*/

class GraphicsViewer : public GraphicsApp {
public:
    GraphicsViewer();
    ~GraphicsViewer();

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

private:
    bool paused_;
    nanogui::Button *pauseBtn_;

    Matrix4 projMatrix_;
    Matrix4 viewMatrix_;
    Matrix4 modelMatrix_;

    // reference to robot class and our main entity
    std::vector<Robot> robotList_;

    // collection of obstacles and a reference to obstacle class
    std::vector<Obstacle> obstacleList_;

    // reference to our PRM
    PRM* prm_;

    // reference to our algorithm
    Astar* astar_;

    // save our path of correct nodes
    std::vector<Node> path_;

    // reference to quick_shapes to draw 3d objects
    QuickShapes quick_shapes_;
};

#endif // GRAPHICS_VIEWER_H_
#ifndef App_h
#define App_h

#include <vector>
#include "GlutApp.h"
#include "GameManager.h"

class App: public GlutApp {

// std::vector<Shape*> shapes;

GameManager gm;

public:
    
    App(int argc, char** argv, int width, int height, const char* title);
    
    void draw() const;
    
    void keyDown(unsigned char key, float x, float y);
    
    void idle();

    ~App();
};

#endif

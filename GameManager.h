#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include "PlayerShip.h"

class GameManager {
private:
    PlayerShip ps;

public:
    GameManager();

    void draw() const;
    void moveUpdate(unsigned char key);
    void update();
};
#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <vector>
#include "PlayerShip.h"
#include "Projectile.h"
#include "Hearts.h"

class GameManager {
private:
    PlayerShip ps;
    std::vector<GameEntity*> gameObjects;
    std::vector<GUIEntity*> guiObjects;

public:
    GameManager();

    void draw() const;
    void moveUpdate(unsigned char key);
    void update();

    void fireProjectile();
    bool decreaseHealth();
};
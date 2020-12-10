#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include "PlayerShip.h"
#include "Projectile.h"
#include "Meteor.h"
#include "Hearts.h"
#include "Ammo.h"

class GameManager {
private:
    int ammoCount = 3;
    int gameState = 0;
    int score = 0;
    float timer;
    std::clock_t currTime;

    PlayerShip ps;
    std::vector<Meteor*> gameObjects;
    std::vector<Projectile*> projs;
    std::vector<GUIEntity*> guiObjects;

public:
    GameManager();

    void draw() const;
    void moveUpdate(unsigned char key);
    void update();

    void checkForCollisions();

    void fireProjectile();
    bool decreaseHealth();

    void increaseAmmo();
    void decreaseAmmo();

    void startMeteorTime();
    void checkMeteorTime();
    
    float genRandFloat(float, float);
    void reset();
};
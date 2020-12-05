#include "GameManager.h"

GameManager::GameManager() {
    
}

void GameManager::draw() const {
    //Draw background
    glColor3f(0,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(1,1);
    glVertex2f(1,-1);
    glVertex2f(-1,-1);
    glVertex2f(-1,1);
    glEnd();

    ps.draw();
}

void GameManager::moveUpdate(unsigned char key) {
    switch(key) {
        case 'w':
        case 'W':
            ps.moveForward();
            break;
        
        case 's':
        case 'S':
            ps.moveBackwards();
            break;
        
        case 'a':
        case 'A':
            ps.turnLeft();
            break;

        case 'd':
        case 'D':
            ps.turnRight();
            break;
    }
}

void GameManager::update() {
    //Loop over objects that need to be updated here
}
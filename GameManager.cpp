#include "GameManager.h"

GameManager::GameManager() {
    for(int i = 0; i < 3; i++) {
        guiObjects.push_back(new Hearts(-0.9, -.9+(i*.11)));
        guiObjects.push_back(new Ammo(0.85, -.9+(i*.11)));
    }
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

    for(auto i = gameObjects.begin(); i != gameObjects.end(); i++) {
        (*i)->draw(0);
    }

    for(auto i = guiObjects.begin(); i != guiObjects.end(); i++) {
        (*i)->draw(-1);
    }

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

        case ' ':
            fireProjectile();
            break;
    }
}

void GameManager::update() {
    //Loop over objects that need to be updated here
    for(auto i = gameObjects.begin(); i != gameObjects.end();) {
        (*i)->move();
        
        if((*i)->toDelete()) {
            std::cout << "yey" << std::endl;
            if((*i)->getType() == 1) {
                
                ammoCount++;
            }
            i = gameObjects.erase(i);
        } else {
            ++i;
        }
    }
}

void GameManager::fireProjectile() {
    if(ammoCount == 0) {
        return;
    }

    gameObjects.push_back(new Projectile(ps.getX(), ps.getY(), ps.getAngle()));
    ammoCount--;
}

bool GameManager::decreaseHealth() {
    int hiddenCount = 0;

    for(auto i = guiObjects.end()-1; i != guiObjects.begin()-1; i--) {
        if(!(*i)->getHidden()) {
            (*i)->setHidden(true);

            break;
        } else {
            hiddenCount++;
        }
    }

    return hiddenCount == 3;
}
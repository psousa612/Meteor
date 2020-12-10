#include "GameManager.h"

GameManager::GameManager() {
    for(int i = 0; i < 3; i++) {
        guiObjects.push_back(new Hearts(-0.9, -.9+(i*.11)));
        guiObjects.push_back(new Ammo(0.85, -.9+(i*.11)));
    }
    ammoCount = 3;
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

    for(auto i = projs.begin(); i != projs.end(); i++) {
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

        // std::cout << gameObjects.size() << std::endl;
        if((*i)->toDelete()) {
            // std::cout << (*i)->getType() << std::endl;

            i = gameObjects.erase(i);
        } else {
            ++i;
        }
    }

    for(auto i = projs.begin(); i != projs.end();) {
        (*i)->move();

        if((*i)->toDelete()) {
            increaseAmmo();
            i = projs.erase(i);
        } else {
            i++;
        }
    }

    checkForCollisions();

    checkMeteorTime();
}

void GameManager::checkForCollisions() {
    for(int i = 0; i < projs.size(); i++) {
        for(int j = 0; j < gameObjects.size(); j++) {
            if(gameObjects.at(j)->contains(projs.at(i)->getX(), projs.at(i)->getY(), projs.at(i)->getW(), projs.at(i)->getH())) {
                
            }
        }
    }
}

void GameManager::fireProjectile() {
    if(ammoCount == 0) {
        return;
    }

    projs.push_back(new Projectile(ps.getX(), ps.getY(), ps.getAngle()));
    decreaseAmmo();
}

bool GameManager::decreaseHealth() {
    int hiddenCount = 0;

    for(auto i = guiObjects.end()-1; i != guiObjects.begin()-1; i--) {
        if((*i)->getType() != 100) {
            return false;
        }

        if(!(*i)->getHidden()) {
            (*i)->setHidden(true);

            break;
        } else {
            hiddenCount++;
        }
    }

    return hiddenCount == 3;
}

void GameManager::increaseAmmo() {
    ammoCount++;
    
    for(auto i = guiObjects.begin(); i != guiObjects.end(); i++) {
        if((*i)->getType() != 101) {
            continue;
        }

        if((*i)->getHidden()) {
            (*i)->setHidden(false);
            return;
        }
    }
}

void GameManager::decreaseAmmo() {
    ammoCount--;

    for(auto i = guiObjects.end()-1; i != guiObjects.begin()-1; i--) {
        if((*i)->getType() != 101) {
            continue;
        }

        if(!(*i)->getHidden()) {
            (*i)->setHidden(true);
            return;
        }
    }
}

void GameManager::startMeteorTime() {
    currTime = std::clock();
    timer = .04;
}

void GameManager::checkMeteorTime() {
    
    double duration = ( std::clock() - currTime ) / (double) CLOCKS_PER_SEC;
    // std::cout << timer << ", " << duration << std::endl;
    if(duration > timer) {
        //Spawn Meteor
        int direction = ((int)rand() % 4) + 1;
        float nX = 0;
        float nY = 0;
        
        
        nY = (((float)(rand())/(float)RAND_MAX)*2)-1;
        // std::cout <<"dir:" <<  direction << std::endl;
        switch(direction) {
            case 1: //Left
                nX = genRandFloat(-1, -0.8);
                nY = genRandFloat(-1, 1);
                break;

            case 2: //Up
                nX = genRandFloat(-1, 1);
                nY = genRandFloat(0.8, 1);
                break;

            case 3: //Right
                nX = genRandFloat(0.8, 1);
                nY = genRandFloat(-1, 1);
                break;

            case 4: //Down
                nX = genRandFloat(-1, 1);
                nY = genRandFloat(-0.8, -1);
                break;
        }

        

        // std::cout << nX << ", " << nY << std::endl;
        gameObjects.push_back(new Meteor(nX, nY));
        
        //Reset the timer
        startMeteorTime();
    }
}

float GameManager::genRandFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}



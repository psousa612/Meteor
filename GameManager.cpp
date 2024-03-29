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
    void* font = GLUT_BITMAP_HELVETICA_18;
    float offset, x, y;
    ps.draw();

    glColor3f(1, 1, 1);
    offset = 0.02;
    x = -0.15;
    y = 0.8;
    std::string text = "Score: " + std::to_string(score);
    for (int i = 0; i < text.length(); i++) {
        glRasterPos3f(x+offset, y,1);
        glutBitmapCharacter(font, text[i]);
        int w = glutBitmapWidth(font, text[i]);
        offset += ((float)w / 640)*2;
    }

    for(auto i = gameObjects.begin(); i != gameObjects.end(); i++) {
        (*i)->draw(0);
    }

    for(auto i = guiObjects.begin(); i != guiObjects.end(); i++) {
        (*i)->draw(-1);
    }

    for(auto i = projs.begin(); i != projs.end(); i++) {
        (*i)->draw(-1);
    }

    if(gameState == 1) {
        

        glColor3f(1, 1, 1);
        offset = 0.02;
        x = -0.1;
        y = 0;
        std::string text = "Game Over!";
        for (int i = 0; i < text.length(); i++) {
            glRasterPos3f(x+offset, y,1);
            glutBitmapCharacter(font, text[i]);
            int w = glutBitmapWidth(font, text[i]);
            offset += ((float)w / 640)*2;
        }

        glColor3f(1, 1, 1);
        offset = 0.02;
        x = -0.1;
        y = -0.2;
        text = "Press Space To Continue!";
        for (int i = 0; i < text.length(); i++) {
            glRasterPos3f(x+offset, y,1);
            glutBitmapCharacter(font, text[i]);
            int w = glutBitmapWidth(font, text[i]);
            offset += ((float)w / 640)*2;
        }
        
    }

}

void GameManager::moveUpdate(unsigned char key) {
    if(gameState == 1) {
        if(key == ' ') {
            reset();
            return;
        } else {
            return;
        }
    }

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
    if(gameState == 1) {
        return;
    }
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
                gameObjects.erase(gameObjects.begin() + j);
                projs.erase(projs.begin() + i);
                increaseAmmo();
                score += 100;
                // i--;
                // j--;
                return;
            }
            // std::cout << gameObjects.at(j)->contains(ps.getX(), ps.getY(), ps.getW(), ps.getY()) << std::endl;
            
        }
    }

    for(int i = 0; i < gameObjects.size(); i++) {
        if(gameObjects.at(i)->contains(ps.getX(), ps.getY(), ps.getW(), ps.getH())) {
            
            if(decreaseHealth()) {
                gameState = 1;
            }
            //delete meteor 
            gameObjects.erase(gameObjects.begin() + i);
            return;
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
    // std::cout << "bye bye mario" << std::endl;
    int hiddenCount = 0;

    for(auto i = guiObjects.end()-1; i != guiObjects.begin()-1; i--) {
        if((*i)->getType() != 100) {
            continue;
        }

        if(!(*i)->getHidden()) {
            (*i)->setHidden(true);
            hiddenCount++;
            break;
        } else {
            hiddenCount++;
        }
    }
    // std::cout << hiddenCount << std::endl;
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
    timer = .03;
}

void GameManager::checkMeteorTime() {
    
    double duration = ( std::clock() - currTime ) / (double) CLOCKS_PER_SEC;
    // std::cout << timer << ", " << duration << std::endl;
    if(duration > timer) {
        //Spawn Meteor
        int direction = ((int)rand() % 4) + 1;
        float nX = 0;
        float nY = 0;
        float a = 0;
        
        
        // nY = (((float)(rand())/(float)RAND_MAX)*2)-1;
        // std::cout <<"dir:" <<  direction << std::endl;
        switch(direction) {
            case 1: //Left
                nX = genRandFloat(-1, -0.8);
                nY = genRandFloat(-1, 1);
                a = genRandFloat(-25, 25);
                break;

            case 2: //Up
                nX = genRandFloat(-1, 1);
                nY = genRandFloat(0.8, 1);
                a = genRandFloat(225, 270);
                break;

            case 3: //Right
                nX = genRandFloat(0.8, 1);
                nY = genRandFloat(-1, 1);
                a = genRandFloat(155, 205);
                break;

            case 4: //Down
                nX = genRandFloat(-1, 1);
                nY = genRandFloat(-0.8, -1);
                a = genRandFloat(65, 115);
                break;
        }

        
        // std::cout << nX << ", " << nY << std::endl;
        gameObjects.push_back(new Meteor(nX, nY, a));
        
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

void GameManager::reset() {
    ps.setX(0);
    ps.setY(0);
    // std::cout << "huh" << std::endl;
    gameObjects.clear();
    guiObjects.clear();
    
    for(int i = 0; i < 3; i++) {
        guiObjects.push_back(new Hearts(-0.9, -.9+(i*.11)));
        guiObjects.push_back(new Ammo(0.85, -.9+(i*.11)));
    }

    ammoCount = 3;
    score = 0;
    gameState = 0;
}


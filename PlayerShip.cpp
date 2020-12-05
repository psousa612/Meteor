#include "PlayerShip.h"
#include <iostream>

PlayerShip::PlayerShip() : GameEntity("images/ship.png", -1, 1, 3, 3) {
    x = 0;
    y = 0;
    w = .1;
    h = .1;
    moveRes = .1;
    angle = 0;
    angleOffset = 90;
    angleMoveRes = 15;
    w = .5;
}

void PlayerShip::draw(float z) const {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glEnable(GL_TEXTURE_2D);

    glColor4f(1,1,1,1);
    glBegin(GL_POLYGON);
    // std::cout<<"_____"<<std::endl;
    for(int i = 0; i < 4; i++) {
        // std::cout << (i*90.0 + angle + angleOffset) << std::endl;
        // switch(i) {
        //     case 0:
        //         glTexCoord2f(1, 1);
        //         break;

        //     case 1:
        //         glTexCoord2f(1,0);
        //         break;

        //     case 2:
        //         glTexCoord2f(0,0);
        //         break;

        //     case 3:
        //         glTexCoord2f(0, 1);
        //         break;
        // }
        
        
        float currAngle = toRads((i*90.0 + angle + angleOffset));
        glTexCoord2f(w * cos(currAngle), w * sin(currAngle));
        glVertex2f((w * cos(currAngle))+x, (w * sin(currAngle))+y);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // glColor3f(0,0,0);
    // glBegin(GL_LINES);
    // glVertex2f(x, y);
    // glVertex2f(x+cos(toRads(angle)), y+sin(toRads(angle)));
    // glEnd();

    // std::cout<<x << ", " << y <<std::endl;
    // std::cout << angle << std::endl;
}

void PlayerShip::moveForward() {
    x += moveRes*cos(toRads(angle + angleOffset));
    y += moveRes*sin(toRads(angle + angleOffset));
}

void PlayerShip::moveBackwards() {
    x -= moveRes*cos(toRads(angle + angleOffset));
    y -= moveRes*sin(toRads(angle + angleOffset));
}

void PlayerShip::turnLeft() {
    angle += angleMoveRes;
}

void PlayerShip::turnRight() {
    std::cout << "turning right!" << std::endl;
    angle -= angleMoveRes;
}

void PlayerShip::move() {
    //nothing here....
}



bool PlayerShip::contains(float nX, float nY) {
    std::cout << "checking collision!" << std::endl;
}

float PlayerShip::toRads(float degrees) const {
    return degrees * (M_PI/180.0);
}
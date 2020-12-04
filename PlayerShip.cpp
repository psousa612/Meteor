#include "PlayerShip.h"
#include <iostream>

PlayerShip::PlayerShip() {
    x = 0;
    y = 0;
    w = .1;
    h = .1;
    moveRes = .1;
    angle = 90;
    angleOffset = 0;
    angleMoveRes = 0.15;
    w = (0.1 * sqrt(2)) / 2.0;
}

void PlayerShip::draw(float z) const {
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    // std::cout<<"_____"<<std::endl;
    for(int i = 0; i < 4; i++) {
        // std::cout << (i*90.0 + angle + angleOffset) << std::endl;
        float currAngle = toRads((i*90.0 + angle + angleOffset));
        glVertex2f((w * cos(currAngle))+x, (w * sin(currAngle))+y);
    }
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x+cos(toRads(angle)), y+sin(toRads(angle)));
    glEnd();

    // std::cout<<x << ", " << y <<std::endl;
    // std::cout << angle << std::endl;
}

void PlayerShip::moveForward() {
    std::cout << "moving forward!" << std::endl;
    x += moveRes*cos(toRads(angle + angleOffset));
    y += moveRes*sin(toRads(angle + angleOffset));
}

void PlayerShip::moveBackwards() {
    std::cout << "move backwards!" << std::endl;
    x -= moveRes*cos(toRads(angle + angleOffset));
    y -= moveRes*sin(toRads(angle + angleOffset));
}

void PlayerShip::turnLeft() {
    std::cout << "-----------" << std::endl;
    std::cout << angle << std::endl;
    std::cout << angleMoveRes << std::endl;
    angle += angleMoveRes;
    std::cout << angle << std::endl;

}

void PlayerShip::turnRight() {
    std::cout << "turning right!" << std::endl;
    angle -= angleMoveRes;
}

void PlayerShip::move() {
    //nothing here....
}

bool PlayerShip::checkCollision(float nX, float nY) {
    std::cout << "checking collision!" << std::endl;
}

float PlayerShip::toRads(float degrees) const {
    return degrees * (M_PI/180.0);
}
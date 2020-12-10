#include "Meteor.h"
#include <iostream>

Meteor::Meteor() : GameEntity("images/meteor1.png", -1, 1, 1, 1) {

}

Meteor::Meteor(float x, float y, float a) : GameEntity("images/meteor1.png", -1, 1, 1, 1){
    this->x = x;
    this->y = y;
    w = 0.15;
    h = 0.15;
    angle = a;
    // angle = tan(y/x);
    // std::cout << angle<< std::endl;
    moveRes = 0.01;
}

void Meteor::draw(float z) const {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glEnable(GL_TEXTURE_2D);

    glColor4f(1,1,1,1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(x, y, z);

    glTexCoord2f(1, 1);
    glVertex3f(x+w, y, z);

    glTexCoord2f(1, 0);
    glVertex3f(x+w, y+h, z);

    glTexCoord2f(0, 0);
    glVertex3f(x, y+h, z);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Meteor::move() {
    x += moveRes*cos(toRads(angle));
    y += moveRes*sin(toRads(angle));
}
bool Meteor::contains(float a, float b) {
    return a > x && a < x+w && b > y && b < y+h;
}

bool Meteor::contains(float nX, float nY, float nW, float nH) {
    // std::cout << "hi" << std::endl;
    return x < nX + nW && x + w > nX && y < nY + nH && y + h > nY;
}

int Meteor::getType() const {
    return 2;
}
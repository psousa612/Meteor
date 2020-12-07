#include "Hearts.h"

Hearts::Hearts() : GUIEntity("images/heart.png", -1, 1, 1, 1) {
    this->x = 0;
    this->y = 0;
    w = .1;
    h = w;
}

Hearts::Hearts(float x, float y) : GUIEntity("images/heart.png", -1, 1, 1, 1) {
    this->x = x;
    this->y = y;
    w = 0.1;
    h = w;
}

void Hearts::draw(float z) const {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glEnable(GL_TEXTURE_2D);

    glColor4f(1,1,1,1);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(x, y, z);

    glTexCoord2f(1, 0);
    glVertex3f(x+w, y, z);

    glTexCoord2f(1, 1);
    glVertex3f(x+w, y+h, z);

    glTexCoord2f(0, 1);
    glVertex3f(x, y+h, z);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

bool Hearts::contains(float nX, float nY) {
    return false;
}
#include "Ammo.h"

Ammo::Ammo() : GUIEntity("images/projectile.png", -1, 1, 1, 1)  {
    this->x = 0;
    this->y = 0;
    w = 0.1;
    h = w;
    hidden = false;
}

Ammo::Ammo(float x, float y) : GUIEntity("images/projectile.png", -1, 1, 1, 1) {
    this->x = x;
    this->y = y;
    w = 0.1;
    h = w;
    hidden = false;
}

void Ammo::draw(float z ) const {
    if(hidden) {
        return;
    }

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

bool Ammo::contains(float, float) {
    return false;
}

int Ammo::getType() const {
    return 101;
}
#include "Projectile.h"
#include <iostream>

Projectile::Projectile() : GameEntity("images/projectile.png", -1, 1, 1, 1) {
    angle = 0;
    angleOffset = 0;
}

Projectile::Projectile(float x, float y, float angle) : GameEntity("images/projectile.png", -1, 1, 1, 3) {
    this->x = x;
    this->y = y;
    w = .05;
    h = .05;
    this->angle = angle;
    this->angleOffset = 45;
    moveRes = 0.015;

}
void Projectile::draw(float z) const {
    // glColor3f(1,0,0);
    // glBegin(GL_QUADS);
    // glVertex2f(x, y);
    // glVertex2f(x+w, y);
    // glVertex2f(x+w, y+h);
    // glVertex2f(x, y+h);
    // glEnd();

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glEnable(GL_TEXTURE_2D);

    glColor4f(1,1,1,1);
    glBegin(GL_POLYGON);
    // std::cout<<"_____"<<std::endl;
    for(int i = 0; i < 4; i++) {
        // std::cout << (i*90.0 + angle + angleOffset) << std::endl;
        switch(i) {
            case 2:
                glTexCoord2f(0, 0);
                break;

            case 3:
                glTexCoord2f(1, 0);
                break;

            case 0:
                glTexCoord2f(1, 1);
                break;

            case 1:
                glTexCoord2f(0, 1);
                break;
        }
        
        
        float currAngle = toRads((i*90.0 + angle + angleOffset));
        glVertex2f(w * cos(currAngle)+x, h * sin(currAngle)+y);
    }
    
    glEnd();
    glDisable(GL_TEXTURE_2D);
    // std::cout << "proj move" << std::endl;
}

void Projectile::move() {
    x += moveRes*cos(toRads(angle));
    y += moveRes*sin(toRads(angle));

    // std::cout << w << ", " << h << std::endl;
    // std::cout << (w * cos( angle)) << std::endl;
}

bool Projectile::contains(float x, float y) {
    return false;
}

int Projectile::getType() const {
    return 1;
}
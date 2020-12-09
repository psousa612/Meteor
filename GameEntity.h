#pragma once
#include "Entity.h"
#include <math.h>

class GameEntity: public Entity {
protected:
    GLuint texture_id;
    int texwidth, texheight;

    float x, y, w, h;
    float moveRes;

    float angle;
    double angleOffset;
    float angleMoveRes;

public:
    GameEntity(const char*, float, float, float, float);

    void draw(float) const;
    void move();

    void setX(float x);
    void setY(float y);

    float getX() const;
    float getY() const;
    float getW() const;
    float getH() const;
    float getAngle() const;

    bool contains(float, float) const;
    bool toDelete() const;
    float toRads(float) const;

    int getType() const;
};

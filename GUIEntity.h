#pragma once
#include "Entity.h"

class GUIEntity : public Entity {
protected:
    GLuint texture_id;
    int texwidth, texheight;

    float x, y, w, h;
    bool hidden;

public:
    GUIEntity(const char*, float, float, float, float);

    void draw(float) const;
    void move();
    bool contains(float, float) const;

    bool getHidden() const;
    bool setHidden(bool);

};
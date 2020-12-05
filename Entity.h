#if defined WIN32
#include <freeglut.h>
#include "../windows/SOIL.h"
#elif defined __APPLE__
#include <GLUT/glut.h>
#include "SOIL.h"
#else
#include <GL/freeglut.h>
#include "SOIL.h"
#endif

class Entity {
protected:
public:
    virtual void draw(float zindex = 1) const = 0;
    virtual void move() = 0;
    virtual bool contains(float, float) = 0;
    virtual ~Entity() {};
};
#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

class Entity {
protected:
    float x, y, w, h;
    float r, g, b;
    float moveRes;

public:
    Entity(){};
    virtual ~Entity(){}

    virtual void draw(float zindex = 1) const = 0;
    virtual void move() = 0;
    virtual bool checkCollision(float, float) = 0;

    float getX() {
        return x;
    }

    float getY() {
        return y;
    }
};
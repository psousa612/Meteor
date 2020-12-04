#include "Entity.h"
#include <math.h>

class PlayerShip : public Entity {
private:
    float angle;
    double angleOffset;
    float angleMoveRes;

public:
    PlayerShip();

    void draw(float z = 0) const;
    void move();

    //Move Functions, to be called by a GameManager object
    void moveForward();
    void moveBackwards();
    void turnLeft();
    void turnRight();

    float toRads(float degrees) const;

    bool checkCollision(float nX, float nY);
};
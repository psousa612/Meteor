#include "GameEntity.h"

class PlayerShip : public GameEntity {
public:
    PlayerShip();

    void draw(float z = 0) const;
    void move();

    //Move Functions, to be called by a GameManager object
    void moveForward();
    void moveBackwards();
    void turnLeft();
    void turnRight();

    bool contains(float nX, float nY);
};
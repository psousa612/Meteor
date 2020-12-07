#include "GameEntity.h"

class Projectile : public GameEntity {
public:
    Projectile();
    Projectile(float, float, float);

    void draw(float z = 0) const;
    void move();
    bool contains(float, float);
};
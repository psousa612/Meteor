#include "GameEntity.h"

class Meteor : public GameEntity {
public:
    Meteor();
    Meteor(float, float, float);

    void draw(float z = 0) const;
    void move();
    bool contains(float, float);
};
#include "Meteor.h"

Meteor::Meteor() : GameEntity("images/projectile.png", -1, 1, 1, 1) {

}

Meteor::Meteor(float, float, float) : GameEntity("images/met.png", -1, 1, 1, 1){

}

void Meteor::draw(float z) const {

}

void Meteor::move() {

}

bool Meteor::contains(float, float) {

}

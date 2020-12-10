#include "GUIEntity.h"

class Ammo : public GUIEntity {
public:
    Ammo();
    Ammo(float, float);

    void draw(float z = 0) const;
    bool contains(float, float);

    int getType() const;
};
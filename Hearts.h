#include "GUIEntity.h"

class Hearts : public GUIEntity {

public:
    Hearts();
    Hearts(float, float);

    void draw(float z = 0) const;
    bool contains(float, float);

    int getType() const;
};
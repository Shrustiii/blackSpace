#ifndef RESCUETARGET_H
#define RESCUETARGET_H

#include "GameObject.h"

class RescueTarget : public GameObject {
private:
    bool rescued;
    float pulseTime;

public:
    RescueTarget();
    RescueTarget(Vector2 startPos);

    void update(float deltaTime) override;
    void draw() override;

    bool isRescued() const;
    void rescue();
};

#endif

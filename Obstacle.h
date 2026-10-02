#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "GameObject.h"
#include "Constants.h"

class Obstacle : public GameObject {
private:
    Vector2 drift;
    Color color;

public:
    Obstacle();
    Obstacle(Vector2 startPos, float startRadius, Vector2 startDrift, Color startColor);

    void update(float deltaTime) override;
    void draw() override;
};

#endif

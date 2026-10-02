#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "GameObject.h"
#include "Constants.h"

class PlayerShip : public GameObject {
private:
    float speed;
    float fuel;
    float health;
    float angle;

public:
    PlayerShip();

    void update(float deltaTime) override;
    void draw() override;
    void resetForLevel();

    void reduceFuel(float amount);
    void reduceHealth(float amount);
    void refuel(float amount);

    float getFuel() const;
    float getHealth() const;
    float getAngle() const;
};

#endif

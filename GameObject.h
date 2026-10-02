#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "StandardIncludes.h"

class GameObject {
protected:
    Vector2 position;
    float radius;
    bool active;

public:
    GameObject(Vector2 startPos = {0.0f, 0.0f}, float startRadius = 10.0f)
        : position(startPos), radius(startRadius), active(true) {
    }

    virtual ~GameObject() {
    }

    virtual void update(float deltaTime) = 0;
    virtual void draw() = 0;

    Vector2 getPosition() const {
        return position;
    }

    float getRadius() const {
        return radius;
    }

    bool isActive() const {
        return active;
    }

    void setActive(bool value) {
        active = value;
    }

    void setPosition(Vector2 newPos) {
        position = newPos;
    }
};

#endif

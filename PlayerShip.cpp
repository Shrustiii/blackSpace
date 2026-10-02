#include "PlayerShip.h"

PlayerShip::PlayerShip() : GameObject({120.0f, screenHeight / 2.0f}, playerRadius) {
    speed = playerSpeed;
    fuel = maxFuel;
    health = maxHealth;
    angle = 0.0f;
}

void PlayerShip::update(float deltaTime) {
    if (fuel <= 0.0f || health <= 0.0f) {
        return;
    }

    Vector2 direction = {0.0f, 0.0f};

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        direction.y -= 1.0f;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        direction.y += 1.0f;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        direction.x -= 1.0f;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        direction.x += 1.0f;
    }

    if (direction.x != 0.0f || direction.y != 0.0f) {
        float length = sqrtf(direction.x * direction.x + direction.y * direction.y);

        if (length != 0.0f) {
            direction.x /= length;
            direction.y /= length;
        }

        position.x += direction.x * speed * deltaTime;
        position.y += direction.y * speed * deltaTime;

        angle = atan2f(direction.y, direction.x);
        fuel -= fuelDrainPerSecond * deltaTime;
    }

    if (position.x < radius) {
        position.x = radius;
    }
    if (position.x > screenWidth - radius) {
        position.x = screenWidth - radius;
    }
    if (position.y < hudPanelHeight + radius) {
        position.y = hudPanelHeight + radius;
    }
    if (position.y > screenHeight - radius) {
        position.y = screenHeight - radius;
    }

    if (fuel < 0.0f) {
        fuel = 0.0f;
    }
    if (health < 0.0f) {
        health = 0.0f;
    }
}

void PlayerShip::draw() {
    Vector2 nose = {
        position.x + cosf(angle) * 28.0f,
        position.y + sinf(angle) * 28.0f
    };

    Vector2 leftWing = {
        position.x + cosf(angle + 2.4f) * 22.0f,
        position.y + sinf(angle + 2.4f) * 22.0f
    };

    Vector2 rightWing = {
        position.x + cosf(angle - 2.4f) * 22.0f,
        position.y + sinf(angle - 2.4f) * 22.0f
    };

    Vector2 engine = {
        position.x - cosf(angle) * 16.0f,
        position.y - sinf(angle) * 16.0f
    };

    DrawTriangle(nose, leftWing, rightWing, SKYBLUE);
    DrawTriangleLines(nose, leftWing, rightWing, WHITE);
    DrawCircleV(position, 8.0f, WHITE);
    DrawCircleV(engine, 6.0f, ORANGE);
}

void PlayerShip::resetForLevel() {
    position = {120.0f, screenHeight / 2.0f};
    fuel = maxFuel;
    health = maxHealth;
    angle = 0.0f;
}

void PlayerShip::reduceFuel(float amount) {
    fuel -= amount;
    if (fuel < 0.0f) {
        fuel = 0.0f;
    }
}

void PlayerShip::reduceHealth(float amount) {
    health -= amount;
    if (health < 0.0f) {
        health = 0.0f;
    }
}

void PlayerShip::refuel(float amount) {
    fuel += amount;
    if (fuel > maxFuel) {
        fuel = maxFuel;
    }
}

float PlayerShip::getFuel() const {
    return fuel;
}

float PlayerShip::getHealth() const {
    return health;
}

float PlayerShip::getAngle() const {
    return angle;
}

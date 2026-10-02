#include "Obstacle.h"

Obstacle::Obstacle() : GameObject({0.0f, 0.0f}, 20.0f) {
    drift = {0.0f, 0.0f};
    color = GRAY;
}

Obstacle::Obstacle(Vector2 startPos, float startRadius, Vector2 startDrift, Color startColor)
    : GameObject(startPos, startRadius) {
    drift = startDrift;
    color = startColor;
}

void Obstacle::update(float deltaTime) {
    position.x += drift.x * deltaTime;
    position.y += drift.y * deltaTime;

    if (position.x < radius) {
        position.x = radius;
        drift.x *= -1.0f;
    }

    if (position.x > screenWidth - radius) {
        position.x = screenWidth - radius;
        drift.x *= -1.0f;
    }

    if (position.y < hudPanelHeight + radius) {
        position.y = hudPanelHeight + radius;
        drift.y *= -1.0f;
    }

    if (position.y > screenHeight - radius) {
        position.y = screenHeight - radius;
        drift.y *= -1.0f;
    }
}

void Obstacle::draw() {
    DrawCircleV(position, radius, color);
    DrawCircleLines((int)position.x, (int)position.y, radius, Fade(WHITE, 0.5f));

    for (int i = -1; i <= 1; i++) {
        DrawLine(
            (int)(position.x - radius / 2),
            (int)(position.y + i * 6),
            (int)(position.x + radius / 2),
            (int)(position.y - i * 5),
            DARKGRAY
        );
    }
}

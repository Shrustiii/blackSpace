#include "RescueTarget.h"

RescueTarget::RescueTarget() : GameObject({0.0f, 0.0f}, 18.0f) {
    rescued = false;
    pulseTime = 0.0f;
}

RescueTarget::RescueTarget(Vector2 startPos) : GameObject(startPos, 18.0f) {
    rescued = false;
    pulseTime = 0.0f;
}

void RescueTarget::update(float deltaTime) {
    pulseTime += deltaTime;
}

void RescueTarget::draw() {
    if (rescued) {
        DrawCircleV(position, radius, GREEN);
        DrawText("SAFE", (int)position.x - 18, (int)position.y - 6, 16, WHITE);
    } else {
        float pulseRadius = radius + sinf(pulseTime * 4.0f) * 4.0f;
        DrawCircleLines((int)position.x, (int)position.y, pulseRadius + 8.0f, RED);
        DrawCircleV(position, radius, MAROON);
        DrawText("SOS", (int)position.x - 14, (int)position.y - 7, 18, WHITE);
    }
}

bool RescueTarget::isRescued() const {
    return rescued;
}

void RescueTarget::rescue() {
    rescued = true;
}

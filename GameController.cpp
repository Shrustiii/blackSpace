#include "GameController.h"

namespace {
void drawCenteredText(const char* text, int y, int size, Color color) {
    DrawText(text, (screenWidth - MeasureText(text, size)) / 2, y, size, color);
}
}

GameController::GameController() {
    currentState = gameState::menu;
    currentLevel = 1;
    rescuedCount = 0;
    score = 0;
    missionTimer = 0.0f;
    collisionFlashTimer = 0.0f;

    initializeLevel();
}

void GameController::initializeLevel() {
    player.resetForLevel();
    rescuedCount = 0;
    missionTimer = 0.0f;
    collisionFlashTimer = 0.0f;

    missionLog.clear();
    missionLog.addMessage("Mission started.");
    missionLog.addMessage("Rescue all stranded crews.");

    for (int i = 0; i < obstacleCountPerLevel; i++) {
        float x = (float)GetRandomValue(260, screenWidth - 60);
        float y = (float)GetRandomValue((int)hudPanelHeight + 60, screenHeight - 60);
        float radius = (float)GetRandomValue(18, 34);
        float driftX = (float)GetRandomValue(-70, 70);
        float driftY = (float)GetRandomValue(-70, 70);

        Color shade;
        if (i % 3 == 0) {
            shade = GRAY;
        } else if (i % 3 == 1) {
            shade = BROWN;
        } else {
            shade = DARKGRAY;
        }

        obstacles[i] = Obstacle({x, y}, radius, {driftX, driftY}, shade);
    }

    for (int i = 0; i < rescueTargetsPerLevel; i++) {
        float x = (float)GetRandomValue(screenWidth / 2, screenWidth - 80);
        float y = (float)GetRandomValue((int)hudPanelHeight + 80, screenHeight - 80);
        targets[i] = RescueTarget({x, y});
    }
}

void GameController::update() {
    // Avoid large simulation jumps after the window stalls or loses focus.
    float deltaTime = fminf(GetFrameTime(), 0.05f);

    switch (currentState) {
        case gameState::menu:
            updateMenu();
            break;
        case gameState::playing:
            updatePlaying(deltaTime);
            break;
        case gameState::paused:
            updatePaused();
            break;
        case gameState::levelComplete:
            updateLevelComplete();
            break;
        case gameState::gameWon:
            updateGameWon();
            break;
        case gameState::gameLost:
            updateGameLost();
            break;
    }
}

void GameController::updateMenu() {
    if (IsKeyPressed(KEY_ENTER)) {
        currentLevel = 1;
        score = 0;
        initializeLevel();
        currentState = gameState::playing;
    }
}

void GameController::updatePlaying(float deltaTime) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        currentState = gameState::paused;
        return;
    }

    missionTimer += deltaTime;

    if (collisionFlashTimer > 0.0f) {
        collisionFlashTimer -= deltaTime;
        if (collisionFlashTimer < 0.0f) {
            collisionFlashTimer = 0.0f;
        }
    }

    player.update(deltaTime);

    for (int i = 0; i < obstacleCountPerLevel; i++) {
        obstacles[i].update(deltaTime);
    }

    for (int i = 0; i < rescueTargetsPerLevel; i++) {
        targets[i].update(deltaTime);
    }

    checkObstacleCollisions(deltaTime);
    handleRescueInteraction();

    if (player.getFuel() <= 0.0f || player.getHealth() <= 0.0f) {
        missionLog.addMessage("Mission failed.");
        currentState = gameState::gameLost;
        return;
    }

    if (allTargetsRescued()) {
        int timeBonus = (int)(200.0f - missionTimer * 5.0f);
        if (timeBonus < 0) {
            timeBonus = 0;
        }

        score += 300 + timeBonus;
        currentState = gameState::levelComplete;
    }
}

void GameController::updatePaused() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        currentState = gameState::playing;
    }

    if (IsKeyPressed(KEY_M)) {
        currentState = gameState::menu;
    }
}

void GameController::updateLevelComplete() {
    if (IsKeyPressed(KEY_ENTER)) {
        currentLevel++;

        if (currentLevel > totalLevels) {
            currentState = gameState::gameWon;
        } else {
            initializeLevel();
            currentState = gameState::playing;
        }
    }
}

void GameController::updateGameWon() {
    if (IsKeyPressed(KEY_ENTER)) {
        currentState = gameState::menu;
    }
}

void GameController::updateGameLost() {
    if (IsKeyPressed(KEY_ENTER)) {
        currentState = gameState::menu;
    }
}

void GameController::handleRescueInteraction() {
    if (!IsKeyPressed(KEY_SPACE)) {
        return;
    }

    for (int i = 0; i < rescueTargetsPerLevel; i++) {
        if (!targets[i].isRescued()) {
            bool closeEnough = CollisionHelper::circleToCircle(
                player.getPosition(),
                rescueInteractRange,
                targets[i].getPosition(),
                targets[i].getRadius()
            );

            if (closeEnough) {
                targets[i].rescue();
                rescuedCount++;
                score += 100;
                player.refuel(12.0f);
                missionLog.addMessage("Crew rescued successfully.");
                break;
            }
        }
    }
}

void GameController::checkObstacleCollisions(float deltaTime) {
    for (int i = 0; i < obstacleCountPerLevel; i++) {
        if (CollisionHelper::circleToCircle(
                player.getPosition(),
                player.getRadius(),
                obstacles[i].getPosition(),
                obstacles[i].getRadius())) {
            player.reduceHealth(obstacleDamagePerSecond * deltaTime);
            player.reduceFuel(collisionFuelPenaltyPerSecond * deltaTime);
            collisionFlashTimer = 0.15f;
        }
    }
}

bool GameController::allTargetsRescued() const {
    for (int i = 0; i < rescueTargetsPerLevel; i++) {
        if (!targets[i].isRescued()) {
            return false;
        }
    }
    return true;
}

void GameController::draw() {
    drawBackground();

    switch (currentState) {
        case gameState::menu:
            drawMenu();
            break;
        case gameState::playing:
            drawPlaying();
            break;
        case gameState::paused:
            drawPlaying();
            drawPaused();
            break;
        case gameState::levelComplete:
            drawPlaying();
            drawLevelComplete();
            break;
        case gameState::gameWon:
            drawGameWon();
            break;
        case gameState::gameLost:
            drawPlaying();
            drawGameLost();
            break;
    }
}

void GameController::drawBackground() {
    int currentWidth = screenWidth;
    int currentHeight = screenHeight;

    ClearBackground(Color{8, 12, 28, 255});

    for (int i = 0; i < 180; i++) {
        int starX = (i * 91) % currentWidth;
        int starY = ((i * 47) % (currentHeight - 40)) + 40;
        DrawCircle(starX, starY, (i % 3) + 1, Fade(WHITE, 0.7f));
    }

    DrawCircle(currentWidth - 170, 170, 70, Fade(BLUE, 0.18f));
    DrawCircle(currentWidth - 170, 170, 48, Fade(SKYBLUE, 0.35f));

    DrawRing(Vector2{190, (float)(currentHeight - 110)}, 55, 85, 0, 360, 80, Fade(PURPLE, 0.25f));

    if (collisionFlashTimer > 0.0f) {
        DrawRectangle(0, 0, currentWidth, currentHeight, Fade(RED, 0.20f));
    }
}

void GameController::drawMenu() {
    int currentWidth = screenWidth;
    int currentHeight = screenHeight;

    int boxWidth = 780;
    int boxHeight = 270;
    int boxX = (currentWidth - boxWidth) / 2;
    int boxY = currentHeight / 2 - 70;

    drawCenteredText("BLACKSPACE", 140, 64, WHITE);
    drawCenteredText("2D Space Rescue Mission", 225, 28, SKYBLUE);

    DrawRectangleRounded(
        Rectangle{(float)boxX, (float)boxY, (float)boxWidth, (float)boxHeight},
        0.12f, 12, Fade(BLACK, 0.60f)
    );

    DrawText("Move: WASD / Arrow Keys", boxX + 80, boxY + 45, 26, LIGHTGRAY);
    DrawText("Rescue: SPACE", boxX + 80, boxY + 95, 26, LIGHTGRAY);
    DrawText("Pause: ESC    Fullscreen: F", boxX + 80, boxY + 145, 26, LIGHTGRAY);
    drawCenteredText("Rescue every crew before your fuel or health runs out.", boxY + 210, 22, GOLD);

    drawCenteredText("Press ENTER to start", boxY + boxHeight + 70, 30, GREEN);
}

void GameController::drawPlaying() {
    for (int i = 0; i < obstacleCountPerLevel; i++) {
        obstacles[i].draw();
    }

    for (int i = 0; i < rescueTargetsPerLevel; i++) {
        targets[i].draw();

        if (!targets[i].isRescued()) {
            bool closeEnough = CollisionHelper::circleToCircle(
                player.getPosition(),
                rescueInteractRange,
                targets[i].getPosition(),
                targets[i].getRadius()
            );

            if (closeEnough) {
                DrawText(
                    "PRESS SPACE TO RESCUE",
                    (int)targets[i].getPosition().x - 95,
                    (int)targets[i].getPosition().y - 42,
                    18,
                    YELLOW
                );
            }
        }
    }

    player.draw();

    hud.draw(
        player,
        currentLevel,
        rescuedCount,
        rescueTargetsPerLevel,
        score,
        missionTimer,
        missionLog
    );
}

void GameController::drawPaused() {
    int currentWidth = screenWidth;
    int currentHeight = screenHeight;

    DrawRectangle(0, 0, currentWidth, currentHeight, Fade(BLACK, 0.45f));
    DrawRectangleRounded(Rectangle{(float)(currentWidth / 2 - 225), (float)(currentHeight / 2 - 90), 450, 180},
                         0.15f, 10, Fade(DARKBLUE, 0.8f));
    drawCenteredText("PAUSED", currentHeight / 2 - 55, 40, WHITE);
    drawCenteredText("ESC - Resume", currentHeight / 2 + 5, 24, SKYBLUE);
    drawCenteredText("M - Return to Menu", currentHeight / 2 + 40, 24, LIGHTGRAY);
}

void GameController::drawLevelComplete() {
    int currentWidth = screenWidth;
    int currentHeight = screenHeight;

    DrawRectangle(0, 0, currentWidth, currentHeight, Fade(BLACK, 0.45f));
    DrawRectangleRounded(Rectangle{(float)(currentWidth / 2 - 250), (float)(currentHeight / 2 - 110), 500, 220},
                         0.15f, 10, Fade(DARKGREEN, 0.82f));
    drawCenteredText("LEVEL COMPLETE", currentHeight / 2 - 55, 40, WHITE);
    DrawText(TextFormat("Level %d cleared", currentLevel), currentWidth / 2 - 90, currentHeight / 2, 24, GOLD);
    drawCenteredText(currentLevel == totalLevels ? "Press ENTER to finish" : "Press ENTER for next mission",
                     currentHeight / 2 + 55, 26, SKYBLUE);
}

void GameController::drawGameWon() {
    int currentWidth = screenWidth;
    int currentHeight = screenHeight;

    drawCenteredText("ALL MISSIONS COMPLETED", currentHeight / 2 - 120, 52, GREEN);
    DrawText(TextFormat("Final Score: %d", score), currentWidth / 2 - 110, currentHeight / 2 - 20, 34, GOLD);
    drawCenteredText("The trapped crews were rescued safely.", currentHeight / 2 + 50, 28, LIGHTGRAY);
    drawCenteredText("Press ENTER to return to menu", currentHeight / 2 + 140, 28, SKYBLUE);
}

void GameController::drawGameLost() {
    int currentWidth = screenWidth;
    int currentHeight = screenHeight;

    DrawRectangle(0, 0, currentWidth, currentHeight, Fade(BLACK, 0.5f));
    DrawRectangleRounded(Rectangle{(float)(currentWidth / 2 - 240), (float)(currentHeight / 2 - 105), 480, 210},
                         0.15f, 10, Fade(MAROON, 0.85f));
    drawCenteredText("MISSION FAILED", currentHeight / 2 - 55, 42, WHITE);
    drawCenteredText("Ship health or fuel reached zero.", currentHeight / 2 + 5, 24, LIGHTGRAY);
    drawCenteredText("Press ENTER to return to menu", currentHeight / 2 + 55, 24, SKYBLUE);
}

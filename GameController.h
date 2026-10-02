#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "StandardIncludes.h"
#include "Constants.h"
#include "GameTypes.h"
#include "PlayerShip.h"
#include "Obstacle.h"
#include "RescueTarget.h"
#include "HUD.h"
#include "MissionLog.h"
#include "CollisionHelper.h"

class GameController {
private:
    gameState currentState;
    PlayerShip player;
    Obstacle obstacles[obstacleCountPerLevel];
    RescueTarget targets[rescueTargetsPerLevel];
    HUD hud;
    MissionLog missionLog;

    int currentLevel;
    int rescuedCount;
    int score;
    float missionTimer;
    float collisionFlashTimer;

    void initializeLevel();
    void updateMenu();
    void updatePlaying(float deltaTime);
    void updatePaused();
    void updateLevelComplete();
    void updateGameWon();
    void updateGameLost();

    void drawBackground();
    void drawMenu();
    void drawPlaying();
    void drawPaused();
    void drawLevelComplete();
    void drawGameWon();
    void drawGameLost();

    void handleRescueInteraction();
    void checkObstacleCollisions(float deltaTime);
    bool allTargetsRescued() const;

public:
    GameController();
    void update();
    void draw();
};

#endif

#ifndef CONSTANTS_H
#define CONSTANTS_H

const int screenWidth = 1280;
const int screenHeight = 720;
const int targetFps = 60;

const int totalLevels = 3;
const int rescueTargetsPerLevel = 3;
const int obstacleCountPerLevel = 8;

const float playerRadius = 24.0f;
const float playerSpeed = 260.0f;
const float maxFuel = 100.0f;
const float maxHealth = 100.0f;
const float fuelDrainPerSecond = 5.5f;
const float obstacleDamagePerSecond = 35.0f;
const float collisionFuelPenaltyPerSecond = 12.0f;
const float rescueInteractRange = 55.0f;

const float hudPanelHeight = 95.0f;

#endif

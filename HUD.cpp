#include "HUD.h"
#include "Constants.h"

void HUD::draw(const PlayerShip& player,
               int currentLevel,
               int rescuedCount,
               int totalTargets,
               int score,
               float missionTime,
               const MissionLog& log) {
    int currentWidth = screenWidth;

    DrawRectangle(0, 0, currentWidth, (int)hudPanelHeight, Fade(BLACK, 0.82f));
    DrawLine(0, (int)hudPanelHeight, currentWidth, (int)hudPanelHeight, SKYBLUE);

    DrawText("BLACKSPACE", 20, 14, 26, WHITE);
    DrawText(TextFormat("LEVEL: %d", currentLevel), 20, 52, 18, LIGHTGRAY);

    DrawText(TextFormat("RESCUES: %d / %d", rescuedCount, totalTargets), 250, 14, 18, GREEN);
    DrawText(TextFormat("SCORE: %d", score), 250, 52, 18, GOLD);

    DrawText(TextFormat("TIME: %.1f", missionTime), 470, 14, 18, SKYBLUE);

    int barSectionX = 620;

    DrawText("HEALTH", barSectionX, 14, 18, WHITE);
    DrawRectangle(barSectionX + 120, 16, 180, 18, DARKGRAY);
    DrawRectangle(barSectionX + 120, 16,
                  (int)(180.0f * (player.getHealth() / maxHealth)), 18, LIME);

    DrawText("FUEL", barSectionX, 52, 18, WHITE);
    DrawRectangle(barSectionX + 120, 54, 180, 18, DARKGRAY);
    DrawRectangle(barSectionX + 120, 54,
                  (int)(180.0f * (player.getFuel() / maxFuel)), 18, ORANGE);

    log.draw(currentWidth - 280, 14);
}

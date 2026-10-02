#ifndef HUD_H
#define HUD_H

#include "StandardIncludes.h"
#include "PlayerShip.h"
#include "MissionLog.h"

class HUD
{
public:
    void draw(const PlayerShip &player,
              int currentLevel,
              int rescuedCount,
              int totalTargets,
              int score,
              float missionTime,
              const MissionLog &log);
};

#endif

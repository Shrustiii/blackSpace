#ifndef COLLISIONHELPER_H
#define COLLISIONHELPER_H

#include "StandardIncludes.h"

class CollisionHelper {
public:
    static bool circleToCircle(Vector2 firstPos, float firstRadius, Vector2 secondPos, float secondRadius) {
        return CheckCollisionCircles(firstPos, firstRadius, secondPos, secondRadius);
    }

    static bool circleToRectangle(Vector2 circlePos, float radius, Rectangle rect) {
        return CheckCollisionCircleRec(circlePos, radius, rect);
    }
};

#endif

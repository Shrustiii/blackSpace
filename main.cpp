#include "StandardIncludes.h"
#include "Constants.h"
#include "GameController.h"

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "BlackSpace"); // creates game window
    SetWindowMinSize(640, 360);
    SetExitKey(0);   // ESC works for pause instead of closing the game.

    SetTargetFPS(targetFps);
    SetRandomSeed(static_cast<unsigned int>(time(nullptr)));

    // Draw in a fixed game space, then scale uniformly to any window size.
    RenderTexture2D scene = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(scene.texture, TEXTURE_FILTER_BILINEAR);

    GameController gameController;

    while (!WindowShouldClose()) {  // game loop
        if (IsKeyPressed(KEY_F)) {
            ToggleFullscreen();
        }

        gameController.update();

        BeginTextureMode(scene);
        gameController.draw();
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);
        float scale = fminf(static_cast<float>(GetScreenWidth()) / screenWidth,
                            static_cast<float>(GetScreenHeight()) / screenHeight);
        Rectangle destination = {
            (GetScreenWidth() - screenWidth * scale) / 2.0f,
            (GetScreenHeight() - screenHeight * scale) / 2.0f,
            screenWidth * scale, screenHeight * scale
        };
        DrawTexturePro(scene.texture,
                       {0, 0, static_cast<float>(screenWidth), -static_cast<float>(screenHeight)},
                       destination, {0, 0}, 0, WHITE);
        EndDrawing();
    }

    UnloadRenderTexture(scene);
    CloseWindow();
    return 0;
}

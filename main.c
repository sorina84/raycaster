#include "raylib.h"
#include <math.h>
#include "map.h"
#include "player.h"
#include "renderer.h"

typedef enum { STATE_3D, STATE_2D_EDIT } GameMode;

int main(void)
{
    const int screenWidth  = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "BP Project - Final Version");
    SetTargetFPS(60);

    Player player = PlayerCreate(2.5f * TILE, 1.5f * TILE, 8.0f, 150.0f);
    GameMode currentMode = STATE_3D;
    HideCursor();

    while (!WindowShouldClose())
    {   
        float deltaTime = GetFrameTime();

        if (IsKeyPressed(KEY_M)) {
            currentMode = (currentMode == STATE_3D) ? STATE_2D_EDIT : STATE_3D;
            if (currentMode == STATE_2D_EDIT) ShowCursor(); 
            else HideCursor();
        }

        if (currentMode == STATE_3D) {
            PlayerUpdate(&player, deltaTime);
        } 
        else {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                int mX = GetMouseX() / TILE;
                int mY = GetMouseY() / TILE;

                if (mX >= 0 && mX < MAP_W && mY >= 0 && mY < MAP_H) {
                    int currentCell = MapGetCell(mX, mY);
                    MapSetCell(mX, mY, currentCell == 0 ? 1 : 0);
                }
            }

            if (IsKeyPressed(KEY_S)) {
                MapSaveToFile("map.bin");
            }
            if (IsKeyPressed(KEY_L)) {
                MapLoadFromFile("map.bin");
            }
        }

        BeginDrawing();
            ClearBackground(BLACK);

            if (currentMode == STATE_3D) {
                Render3DScene(&player);
                DrawFPS(10, 10);
            } else {
                Draw2DMap();
                PlayerDraw(&player);
                DrawText("EDIT MODE: [L-Click] Toggle Wall | [S] Save | [L] Load", 10, screenHeight - 30, 20, RAYWHITE);
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
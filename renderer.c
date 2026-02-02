#include "renderer.h"
#include "map.h"
#include <math.h>
#include "raylib.h"

void Render3DScene(const Player *player) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    DrawRectangle(0, 0, screenWidth, screenHeight / 2, SKYBLUE);
    DrawRectangle(0, screenHeight / 2, screenWidth, screenHeight / 2, DARKGREEN);

    for (int x = 0; x < screenWidth; x++) {
        double cameraX = 2.0 * x / (double)screenWidth - 1.0;
        double rayDirX = player->dir.x + player->plane.x * cameraX;
        double rayDirY = player->dir.y + player->plane.y * cameraX;

        int mapX = (int)(player->pos.x / TILE);
        int mapY = (int)(player->pos.y / TILE);

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

        int stepX, stepY;
        double sideDistX, sideDistY;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (player->pos.x / TILE - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player->pos.x / TILE) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (player->pos.y / TILE - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player->pos.y / TILE) * deltaDistY;
        }

        int hit = 0;
        int side = 0;
        int guard = 0;
        while (!hit && guard++ < 2048) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (MapGetCell(mapX, mapY) == 1) hit = 1;
        }

        double perpWallDist;
        if (side == 0) perpWallDist = (sideDistX - deltaDistX);
        else          perpWallDist = (sideDistY - deltaDistY);

        if (perpWallDist <= 0.0001) perpWallDist = 0.0001;

        int lineHeight = (int)(screenHeight / perpWallDist);

        int drawStart = (-lineHeight / 2) + (screenHeight / 2);
        if (drawStart < 0) drawStart = 0;

        int drawEnd = (lineHeight / 2) + (screenHeight / 2);
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        Color color = GRAY;
        if (side == 1) color = DARKGRAY;

        DrawLine(x, drawStart, x, drawEnd, color);
    }
}
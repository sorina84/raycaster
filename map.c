#include "raylib.h"
#include "map.h"
#include <stdio.h>

static int map_world[MAP_H][MAP_W] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,0,1},
    {1,0,1,0,0,0,1,0,0,1},
    {1,0,0,0,1,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1},
};

int MapGetCell(int x, int y) {
    if (x < 0 || x >= MAP_W || y < 0 || y >= MAP_H) return 1;
    return map_world[y][x];
}

void MapSetCell(int x, int y, int value) {
    if (x >= 0 && x < MAP_W && y >= 0 && y < MAP_H) {
        map_world[y][x] = value;
    }
}

void MapSaveToFile(const char* filename) {
    FILE* f = fopen(filename, "wb");
    if (!f) return;
    fwrite(map_world, sizeof(int), MAP_W * MAP_H, f);
    fclose(f);
}

void MapLoadFromFile(const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) return;
    fread(map_world, sizeof(int), MAP_W * MAP_H, f);
    fclose(f);
}

void Draw2DMap(void) {
    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            Rectangle cell = (Rectangle){ x * TILE, y * TILE, TILE, TILE };
            if (map_world[y][x] == 1)
                DrawRectangleRec(cell, GRAY);
            else
                DrawRectangleLinesEx(cell, 1, DARKGRAY);
        }
    }
}

int MapIsInside(float x, float y) {
    return (x >= 0 && y >= 0 && x < MAP_W * TILE && y < MAP_H * TILE);
}

int MapIsWallAt(float x, float y) {
    if (!MapIsInside(x, y)) return 1;
    int mx = (int)(x / TILE);
    int my = (int)(y / TILE);
    return (map_world[my][mx] == 1);
}

int MapCircleCollides(float x, float y, float r) {
    if (MapIsWallAt(x + r, y)) return 1;
    if (MapIsWallAt(x - r, y)) return 1;
    if (MapIsWallAt(x, y + r)) return 1;
    if (MapIsWallAt(x, y - r)) return 1;

    if (MapIsWallAt(x + r, y + r)) return 1;
    if (MapIsWallAt(x - r, y + r)) return 1;
    if (MapIsWallAt(x + r, y - r)) return 1;
    if (MapIsWallAt(x - r, y - r)) return 1;

    return 0;
}
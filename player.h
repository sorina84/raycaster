#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct Player {
    Vector2 pos;
    Vector2 dir;
    Vector2 plane;
    float radius;
    float speed;
    float rotSpeed;
} Player;

Player PlayerCreate(float x, float y, float radius, float speed);
void PlayerUpdate(Player *player, float deltaTime);
void PlayerDraw(const Player *p);

#endif
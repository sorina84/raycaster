#include "player.h"
#include "raymath.h"
#include "map.h"
#include <math.h>

Player PlayerCreate(float x, float y, float radius, float speed)
{
    Player p;
    p.pos = (Vector2){ x, y };
    p.dir = (Vector2){ 1.0f, 0.0f };
    p.plane = (Vector2){ 0.0f, 0.66f };
    p.radius = radius;
    p.speed = speed;
    p.rotSpeed = 2.5f;
    return p;
}

void PlayerUpdate(Player *player, float deltaTime)
{
    if (IsKeyDown(KEY_RIGHT)) {
        float angle = -player->rotSpeed * deltaTime;
        float oldDirX = player->dir.x;
        player->dir.x = player->dir.x * cosf(angle) - player->dir.y * sinf(angle);
        player->dir.y = oldDirX * sinf(angle) + player->dir.y * cosf(angle);
    
        float oldPlaneX = player->plane.x;
        player->plane.x = player->plane.x * cosf(angle) - player->plane.y * sinf(angle);
        player->plane.y = oldPlaneX * sinf(angle) + player->plane.y * cosf(angle);
    }

    if (IsKeyDown(KEY_LEFT)) {
        float angle = player->rotSpeed * deltaTime;
        float oldDirX = player->dir.x;
        player->dir.x = player->dir.x * cosf(angle) - player->dir.y * sinf(angle);
        player->dir.y = oldDirX * sinf(angle) + player->dir.y * cosf(angle);
        
        float oldPlaneX = player->plane.x;
        player->plane.x = player->plane.x * cosf(angle) - player->plane.y * sinf(angle);
        player->plane.y = oldPlaneX * sinf(angle) + player->plane.y * cosf(angle);
    }

    Vector2 move = { 0, 0 };

    if (IsKeyDown(KEY_W)) { 
        move.x += player->dir.x; 
        move.y += player->dir.y; 
    }
    if (IsKeyDown(KEY_S)) { 
        move.x -= player->dir.x; 
        move.y -= player->dir.y; 
    }
 
    Vector2 right = { player->dir.y, -player->dir.x };
    if (IsKeyDown(KEY_D)) { 
        move.x += right.x; 
        move.y += right.y; 
    }
    if (IsKeyDown(KEY_A)) { 
        move.x -= right.x; 
        move.y -= right.y; 
    }

    if (move.x != 0 || move.y != 0) 
    {
        move = Vector2Normalize(move);

        float nextX = player->pos.x + move.x * player->speed * deltaTime;
        if (!MapCircleCollides(nextX, player->pos.y, player->radius))
            player->pos.x = nextX;

        float nextY = player->pos.y + move.y * player->speed * deltaTime;
        if (!MapCircleCollides(player->pos.x, nextY, player->radius))
            player->pos.y = nextY;
    }
}

void PlayerDraw(const Player *p){
    DrawCircleV(p->pos, p->radius, RED);

    DrawLine(
        (int)p->pos.x, (int)p->pos.y,
        (int)(p->pos.x + p->dir.x * 20),
        (int)(p->pos.y + p->dir.y * 20),
        BLUE
    );
}
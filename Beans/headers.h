#pragma once

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern float SHIP_SPEED;
extern float SHIP_HEALTH;
extern float SHIP_INVINC_TIME;

extern float BULLET_SPEED;
extern float BULLET_TIME;
extern float BULLET_DAMAGE;

extern float STARS_SPEED;
extern float BEANS_TIME;

enum Scene
{
    SceneMenu, SceneGame
};

int RandomRange(int min, int max);
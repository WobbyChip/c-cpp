#include "headers.h"
#include "raylib.h"
#include <stdlib.h>
#include "game.cpp"

int SCREEN_WIDTH = 480;
int SCREEN_HEIGHT = 800;

float SHIP_SPEED = 7.0f;
float SHIP_HEALTH = 1.0f; //Default is 100
float SHIP_INVINC_TIME = 3.0f;

float BULLET_SPEED = 15.0f;
float BULLET_TIME = 0.1f;
float BULLET_DAMAGE = 101.0f;

float STARS_SPEED = 0.5f;
float BEANS_TIME = 1.0f;


int RandomRange(int min, int max)
{
    return (rand() % (max + 1 - min)) + min;
}


int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Beans");
    SetTargetFPS(60);
    InitAudioDevice();
    Game game = Game(60, 60);

    while (!WindowShouldClose())
    {
        game.Update();

        BeginDrawing();
            ClearBackground(BLACK);
            game.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
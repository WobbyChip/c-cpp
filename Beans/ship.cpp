#include "raylib.h"
#include "headers.h"


class Ship {
    public:
        Texture2D texture;
        Texture2D texture_turbo;
        Texture2D texture_invincible;
        Vector2 pos;
        Vector2 velocity;
        Rectangle rect;
        float scale;
        float rotation;
        float speed;
        float health;
        float invincibleTime;
        bool invincible;

        Ship()
        {
            texture = LoadTexture("resources/ship.png");
            texture_turbo = LoadTexture("resources/ship_turbo.png");
            texture_invincible = LoadTexture("resources/ship_invincible.png");
            pos = (Vector2){ (float)GetScreenWidth()/2, (float)GetScreenHeight()/2 };
            rect = { pos.x-texture.width/2, pos.y-texture.height/2, (float)texture.width, (float)texture.height };
            invincibleTime = GetTime();
            scale = 1.1f;
            rotation = 0.0f;
            speed = SHIP_SPEED;
            health = SHIP_HEALTH;
            invincible = false;
            velocity = (Vector2){ 0, 0 };
        }

        void Move()
        {
            if (GetTime() >= invincibleTime) {
                invincible = false;
            }

            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(68)) velocity.x = +speed;
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(65)) velocity.x = -speed;
            if (IsKeyDown(KEY_UP) || IsKeyDown(87)) velocity.y = -speed;
            if (IsKeyDown(KEY_DOWN) || IsKeyDown(83)) velocity.y = +speed;

            pos.x += velocity.x;
            velocity.x /= 1.2f;

            pos.y += velocity.y;
            velocity.y /= 1.2f;

            if (pos.x > GetScreenWidth()) pos.x = GetScreenWidth();
            if (pos.x < 0) pos.x = 0;
            if (pos.y > GetScreenHeight()) pos.y = GetScreenHeight();
            if (pos.y < 0) pos.y = 0;

            rect = { pos.x-texture.width/2, pos.y-texture.height/2, (float)texture.width, (float)texture.height };
        }

        void Draw()
        {
            Vector2 position = (Vector2){ (float)(pos.x - texture.width/2*scale), (float)(pos.y - texture.height/2*scale) };

            DrawTextureEx(texture, position, 0.0f, scale, WHITE);
            if (IsKeyDown(KEY_UP) || IsKeyDown(87)) DrawTextureEx(texture_turbo, position, 0.0f, scale, WHITE);
            if (invincible && (int(100*(GetTime()-(int)GetTime())) >= 50)) DrawTextureEx(texture_invincible, position, 0.0f, scale, WHITE);
        }
};
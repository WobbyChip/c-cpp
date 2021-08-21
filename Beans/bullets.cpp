#include "raylib.h"
#include <vector>

using std::vector;


class Bullet {
    public:
        Vector2 pos;
        Rectangle rect;
        float speedY;
        float damage;

        Bullet(float x, float y, float s, float d)
        {
            pos = (Vector2){ x, y };
            speedY = s;
            damage = d;
        }
};


class Bullets {
    public:
        Texture2D texture;
        Sound sfx;
        float speedY;
        float damage;
        float time;
        vector<Bullet> bullets;

        Bullets()
        {
            time = GetTime();
            texture = LoadTexture("resources/bullet.png");
            sfx = LoadSound("resources/shot.wav");
        }

        void SpawnBullet(float x, float y, float s, float d)
        {
            if (GetTime() < time+BULLET_TIME) { return; }
            time = GetTime();
            Bullet bullet = Bullet(x, y, s, d);
            bullets.push_back(bullet);
            PlaySound(sfx);
        }

        void DeleteBullet(int index)
        {
            bullets.erase(bullets.begin() + index);
        }

        void Move() {
            for (int i = 0; i < (int)bullets.size(); i++)
            {
                bullets[i].pos.y -= bullets[i].speedY;
                bullets[i].rect = { bullets[i].pos.x-texture.width/2, bullets[i].pos.y-texture.height/2, (float)texture.width, (float)texture.height };
                if (bullets[i].pos.y < 0) { bullets.erase(bullets.begin() + i); }
            }
        }

        void Draw() {
            for (int i = 0; i < (int)bullets.size(); i++)
            {
                Vector2 position = (Vector2){ (float)(bullets[i].pos.x - texture.width/2), (float)(bullets[i].pos.y - texture.height/2) };
                DrawTextureEx(texture, position, 0.0f, 1.0f, WHITE);
            }
        }
};
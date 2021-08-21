#include "raylib.h"
#include <vector>

using std::vector;


class Bean {
    public:
        Vector2 pos;
        Vector2 velocity;
        bool damaged;
        int scale;
        float radius;
        float health;
        float rotation;
        float rotationSpeed;

        Bean(int x, int y, int size, Texture2D* texture)
        {
            pos = (Vector2){ (float)x, (float)y };
            velocity = (Vector2){ 0.0f, 0.1f*(float)RandomRange(10, 30) };
            damaged = false;
            scale = size;
            radius = (((*texture).width+(*texture).height)/2)*scale/2;
            health = 100.0f*size;
            rotation = 0.0f;
            rotationSpeed = 0.05f*RandomRange(-10, 10);
        }
};


class Beans {
    public:
        Sound sfx;
        Texture2D texture;
        Texture2D damaged;
        vector<Bean> beans;
        float time;

        Beans()
        {
            time = GetTime();
            texture = LoadTexture("resources/beans.png");
            damaged = LoadTexture("resources/beans_damaged.png");
            sfx = LoadSound("resources/hit.wav");
        }

        void SpawnBean()
        {
            if (GetTime() < time) { return; }
            time = GetTime()+0.1f*RandomRange(0, 10);
            int scale = RandomRange(1, 3);
            Bean bean = Bean(RandomRange(0, GetScreenWidth()), -(texture.height*scale/2), scale, &texture);
            beans.push_back(bean);
        }

        bool CollideRect(int i, Rectangle rect)
        {
            return CheckCollisionCircleRec(beans[i].pos, beans[i].radius, rect);
        }

        int DamageBean(int i, int damage)
        {
            PlaySound(sfx);
            beans[i].damaged = true;
            beans[i].health -= damage;

            if (beans[i].health < 0.0f) {
                int scale = beans[i].scale;

                if (scale > 1) {
                    Bean beanL = Bean(beans[i].pos.x, beans[i].pos.y, scale-1, &texture);
                    beanL.rotationSpeed = beans[i].rotationSpeed*3.0f;
                    beanL.velocity = (Vector2){ 0.1f*RandomRange(-100, -10), beans[i].velocity.y };
                    beans.push_back(beanL);

                    Bean beanR = Bean(beans[i].pos.x, beans[i].pos.y, scale-1, &texture);
                    beanR.rotationSpeed = beans[i].rotationSpeed*3.0f;
                    beanR.velocity = (Vector2){ 0.1f*RandomRange(10, 100), beans[i].velocity.y };
                    beans.push_back(beanR); //Sometimes this causes exception, idk why, pls help
                }

                beans.erase(beans.begin() + i);
                return scale;
            }

            return 0;
        }

        void Move() {
            int heigth = GetScreenHeight();
            for (int i = 0; i < (int)beans.size(); i++)
            {
                beans[i].pos.y += beans[i].velocity.y;
                beans[i].pos.x += beans[i].velocity.x;
                beans[i].velocity.x /= 1.2f;
                beans[i].rotation += beans[i].rotationSpeed;
                if (beans[i].pos.y-(texture.height*beans[i].scale*2) > heigth) { beans.erase(beans.begin() + i); }
            }
        }

        void Draw() {
            for (int i = 0; i < (int)beans.size(); i++)
            {
                Vector2 position = (Vector2){ (float)(beans[i].pos.x - texture.width*beans[i].scale/2), (float)(beans[i].pos.y - texture.height*beans[i].scale/2) };
                
                float s = sin(beans[i].rotation*DEG2RAD);
                float c = cos(beans[i].rotation*DEG2RAD);

                position.x -= beans[i].pos.x;
                position.y -= beans[i].pos.y;

                float xnew = position.x * c - position.y * s;
                float ynew = position.x * s + position.y * c;

                position.x = xnew + beans[i].pos.x;
                position.y = ynew + beans[i].pos.y;

                //float radius = texture.width*beans[i].scale/2;
                //DrawCircle(position.x, position.y, 3, DARKBLUE);
                //DrawCircleLines(beans[i].pos.x, beans[i].pos.y, radius, RED);
                //DrawText(TextFormat("Bean: %.3f", beans[0].rotation), 10, 70, 25, GREEN);
                //Fix beans[i].rotation, because it rotates from position not from center

                if (beans[i].damaged) {
                    DrawTextureEx(damaged, position, beans[i].rotation, beans[i].scale, WHITE);
                } else {
                    DrawTextureEx(texture, position, beans[i].rotation, beans[i].scale, WHITE);
                }                
            }
        }
};
#include "raylib.h"
#include <vector>

using std::vector;


struct Star{
    Vector2 pos;
    float scale;
    float rotaion;
};


class Stars {
    public:
        Texture2D texture;
        vector<Star> stars;

        Stars(int between, int offset)
        {
            texture = LoadTexture("resources/star.png");

            for (int y = 0; y < GetScreenHeight(); y += between) {
                for (int x = 0; x < GetScreenWidth(); x += between) {
                    Star star;
                    star.pos = (Vector2){ (float)x+RandomRange(-offset,offset), (float)y+RandomRange(-offset,offset) };
                    star.scale = 0.1f*RandomRange(5, 15);
                    star.rotaion = 0.1f*RandomRange(0, 10);
                    stars.push_back(star);
                }
            }
        }

        void Move()
        {
            int heigth = GetScreenHeight();
            for (int i = 0; i < (int)stars.size(); i++ ) {
                stars[i].pos.y += STARS_SPEED;
                if (stars[i].pos.y > heigth) { stars[i].pos.y = 0; }
            }
        }

        void Draw()
        {
            for (int i = 0; i < (int)stars.size(); i++ ) {
                Vector2 position = (Vector2){ (float)(stars[i].pos.x - texture.width*stars[i].scale/2), (float)(stars[i].pos.y - texture.height*stars[i].scale/2) };
                DrawTextureEx(texture, position, stars[i].rotaion, stars[i].scale, WHITE);
            }
        }
};
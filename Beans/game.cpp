#include <cmath>
#include "raylib.h"
#include "headers.h"
#include "ship.cpp"
#include "stars.cpp"
#include "bullets.cpp"
#include "beans.cpp"

class Game {
    public:
        Scene scene;
        Sound end;
        Music music;

        Ship ship = Ship();
        Stars stars = Stars(50, 15);
        Bullets bullets = Bullets();
        Beans beans = Beans();

        int framesCounter = 0;
        int targetFrames;
        int framesSpeed;
        int score;

        Game(int _targetFrames, int _framesSpeed)
        {
            scene = SceneMenu;
            targetFrames = _targetFrames;
            framesSpeed = _framesSpeed;
            score = 0;

            end = LoadSound("resources/end.wav");
            music = LoadMusicStream("resources/music.mp3");
        }

        void CheckBulletsCollide()
        {
            for (int i = 0; i < (int)bullets.bullets.size(); i++) {
                for (int j = 0; j < (int)beans.beans.size(); j++) {
                    float radius = beans.texture.width*beans.beans[j].scale/2;
                    Vector2 bulletPos = (Vector2){ bullets.bullets[i].pos.x-bullets.texture.width/2, bullets.bullets[i].pos.y-bullets.texture.height/2 };
                    Rectangle rec = { bulletPos.x, bulletPos.y, (float)bullets.texture.width, (float)bullets.texture.height };

                    //Vector2 beansPos = beans.beans[j].pos;
                    //DrawCircleLines(beansPos.x, beansPos.y, radius, RED);
                    //DrawRectangleLinesEx(rec, 1, MAGENTA);
                    
                    if (CheckCollisionCircleRec(beans.beans[j].pos, radius, rec)) {
                        score += beans.DamageBean(j, bullets.bullets[i].damage);
                        bullets.DeleteBullet(i);
                    }
                }
            }
        }

        void CheckShipCollide()
        {
            Rectangle shipRec = { ship.pos.x-ship.texture.width/2, ship.pos.y-ship.texture.height/2, (float)ship.texture.width, (float)ship.texture.height };
            for (int i = 0; i < (int)beans.beans.size(); i++) {
                float radius = beans.texture.width*beans.beans[i].scale/2;
                if (CheckCollisionCircleRec(beans.beans[i].pos, radius, shipRec)) {
                    if (ship.invincible) { return; }
                    ship.invincible = true;
                    ship.invincibleTime = GetTime()+SHIP_INVINC_TIME;
                    ship.health -= (beans.beans[i].scale*beans.beans[i].scale)*2;

                    if (ship.health <= 0.0f) {
                        scene = SceneMenu;
                        StopMusicStream(music);
                        PlaySound(end);
                    }
                }
            }
        }

        void Update()
        {
            framesCounter++;
            if (framesCounter < (targetFrames/framesSpeed)) { return; }
            framesCounter = 0;

            switch (scene)
            {
                case SceneMenu:
                    if (IsMouseButtonDown(0))
                    {
                        scene = SceneGame;
                        PlayMusicStream(music);
                        score = 0;

                        //Yes, this causes memory leak, BUT...., idc
                        //And also this can cause Segmentation fault, but, who cares
                        ship = Ship();
                        bullets = Bullets();
                        beans = Beans();
                    }
                    break;
                case SceneGame:
                    UpdateMusicStream(music);

                    if (IsKeyDown(KEY_SPACE))
                    {
                        bullets.SpawnBullet(ship.pos.x, (ship.pos.y-ship.texture.height/2), BULLET_SPEED, BULLET_DAMAGE);
                    }

                    beans.SpawnBean();
                    stars.Move();
                    beans.Move();
                    ship.Move();
                    bullets.Move();

                    CheckBulletsCollide();
                    CheckShipCollide();
                    break;
            }
        }

        void Draw()
        {
            switch (scene)
            {
                case SceneMenu:
                    {
                        char gameTitle[] = "Beeeeeans";
                        DrawText(gameTitle, (GetScreenWidth()/2 - MeasureText(gameTitle, 80)/2), 280, 80, {200, 200, 200, 255});
                        char subTitle[] = "Click To Play!";
                        DrawText(subTitle, (GetScreenWidth()/2 - MeasureText(subTitle, 40)/2), 390 + sin(GetTime()*10)*1.2, 40, {200, 200, 200, 255});
                        const char *scoreTitle = TextFormat("Score: %d", score);
                        DrawText(scoreTitle, (GetScreenWidth()/2 - MeasureText(scoreTitle, 40)/2), 690 , 40, {200, 200, 200, 255});
                        break;
                    }
                case SceneGame:
                    {
                        stars.Draw();
                        beans.Draw();
                        bullets.Draw();
                        ship.Draw();
                        DrawText(TextFormat("Score: %d", score), 10, 10, 25, GREEN);
                        DrawText(TextFormat("Health: %.0f", ship.health), 10, 40, 25, GREEN);
                        break;
                    }
            }
        }
};
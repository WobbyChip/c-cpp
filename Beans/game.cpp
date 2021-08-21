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

        Stars stars = Stars(50, 15);
        Ship ship;
        Bullets bullets;
        Beans beans;

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

        void CheckcCllision()
        {
            for (int i = 0; i < (int)beans.beans.size(); i++) {
                for (int j = 0; j < (int)bullets.bullets.size(); j++) {
                    //DrawCircleLines(beans.beans[j].pos.x, beans.beans[j].pos.y, beans.beans[j].radius, RED);
                    //DrawRectangleLinesEx(bullets.bullets[i].rect, 1, MAGENTA);
                    
                    if (beans.CollideRect(i, bullets.bullets[j].rect)) {
                        score += beans.DamageBean(i, bullets.bullets[j].damage);
                        bullets.DeleteBullet(j);
                    }
                }

                if (beans.CollideRect(i, ship.rect)) {
                    if (ship.invincible) { return; }
                    ship.invincible = true;
                    ship.invincibleTime = GetTime()+SHIP_INVINC_TIME;
                    ship.health -= (beans.beans[i].scale*beans.beans[i].scale)*2;

                    if (ship.health <= 0.0f) {
                        scene = SceneMenu;
                        StopMusicStream(music);
                        PlaySound(end);
                        break;
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
                    bullets.Move();
                    ship.Move();

                    CheckcCllision();
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
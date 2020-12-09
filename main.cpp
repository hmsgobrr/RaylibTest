#include "raylib.h"

struct Asteroid {
    Vector2 pos;
    int texIndex;
    float scale;
    float speed;
};
struct Star {
    Vector2 pos;
    int colorIdx;
    float scale;
    float speed;
    int frame;
    float timer;
};

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Reylib-Gaem v1.0");

    // SetExitKey(0);

    Texture2D ship = LoadTexture("res/gfx/Ship.png");
    Texture2D shipPropulsionTex = LoadTexture("res/gfx/ShipPropulsion.png");

    const float shipWidth = ship.width * 4;
    const float shipHeight = ship.height * 4;

    const int propulsionFrameWidth = shipPropulsionTex.width / 6;
    const int propulsionFrameHeight = shipPropulsionTex.height;
    const int propulsionMaxFrame = shipPropulsionTex.width / propulsionFrameWidth;

    Vector2 shipPos = { 50, (float)screenHeight / 2 - shipWidth / 2 };

    const float velocity = 2.5f;

    const Texture2D asteroidTexs[2] = {
        LoadTexture("res/gfx/asteroid-1.png"),
        LoadTexture("res/gfx/asteroid-2.png") };
    const int maxAsteroids = 100;

    Asteroid asteroids[maxAsteroids] = { 0 };
    for (int i = 0; i < maxAsteroids; i++) {
        asteroids[i].pos.x = screenWidth + 175 * i;
        asteroids[i].pos.y = GetRandomValue(0, screenHeight - 30);
        asteroids[i].texIndex = GetRandomValue(0, 1);
        asteroids[i].scale = GetRandomValue(2, 5);
        asteroids[i].speed = GetRandomValue(2, 5);
    }

    Texture2D starsTex = LoadTexture("res/gfx/stars.png");
    const int starFrameWidth = starsTex.width / 8;
    const int starFrameHeight = starsTex.height / 6;
    const int starMaxFrame = starsTex.width / starFrameWidth;
    const int maxStars = 100;
    Star stars[maxStars] = { 0 };
    for (int i = 0; i < maxStars; i++) {
        stars[i].pos.x = screenWidth + 175 * i;
        stars[i].pos.y = GetRandomValue(0, screenHeight - 30);
        stars[i].colorIdx = GetRandomValue(0, 5);
        stars[i].scale = GetRandomValue(1, 3);
        stars[i].speed = GetRandomValue(1, 2);
        stars[i].frame = GetRandomValue(0, 7);
        stars[i].timer = 0;
    }


    SetTargetFPS(60);

    float timer = 0.0f;
    int shipPropulsionFrame = 0;

    while (!WindowShouldClose()) {
        timer += GetFrameTime();

        if (timer >= 0.1f) {
            timer = 0.0f;
            shipPropulsionFrame++;
        }

        shipPropulsionFrame %= propulsionMaxFrame;

        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) shipPos.x += velocity;
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) shipPos.x -= velocity;
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) shipPos.y -= velocity;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) shipPos.y += velocity;

        BeginDrawing();

        ClearBackground(BLACK);

        for (int i = 0; i < maxStars; i++) {
            stars[i].timer += GetFrameTime();

            if (stars[i].timer >= 0.1f) {
                stars[i].timer = 0;
                stars[i].frame++;
            }

            stars[i].frame %= starMaxFrame;

            stars[i].pos.x -= stars[i].speed;

            if (stars[i].pos.x < -starFrameWidth * stars[i].scale) {
                stars[i].pos.x = screenWidth + 175 * i;
                stars[i].pos.y = GetRandomValue(0, screenHeight - 30);
                stars[i].colorIdx = GetRandomValue(0, 5);
                stars[i].scale = GetRandomValue(1, 3);
                stars[i].speed = GetRandomValue(1, 2);
                stars[i].frame = GetRandomValue(0, 7);
                stars[i].timer = 0;
            }

            DrawTexturePro(
                starsTex,
                Rectangle{
                    (float)(starFrameWidth * stars[i].frame),
                    (float)(starFrameHeight * stars[i].colorIdx),
                    (float)starFrameWidth,
                    (float)starFrameHeight
                },
                Rectangle{
                    stars[i].pos.x,
                    stars[i].pos.y,
                    starFrameWidth * stars[i].scale,
                    starFrameHeight * stars[i].scale
                },
                Vector2{ (float)starFrameWidth, (float)starFrameHeight },
                0,
                RAYWHITE
            );
        }


        DrawTexturePro(
            shipPropulsionTex,
            Rectangle{
                (float)(propulsionFrameWidth * shipPropulsionFrame),
                0,
                (float)propulsionFrameWidth,
                (float)propulsionFrameHeight
            },
            Rectangle{
                shipPos.x - ship.width - 6,
                shipPos.y + shipHeight / 2 - propulsionFrameHeight,
                propulsionFrameWidth * 4.5f,
                propulsionFrameHeight * 4.5f
            },
            Vector2{ (float)propulsionFrameWidth, (float)propulsionFrameHeight },
            0,
            RAYWHITE
        );

        DrawTextureEx(ship, shipPos, 0.0f, 4, RAYWHITE);

        for (int i = 0; i < maxAsteroids; i++) {
            asteroids[i].pos.x -= asteroids[i].speed;

            if (asteroids[i].pos.x < -asteroidTexs[asteroids[i].texIndex].width * asteroids[i].scale) {
                asteroids[i].pos.x = screenWidth + 175 * i;
                asteroids[i].pos.y = GetRandomValue(0, screenHeight - 30);
                asteroids[i].texIndex = GetRandomValue(0, 1);
                asteroids[i].scale = GetRandomValue(2, 5);
                asteroids[i].speed = GetRandomValue(2, 5);
            }

            if (CheckCollisionRecs(
                Rectangle{ shipPos.x, shipPos.y, shipWidth, shipHeight },
                Rectangle{
                    asteroids[i].pos.x,
                    asteroids[i].pos.y,
                    asteroidTexs[asteroids[i].texIndex].width * asteroids[i].scale,
                    asteroidTexs[asteroids[i].texIndex].height * asteroids[i].scale
                }
            )) {
                shipPos.x = 50;
                shipPos.y = screenHeight / 2 - shipWidth / 2;

                for (int i = 0; i < maxAsteroids; i++) {
                    asteroids[i].pos.x = screenWidth + 175 * i;
                    asteroids[i].pos.y = GetRandomValue(0, screenHeight - 30);
                    asteroids[i].texIndex = GetRandomValue(0, 1);
                    asteroids[i].scale = GetRandomValue(2, 5);
                    asteroids[i].speed = GetRandomValue(2, 5);
                }
            }

            DrawTextureEx(asteroidTexs[asteroids[i].texIndex], asteroids[i].pos, 0, asteroids[i].scale, RAYWHITE);
        }

        DrawText("move the ship with WASD or Arrow Keys", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    UnloadTexture(ship);
    UnloadTexture(shipPropulsionTex);
    for (int i = 0; i < 2; i++) UnloadTexture(asteroidTexs[i]);
    UnloadTexture(starsTex);

    CloseWindow();

    return 0;
}
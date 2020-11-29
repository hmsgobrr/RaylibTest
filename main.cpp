#include "raylib.h"

struct Asteroid {
    Vector2 pos;
    int texIndex;
    float scale;
};
struct Star {

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
        LoadTexture("res/gfx/asteroid-2.png")
    };
    const int maxAsteroids = 100;
    int asteroidsSpeedX = 2;

    Asteroid asteroids[maxAsteroids] = { 0 };
    for (int i = 0; i < maxAsteroids; i++) {
        asteroids[i].pos.x = screenWidth + 175 * i;
        asteroids[i].pos.y = GetRandomValue(0, screenHeight - 30);
        asteroids[i].texIndex = GetRandomValue(0, 1);
        asteroids[i].scale = GetRandomValue(2, 5);
    }


    SetTargetFPS(60);

    float timer = 0.0f;
    int frame = 0;

    while (!WindowShouldClose()) {
        timer += GetFrameTime();

        if (timer >= 0.1f) {
            timer = 0.0f;
            frame++;
        }

        frame %= propulsionMaxFrame;

        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) shipPos.x += velocity;
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) shipPos.x -= velocity;
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) shipPos.y -= velocity;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) shipPos.y += velocity;

        BeginDrawing();

        ClearBackground(BLACK);

        DrawTexturePro(
            shipPropulsionTex,
            Rectangle{
                (float)(propulsionFrameWidth * frame),
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
            asteroids[i].pos.x -= asteroidsSpeedX;

            if (asteroids[i].pos.x < -asteroidTexs[asteroids[i].texIndex].width * asteroids[i].scale) {
                asteroids[i].pos.x = screenWidth + 175 * i;
                asteroids[i].pos.y = GetRandomValue(0, screenHeight - 30);
                asteroids[i].texIndex = GetRandomValue(0, 1);
                asteroids[i].scale = GetRandomValue(2, 5);
            }

            DrawTextureEx(asteroidTexs[asteroids[i].texIndex], asteroids[i].pos, 0, asteroids[i].scale, RAYWHITE);
        }


        DrawText("move the ship with WASD or Arrow Keys", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    UnloadTexture(ship);
    UnloadTexture(shipPropulsionTex);

    for (int i = 0; i < 2; i++)
        UnloadTexture(asteroidTexs[i]);

    CloseWindow();

    return 0;
}
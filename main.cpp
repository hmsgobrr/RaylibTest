#include "raylib.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Reylib-Gaem v1.0");

    // SetExitKey(0);

    Texture2D ship = LoadTexture("res/gfx/Ship.png");
    Texture2D shipPropulsionTex = LoadTexture("res/gfx/ShipPropulsion.png");

    float shipWidth = ship.width * 4;
    float shipHeight = ship.height * 4;

    int propulsionFrameWidth = shipPropulsionTex.width / 6;
    int propulsionFrameHeight = shipPropulsionTex.height;
    int propulsionMaxFrame = shipPropulsionTex.width / propulsionFrameWidth;

    Vector2 shipPos = { 20, (float)screenHeight / 2 - shipWidth / 2 };

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

        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) shipPos.x += 2.0f;
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) shipPos.x -= 2.0f;
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) shipPos.y -= 2.0f;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) shipPos.y += 2.0f;

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

        DrawText("move the ship with WASD or Arrow Keys", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    UnloadTexture(ship);
    UnloadTexture(shipPropulsionTex);

    CloseWindow();

    return 0;
}
#include "raylib.h";

int main()
{

    const int windowWidth{1920};
    const int windowHeight{1080};

    InitWindow(windowWidth, windowHeight, "RPG Clasher");

    Texture2D worldMap = LoadTexture("nature_tileset/workldmap.png");

    SetTargetFPS(180);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 worldMapPos{0.0, 0.0};
        DrawTextureEx(worldMap, worldMapPos, 0.0, 4.0, WHITE);

        EndDrawing();
    }
    CloseWindow();
}
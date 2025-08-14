#include "raylib.h"
#include "raymath.h"

int main()
{

    const int windowWidth{1920};
    const int windowHeight{1080};

    InitWindow(windowWidth, windowHeight, "RPG Clasher");

    Texture2D worldMap = LoadTexture("nature_tileset/worldMap.png");
    Vector2 worldMapPos{0.0, 0.0};
    
    // speed used to scale the movement of map
    float speed{3.0};

    SetTargetFPS(180);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Direction of movement
        Vector2 direction{};
        if (IsKeyDown(KEY_A))
            direction.x -= 1.0;
        if (IsKeyDown(KEY_D))
            direction.x += 1;
        if (IsKeyDown(KEY_W))
            direction.y -= 1;
        if (IsKeyDown(KEY_S))
            direction.y += 1;

        // normalizing the length of direction and calculating the new position of worldMapPos and changing it as per the keys downed
        if (Vector2Length(direction) != 0)
        {
            // calculating the new position and scaling the speed
            //  worldMapPos = worldMapPos - direction
            worldMapPos = Vector2Subtract(worldMapPos, Vector2Scale(Vector2Normalize(direction), speed));
        }

        DrawTextureEx(worldMap, worldMapPos, 0.0, 2.0, WHITE);

        EndDrawing();
    }
    CloseWindow();
}
#include "raylib.h"
#include "raymath.h"

class Character
{
public:
private:
};

int main()
{

    const int windowWidth{1920};
    const int windowHeight{1080};

    InitWindow(windowWidth, windowHeight, "RPG Clasher");

    // Loading the background worldMap
    Texture2D worldMap = LoadTexture("nature_tileset/worldMap.png");
    Vector2 worldMapPos{0.0, 0.0};
    // speed used to scale the movement of map
    float speed{3.0};

    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knightIdle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knightOnTheMove = LoadTexture("characters/knight_run_spritesheet.png");

    // positioning the knight in the center of the screen and scaling its size by 4
    Vector2 knightPos{
        (float)windowWidth / 2.0f - (4.0f * (0.5f * (float)knight.width / 6.0f)),
        (float)windowHeight / 2.0f - (4.0f * (0.5f * (float)knight.height))};

    // direction knight is facing. -1 = left, 1 = right
    float rightLeft{1.0f};
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.0f / 12.0f};

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
            // left right value allocation
            (direction.x < 0.0f) ? rightLeft = -1.0f : rightLeft = 1.0f;
            // changing the textures for knight if he is moving
            knight = knightOnTheMove;
        }
        else
            knight = knightIdle;

        // drawing the map
        DrawTextureEx(worldMap, worldMapPos, 0.0, 7.0, WHITE);

        // updating animation frames for knight
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrames)
                frame = 0;
        }
        // drawing the knight
        Rectangle source{frame * ((float)knight.width / 6.0f), 0.f, rightLeft * (float)knight.width / 6.0f, (float)knight.height};
        Rectangle dest{knightPos.x, knightPos.y, 4.5f * (float)knight.width / 6.0f, 4.5f * (float)knight.height};
        DrawTexturePro(knight, source, dest, Vector2{}, 0.0f, WHITE);

        EndDrawing();
    }
    CloseWindow();
}
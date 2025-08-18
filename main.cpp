#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);

private:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos;
    Vector2 worldPos;
    // direction knight is facing. -1 = left, 1 = right
    float rightLeft{1.0f};
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.0f / 12.0f};
    // speed used to scale the movement of map
    const float speed{3.0};
};

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth / 2.0f - (4.0f * (0.5f * (float)texture.width / 6.0f)),
        (float)winHeight / 2.0f - (4.0f * (0.5f * (float)texture.height))};
}

void Character::tick(float deltaTime)
{
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
        // set worldMapPos = worldMapPos + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        // left right value allocation
        (direction.x < 0.0f) ? rightLeft = -1.0f : rightLeft = 1.0f;
        // changing the textures for knight if he is moving
        texture = run;
    }
    else
        texture = idle;

    // updating animation frames for knight
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    // drawing the knight
    Rectangle source{frame * ((float)texture.width / 6.0f), 0.f, rightLeft * (float)texture.width / 6.0f, (float)texture.height};
    Rectangle dest{screenPos.x, screenPos.y, 4.5f * (float)texture.width / 6.0f, 4.5f * (float)texture.height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}

int main()
{

    const int windowWidth{1920};
    const int windowHeight{1080};

    InitWindow(windowWidth, windowHeight, "RPG Clasher");

    // Loading the background worldMap
    Texture2D worldMap = LoadTexture("nature_tileset/worldMap.png");
    Vector2 worldMapPos{0.0, 0.0};

    // an instance of character class, knight
    Character knight{};
    // calling setScreenPos fuc to update winWidth and winHeight
    knight.setScreenPos(windowWidth, windowHeight);

    SetTargetFPS(180);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // getting the characters worldPos and flipping it to negative by multiplying it to -1.0f
        worldMapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // drawing the map
        DrawTextureEx(worldMap, worldMapPos, 0.0, 7.0, WHITE);
        knight.tick(GetFrameTime());

        EndDrawing();
    }
    CloseWindow();
}
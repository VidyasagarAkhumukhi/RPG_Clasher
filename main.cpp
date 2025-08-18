// Main entry for the simple RPG Clasher demo.
// - Loads a tiled world map, spawns props and enemies in world coordinates.
// - Keeps the player (knight) centered on screen and moves the world underneath.
// - Handles input, rendering, simple collisions and a basic attack.

#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "RPG Clasher");

    // Load the large world map texture. The world is drawn scaled by `mapScale`.
    // We compute `mapPos` each frame from the character world position so the
    // knight appears centered while the map moves under the player.
    Texture2D map = LoadTexture("nature_tileset/worldMap.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    // Create the player character. The character stores its world position
    // (in world units) and a screen position (keeps the knight centered).
    Character knight{windowWidth, windowHeight};

    // Props are static world objects (rocks, logs). Their `worldPos` is in
    // world coordinates; when rendering we subtract the knight world pos to
    // get a screen position.
    Prop props[7]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{1200.f, 1200.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{1500.f, 700.f}, LoadTexture("nature_tileset/Log.png")},
        Prop{Vector2{1750.f, 600.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{1000.f, 400.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{1670.f, 900.f}, LoadTexture("nature_tileset/Log.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    // Create simple enemies with idle/run textures. They will be given a
    // pointer to the player as a target so they can follow or interact.
    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy *enemies[]{
        &goblin,
        &slime};

    // Tell each enemy which character to target.
    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // Compute map position so the knight remains centered. worldPos is
        // in world units; multiplying by -1 flips the map so the player stays
        // visually in the middle of the screen.
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map (scaled). All world objects will be drawn relative to
        // the knight's world position so they line up with the map.
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        // Draw props (rocks/logs) in screen space relative to the knight.
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        // If player is dead show Game Over and skip rest of frame logic.
        if (!knight.getAlive()) // Character is not alive
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else // Character is alive
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        // Update player logic (movement, animation, weapon drawing).
        knight.tick(GetFrameTime());

        // Check world bounds so the player can't move the camera outside map.
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
        {
            knight.undoMovement();
        }
        // Check collisions between the player's collision rect (screen) and
        // each prop's collision rect (also returned in screen-space). If a
        // collision occurs we undo the player's last movement.
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        // Update enemies (simple AI/ticking).
        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        // On mouse click, check weapon collision against enemies and kill any
        // enemy hit by the weapon hitbox.
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }
    CloseWindow();
}

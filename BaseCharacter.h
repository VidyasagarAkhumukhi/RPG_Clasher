#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"
// BaseCharacter implements shared behavior for player and enemies.
// - Holds world-space position and common animation fields.
// - Provides collision rect and undoMovement to revert the last step.
class BaseCharacter
{
public:
    BaseCharacter();
    // Return the character position in world coordinates (used to offset map)
    Vector2 getWorldPos() { return worldPos; }

    // Revert movement to previous frame (used when colliding with world/props)
    void undoMovement();

    // Return collision rectangle in screen-space (based on derived getScreenPos)
    Rectangle getCollisionRec();

    // Common tick which derived classes extend; updates animation & movement
    virtual void tick(float deltaTime);

    // Derived classes must provide their screen position (where to draw)
    virtual Vector2 getScreenPos() = 0;

    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }

protected:
    // Textures for animation frames (derived classes may change these)
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};

    // World-space position and previous frame position (for undoMovement)
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};

    // Facing direction: 1 = right, -1 = left
    float rightLeft{1.f};

    // Animation bookkeeping
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};

    // Movement speed applied to worldPos
    float speed{4.f};

    // Sprite frame dimensions and draw scale
    float width{};
    float height{};
    float scale{4.0f};

    // Velocity used by tick() for movement
    Vector2 velocity{};

private:
    bool alive{true};
};

#endif

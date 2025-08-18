#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) : worldPos(pos),
                                         texture(tex)
{
}

void Prop::Render(Vector2 knightPos)
{
    // Compute screen position by subtracting the knight's world position.
    // This yields coordinates relative to the center-anchored player.
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 knightPos)
{
    // Collision rect uses the same screen-space position as Render above.
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    return Rectangle{
        screenPos.x,
        screenPos.y,
        texture.width * scale,
        texture.height * scale};
}

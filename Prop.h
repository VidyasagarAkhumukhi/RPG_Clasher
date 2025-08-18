#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    // Draw the prop at screen position relative to the knight's world pos.
    void Render(Vector2 knightPos);

    // Return a collision rectangle for the prop in screen-space. The
    // caller must provide the knight's world position so the prop can compute
    // its screen position (worldPos - knightPos).
    Rectangle getCollisionRec(Vector2 knightPos);

private:
    // Texture for the prop (single image)
    Texture2D texture{};
    // worldPos is the prop's position in world coordinates (not screen px)
    Vector2 worldPos{};
    // scale controls how large the prop is drawn compared to its texture size
    float scale{4.f};
};

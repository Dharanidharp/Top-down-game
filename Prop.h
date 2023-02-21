#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 knight_pos);
    Rectangle GetCollisionRect(Vector2 knight_pos);

private:
    Texture2D texture{};
    Vector2 worldPos{};
    float scale{8.f};
};
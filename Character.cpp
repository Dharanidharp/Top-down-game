#include "Character.h"
#include "raymath.h"

Character::Character(int window_width, int window_height) : 
    window_width(window_height), window_height(window_height)
{
    width = texture.width / max_frames;
    height = texture.height;
}

void Character::Tick(float delta_time)
{
    if(!GetAlive()) return;

    // Input / moving map - ASWD
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0; // LEFT
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0; // RIGHT
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0; // UP
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0; // DOWN

    BaseCharacter::Tick(delta_time);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};

    if(knight_facing > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = {85.f, 105.f};

        weaponCollisionRect = 
        {
            GetScreenPos().x + offset.x,
            GetScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };

        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {40.f, 105.f};

        weaponCollisionRect = 
        {
            GetScreenPos().x + offset.x - weapon.width * scale,
            GetScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };

        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
    }

    // Draw sword
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * knight_facing, static_cast<float>(weapon.height)};
    Rectangle dest{GetScreenPos().x + offset.x, GetScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    DrawRectangleLines(
        weaponCollisionRect.x,
        weaponCollisionRect.y,
        weaponCollisionRect.width,
        weaponCollisionRect.height,
        RED
    );
}

Vector2 Character::GetScreenPos()
{
    return Vector2
    {
        static_cast<float>(window_width / 2.0f) - scale * (0.5f * width),
        static_cast<float>(window_height / 2.0f) - scale * (0.5f * height)
    };
}

void Character::TakeDamage(float damage)
{
    health -= damage;
    if(health <= 0.f)
    {
        SetAlive(false);
    }
}

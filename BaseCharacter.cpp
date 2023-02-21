#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::UndoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRect()
{
    return Rectangle
    {
        GetScreenPos().x,
        GetScreenPos().y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::Tick(float delta_time)
{
    worldPosLastFrame = worldPos;

    // update character animation
    running_time += delta_time;
    if (running_time >= update_time)
    {
        frame++;
        running_time = 0.f;
        if (frame > max_frames)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // set world_pos = world_pos + direction
        texture = run;
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? knight_facing = -1.f : knight_facing = 1.f;
    }
    else
    {
        texture = idle;
    }

    velocity = {};

    // Draw Character
    Rectangle source{frame * width, 0.0f, knight_facing * width, height};
    Rectangle dest{GetScreenPos().x, GetScreenPos().y, scale * width, scale * height};

    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}
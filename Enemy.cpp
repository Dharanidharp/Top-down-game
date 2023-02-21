#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture, float speed_val)
{
    width = texture.width/ max_frames;
    height = texture.height;
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    speed = speed_val;
}

void Enemy::Tick(float deltaTime)
{
    if(!GetAlive()) return;

    // get to target -> character(player) screen position - enemy screen position
    velocity = Vector2Subtract(target->GetScreenPos(), GetScreenPos());

    if(Vector2Length(velocity) < radius) velocity = {};

    BaseCharacter::Tick(deltaTime);

    if(CheckCollisionRecs(target->GetCollisionRect(), GetCollisionRect()))
    {
        target->TakeDamage(GetDamagePerSec() * deltaTime);
    }
}

Vector2 Enemy::GetScreenPos()
{
    return Vector2Subtract(worldPos, target->GetWorldPos());
}
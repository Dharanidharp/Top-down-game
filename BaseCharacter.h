#ifndef BASE_CHARACTER_H // if not defined
#define BASE_CHARACTER_H

#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 GetWorldPos() { return worldPos; }
    void UndoMovement();
    Rectangle GetCollisionRect();

    virtual void Tick(float delta_time);
    virtual Vector2 GetScreenPos() = 0;

    bool GetAlive() { return alive; }
    bool SetAlive(bool isAlive) { alive = isAlive; }

protected:
    float width{};
    float height{};
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 worldPos{};
    float knight_facing{1.f}; // right or left
    // Animation character
    float running_time{};
    int frame{};
    int max_frames{6};
    float update_time{1.f / 12.f};
    float speed{8.f};

    // map bounds
    Vector2 worldPosLastFrame{};

    float scale{8.f};

    Vector2 velocity{};

private:
    bool alive{true};
};

#endif
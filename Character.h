#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int window_width, int window_height);
    virtual void Tick(float delta_time) override;
    virtual Vector2 GetScreenPos() override;
    Rectangle GetWeaponCollisionRect() { return weaponCollisionRect; }
    float GetHealth() const { return health; }
    void TakeDamage(float damage);

private:
    int window_width{};
    int window_height{};

    Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
    Rectangle weaponCollisionRect{};

    float health{100.f};
};

#endif
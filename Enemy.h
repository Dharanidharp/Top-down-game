#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture, float speed);
    virtual void Tick(float delta_time) override;
    void SetTarget(Character* character) { target = character; }
    virtual Vector2 GetScreenPos() override;
    float GetDamagePerSec() { return damagePerSec; }

private:
    Character* target;
    float damagePerSec{10.f};
    float radius{35.f};
};

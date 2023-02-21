#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include <string>

int main()
{
    // Game Window
    const int game_window[2]{768, 768};
    InitWindow(game_window[0], game_window[1], "Top Down Game");

    // World MAP
    Texture2D map = LoadTexture("nature-tileset-map/WorldMap.png");
    Vector2 map_position{0.0, 0.0};
    const float map_scale{8.f};

    SetTargetFPS(60);

    // Create character
    Character knight{game_window[0], game_window[1]};

    // Props
    Prop rock{Vector2{0.f, 0.f}, LoadTexture("nature-tileset-map/Rock.png")};
    Prop props[2]{
        Prop{Vector2{1000.f, 300.f}, LoadTexture("nature-tileset-map/Rock.png")},
        Prop{Vector2{400.f, 1000.f}, LoadTexture("nature-tileset-map/Log.png")}};

    // Create Enemy
    Enemy goblin
    {Vector2{800.f, 300.f},
                 LoadTexture("characters/goblin_idle_spritesheet.png"),
                 LoadTexture("characters/goblin_run_spritesheet.png"),
                 6.5f
    };

    Enemy slime
    {
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png"),
        4.5f
    };

    Enemy *enemies[]{
        &goblin,
        &slime};

    for (auto enemy : enemies)
    {
        enemy->SetTarget(&knight);
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(WHITE);

        map_position = Vector2Scale(knight.GetWorldPos(), -1.f);

        DrawTextureEx(map, map_position, 0.0, map_scale, WHITE);

        for (auto prop : props)
        {
            prop.Render(knight.GetWorldPos());
        }

        knight.Tick(GetFrameTime());

        // Map bounds
        if (knight.GetWorldPos().x < 0.f ||
            knight.GetWorldPos().y < 0.f ||
            knight.GetWorldPos().x + game_window[0] + 60 > map.width * map_scale ||
            knight.GetWorldPos().y + game_window[1] + 60 > map.height * map_scale)
        {
            knight.UndoMovement();
        }

        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.GetCollisionRect(knight.GetWorldPos()), knight.GetCollisionRect()))
            {
                knight.UndoMovement();
            }
        }

        if (!knight.GetAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 80, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knight_health = "Health: ";
            knight_health.append(std::to_string(knight.GetHealth()), 0, 5);
            DrawText(knight_health.c_str(), 55.f, 45.f, 80, RED);
        }

        for (auto enemy : enemies)
        {
            enemy->Tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->GetCollisionRect(), knight.GetWeaponCollisionRect()))
                {
                    enemy->SetAlive(false);
                }
            }
        }

        EndDrawing();
    }

    UnloadTexture(map);
    CloseWindow();
}
#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

struct Projectile {
    Vector2 position;
    Vector2 speed;
};

int hitCounter = 0;

int main(void) {
    InitWindow(1000, 800, "Game");
    SetTargetFPS(60);

    srand(time(0));

    vector<Projectile> projectiles;
    Vector2 bluePos = {500, 700};

    // Red square stuff
    Rectangle red = {400, 200, 50, 50};
    int moveSpeed = 5;
    int direction = 0;
    int changeDirectionCounter = 0;
    const int changeInterval = 60;

    while (!WindowShouldClose()) {
        string h = to_string(hitCounter);
        if (hitCounter >= 1000){
            h = "You Win!";
        }
        DrawText(h.c_str(), 50, 50, 40, GREEN);
        DrawText("Reach 1000 pts to win.", 300, 100, 40, GREEN);

        if (changeDirectionCounter >= changeInterval) {
            direction = rand() % 3 - 1;
            changeDirectionCounter = 0;
        } else {
            changeDirectionCounter++;
        }
        red.x += direction * moveSpeed;
        if (red.x < 0) red.x = 0;
        if (red.x > GetScreenWidth() - red.width) red.x = GetScreenWidth() - red.width;
        
        //user input
        if (IsKeyDown(KEY_D)){
            bluePos.x += 4.0f;
        }
        if (IsKeyDown(KEY_A)){
            bluePos.x -= 4.0f;
        }
        if (IsKeyDown(KEY_S)){
            bluePos.y += 1.5f;
        }
        if (IsKeyDown(KEY_W)){
            bluePos.y -= 1.5f;
        }
        if (IsKeyPressed(KEY_SPACE)) {
            Projectile newProjectile = {{bluePos.x, bluePos.y}, {0, -5}};
            projectiles.push_back(newProjectile);
        }

        for (auto &proj : projectiles) {
            proj.position.y += proj.speed.y;

            // Check if red square is hit
            if (proj.position.x >= red.x && proj.position.x <= red.x + red.width &&
                proj.position.y >= red.y && proj.position.y <= red.y + red.height) {
                hitCounter = hitCounter + 1;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        //Blue
        DrawRectangle(bluePos.x, bluePos.y, 50, 50, BLUE);

        for (const auto &proj : projectiles) {
            DrawRectangle(proj.position.x, proj.position.y, 5, 10, WHITE);
        }

        //Red
        DrawRectangleRec(red, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

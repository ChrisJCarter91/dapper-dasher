#include "raylib.h"

int main()
{
    // Window Dimensions
    int width{800};
    int height {450};
    InitWindow(width, height, "Dapper-Dasher");

    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        
        ClearBackground(WHITE);

        EndDrawing();
    }
}
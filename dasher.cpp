#include "raylib.h"

int main()
{
    // Window Dimensions
    const int windowWidth{800};
    const int windowHeight {450};

    // Initialize the window
    InitWindow(windowWidth, windowHeight, "Dapper-Dasher!");

    // Rectangle dimensions
    const int width{50};
    const int height{80};

    int posY{windowHeight - height};
    int velocity{0};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Start Drawing
        BeginDrawing();

        ClearBackground(WHITE);

        posY += velocity;

        DrawRectangle(windowWidth/2, posY, width, height, BLUE);

        // Jumping
        if (IsKeyPressed(KEY_SPACE)) 
        {
            velocity -= 10;
        }

        // Stop Drawing
        EndDrawing();
    }
    CloseWindow();
}
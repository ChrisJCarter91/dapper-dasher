#include "raylib.h"

int main()
{
    // Window Dimensions
    const int windowWidth{800};
    const int windowHeight {450};

    // Initialize the window
    InitWindow(windowWidth, windowHeight, "Dapper-Dasher!");

    // Acceleration due to gravity (pixels/frame/frame)
    const int gravity{1};

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

        // Perform ground check
        if (posY >= windowHeight - height)
        {
            // rectangle is on the ground
            velocity = 0;
        }
        else
        {
            // rectangle is in the air - Apply gravity
            velocity += gravity;
        }

        // Jumping
        if (IsKeyPressed(KEY_SPACE)) 
        {
            velocity -= 10;
        }

        // Update Position
        posY += velocity;

        DrawRectangle(windowWidth/2, posY, width, height, BLUE);

        // Stop Drawing
        EndDrawing();
    }
    CloseWindow();
}
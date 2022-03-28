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

        // is rectangle in the air?
        bool isInAir {};
        // jump velocity
        const int jumpVel{-22};

        if (posY >= windowHeight - height)
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in the air - Apply gravity
            velocity += gravity;
            isInAir = true;
        }

        // Jump Check
        if (IsKeyPressed(KEY_SPACE) && !isInAir) 
        {
            velocity += jumpVel;
        }

        // Update Position
        posY += velocity;

        DrawRectangle(windowWidth/2, posY, width, height, BLUE);

        // Stop Drawing
        EndDrawing();
    }
    CloseWindow();
}
#include "raylib.h"

int main()
{
    // Window Dimensions
    const int windowWidth{800};
    const int windowHeight {450};

    // Initialize the window
    InitWindow(windowWidth, windowHeight, "Dapper-Dasher!");

    // Acceleration due to gravity (pixels/s/s)
    const int gravity{1'000};

    Texture2D scarfy = LoadTexture("textures/scarfy.png");

    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;

    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    int velocity{0};

    // animation frame
    int frame{};
    // Amount of time before we update the animation frame
    const float updateTime{1.0/12.0};
    float runningTime{};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Delta time (time since last frame)
        const float dT{GetFrameTime()};

        // Start Drawing
        BeginDrawing();

        ClearBackground(WHITE);

        // is rectangle in the air?
        bool isInAir {};
        // jump velocity (pixels/s)
        const int jumpVel{-600};

        // Perform ground check
        if (scarfyPos.y >= windowHeight - scarfyRec.width)
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // rectangle is in the air - Apply gravity
            velocity += gravity * dT;
            isInAir = true;
        }

        // Jump Check
        if (IsKeyPressed(KEY_SPACE) && !isInAir) 
        {
            velocity += jumpVel;
        }

        // Update Position
        scarfyPos.y += velocity * dT;

        runningTime += dT;
        // Update Running time
        if (runningTime >= updateTime)
        {
            runningTime = 0.0;
            // Update animation frame
            scarfyRec.x = frame * scarfyRec.width;
            frame++;
            if (frame > 5)
            {
                frame = 0;
            }
        }

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}
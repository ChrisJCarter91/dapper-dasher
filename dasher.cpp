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

    // Nebula Variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height};

    // Nebula X Velocity (pixels/second)
    int nebVel{-600};

    // Scarfy Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec{0, 0, scarfy.width/6, scarfy.height};
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

        //Update Nebula Position
        nebPos.x += nebVel * dT;

        // Update Scarfy Position
        scarfyPos.y += velocity * dT;

        runningTime += dT;

        if (!isInAir)
        {
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
        }
        

        //Draw Nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
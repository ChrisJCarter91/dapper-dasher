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

    Rectangle neb2Rec{0.0, 0.0, nebula.width/8, nebula.height/8};
    Vector2 neb2Pos{windowWidth + 300, windowHeight - nebRec.height};

    // Nebula animation variables
    int nebFrame{};
    const float nebUpdateTime(1.0/12.0);
    float nebRunningTime{};

    int neb2Frame{};
    const float neb2UpdateTime(1.0/16.0);
    float neb2RunningTime{};

    // Nebula X Velocity (pixels/second)
    int nebVel{-300};

    // Scarfy Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    // animation frame
    int frame{};
    // Amount of time before we update the animation frame
    const float updateTime{1.0/12.0};
    float runningTime{};

    // is rectangle in the air?
    bool isInAir {};
    // jump velocity (pixels/s)
    const int jumpVel{-600};

    int velocity{0};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Delta time (time since last frame)
        const float dT{GetFrameTime()};

        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // Perform ground check
        if (scarfyPos.y >= windowHeight - scarfyRec.height)
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

        // Update 2nd Nebula position
        neb2Pos.x += nebVel * dT;

        // Update Scarfy Position
        scarfyPos.y += velocity * dT;

        // Update Scarfy animation frame
        if (!isInAir)
        {
            // Update Running time
            runningTime += dT;
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

        // Update nebula animation frame
        nebRunningTime += dT;
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0;
            nebRec.x = nebFrame * nebRec.width;
            nebFrame++;
            if (nebFrame > 7)
            {
                frame = 0;
            }
        }

        // Update nebula 2 animation frame
        neb2RunningTime += dT;
        if (neb2RunningTime >= neb2UpdateTime)
        {
            neb2RunningTime = 0.0;
            neb2Rec.x = neb2Frame * neb2Rec.width;
            neb2Frame++;
            if (neb2Frame > 7)
            {
                neb2Frame = 0;
            }
        }

        //Draw Nebula
        DrawTextureRec(nebula, nebRec, nebPos, WHITE);

        // Draw the second nebula
        DrawTextureRec(nebula, neb2Rec, neb2Pos, RED);

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        // Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
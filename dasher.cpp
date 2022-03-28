#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    // Window Dimensions
    int windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;

    // Initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper-Dasher!");

    // Acceleration due to gravity (pixels/s/s)
    const int gravity{1'000};

    // Nebula Variables
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula
    AnimData nebData{ 
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {windowDimensions[0], windowDimensions[1] - nebula.height/8}, // Vector2 pos
        0, // int frame
        1.0/12.0, // float updateTime
        0 // float runningTime
        };

    AnimData neb2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {windowDimensions[0] + 300, windowDimensions[1] - nebula.height/8}, // Vector2 pos
        0, // int frame
        1.0/16.0, // float updateTime
        0.0 // float runningTime
    };

    AnimData nebulae[2]{ nebData, neb2Data };

    // Nebula X Velocity (pixels/second)
    int nebVel{-200};

    // Scarfy Variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

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
        if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rec.height)
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
        nebulae[0].pos.x += nebVel * dT;

        // Update 2nd Nebula position
        nebulae[1].pos.x += nebVel * dT;

        // Update Scarfy Position
        scarfyData.pos.y += velocity * dT;

        // Update Scarfy animation frame
        if (!isInAir)
        {
            // Update Running time
            scarfyData.runningTime += dT;
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;
                // Update animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }
        }

        // Update nebula animation frame
        nebulae[0].runningTime += dT;
        if (nebulae[0].runningTime >= nebulae[0].updateTime)
        {
            nebulae[0].runningTime = 0.0;
            nebulae[0].rec.x = nebulae[0].frame * nebulae[0].rec.width;
            nebulae[0].frame++;
            if (nebulae[0].frame > 7)
            {
                nebulae[0].frame = 0;
            }
        }

        // Update nebula 2 animation frame
        nebulae[2].runningTime += dT;
        if (nebulae[2].runningTime >= nebulae[2].updateTime)
        {
            nebulae[2].runningTime = 0.0;
            nebulae[2].rec.x = nebulae[2].frame * nebulae[2].rec.width;
            nebulae[2].frame++;
            if (nebulae[2].frame > 7)
            {
                nebulae[2].frame = 0;
            }
        }

        //Draw Nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);

        // Draw the second nebula
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
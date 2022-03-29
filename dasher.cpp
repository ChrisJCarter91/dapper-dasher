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

    AnimData nebulae[3]{};
    for (int i = 0; i < 3; i++)
    {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 0.0;
    }

    nebulae[0].pos.x = windowDimensions[0];
    nebulae[1].pos.x = windowDimensions[0] + 300;
    nebulae[2].pos.x = windowDimensions[0] + 600;

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
        nebulae[1].runningTime += dT;
        if (nebulae[1].runningTime >= nebulae[1].updateTime)
        {
            nebulae[1].runningTime = 0.0;
            nebulae[1].rec.x = nebulae[1].frame * nebulae[1].rec.width;
            nebulae[1].frame++;
            if (nebulae[1].frame > 7)
            {
                nebulae[1].frame = 0;
            }
        }

        //Draw Nebula
        DrawTextureRec(nebula, nebulae[0].rec, nebulae[0].pos, WHITE);

        // Draw the second nebula
        DrawTextureRec(nebula, nebulae[1].rec, nebulae[1].pos, RED);

        // Draw Scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // Stop Drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}
#include <stdio.h>
#include "raylib/include/raylib.h"
#include "raylib/include/raymath.h"

#define WIDTH 800
#define HEIGHT 600

int main(void) {
    InitWindow(WIDTH, HEIGHT, "Julia Set");

    Shader shader = LoadShader(0, "fractal.fs");
    
    int resolutionLoc = GetShaderLocation(shader, "resolution");
    int cLoc = GetShaderLocation(shader, "c");
    int offsetLoc = GetShaderLocation(shader, "offset");
    int zoomLoc = GetShaderLocation(shader, "zoom");
    
    Vector2 resolution = { (float)WIDTH, (float)HEIGHT };
    Vector2 c = { -0.7f, 0.27015f };
    Vector2 offset = { 0.0f, 0.0f };
    float zoom = 1.0f;

    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        float renderWidth = (float)GetRenderWidth();
        float renderHeight = (float)GetRenderHeight();
        Vector2 currentRes = { renderWidth, renderHeight };
        SetShaderValue(shader, resolutionLoc, &currentRes, SHADER_UNIFORM_VEC2);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition();
            c.x = (mouse.x / WIDTH - 0.5f) * 4.0f;
            c.y = (mouse.y / HEIGHT - 0.5f) * 4.0f;
        }

        if (IsKeyDown(KEY_UP)) zoom *= 1.02f;
        if (IsKeyDown(KEY_DOWN)) zoom /= 1.02f;

        SetShaderValue(shader, cLoc, &c, SHADER_UNIFORM_VEC2);
        SetShaderValue(shader, offsetLoc, &offset, SHADER_UNIFORM_VEC2);
        SetShaderValue(shader, zoomLoc, &zoom, SHADER_UNIFORM_FLOAT);

        BeginDrawing();
        ClearBackground(BLACK);
        
        BeginShaderMode(shader);
        DrawRectangle(0, 0, WIDTH, HEIGHT, WHITE);
        EndShaderMode();
        
        DrawText(TextFormat("C: %.4f + %.4fi", c.x, c.y), 10, 40, 20, WHITE);
        DrawFPS(WIDTH - 80, 10);

        EndDrawing();
    }

    UnloadShader(shader);
    CloseWindow();
    return 0;
}

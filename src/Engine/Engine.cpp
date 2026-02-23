/*
 * @Author: Martin Bonte
 * @Date: 2026-02-15 12:05:56 
 * @Last Modified by: Martin Bonte
 * @Last Modified time: 2026-02-15 12:55:33
 */

#include "Engine.hpp"
#include "raylib.h"

Engine::Engine()
{
    InitWindow(1920, 1080, "Particle Engine");
    SetTargetFPS(60);

    Image gradient = GenImageGradientRadial(128, 128, 0.3f, WHITE, BLANK); 
    _particleTexture = LoadTextureFromImage(gradient);
    UnloadImage(gradient);

    _blurShader = LoadShader(nullptr, "../shaders/bloom.frag");
    _dirLoc = GetShaderLocation(_blurShader, "dir");
    _resLoc = GetShaderLocation(_blurShader, "resolution");
    _radLoc = GetShaderLocation(_blurShader, "radius");

    _targetA = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    _targetB = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    _camera = { 0 };
    _camera.position = { 0.0f, 50.0f, 100.0f };
    _camera.target = { 0.0f, 0.0f, 0.0f };
    _camera.up = { 0.0f, 1.0f, 0.0f };
    _camera.fovy = 45.0f;
    _camera.projection = CAMERA_PERSPECTIVE;

    _ps = std::make_shared<ParticleSystem>(100000);
}

Engine::~Engine()
{
    UnloadTexture(_particleTexture);
    UnloadShader(_blurShader);
    CloseWindow();
}

void Engine::Update() {
    UpdateCamera(&_camera, CAMERA_FREE);

    if (IsKeyPressed(KEY_ONE)) _ps->SetTechnique("red");
    if (IsKeyPressed(KEY_TWO)) _ps->SetTechnique("void");
    if (IsKeyPressed(KEY_THREE)) _ps->SetTechnique("purple");
    if (IsKeyPressed(KEY_FOUR)) _ps->SetTechnique("shrine");
    if (IsKeyPressed(KEY_FIVE)) _ps->SetTechnique("blackhole");

    _ps->Update(GetFrameTime());
}

void Engine::Draw() {
    float width = (float)GetScreenWidth();
    float height = (float)GetScreenHeight();
    float radius = 30.0f;

    BeginTextureMode(_targetA);
        ClearBackground(BLACK);
        BeginMode3D(_camera);
            _ps->Draw(); 
        EndMode3D();
    EndTextureMode();

    BeginTextureMode(_targetB);
        ClearBackground(BLACK);
        BeginShaderMode(_blurShader);
            Vector2 dirH = {1.0f, 0.0f};
            Vector2 res = {width, height};
            SetShaderValue(_blurShader, _dirLoc, &dirH, SHADER_UNIFORM_VEC2);
            SetShaderValue(_blurShader, _resLoc, &res, SHADER_UNIFORM_VEC2);
            SetShaderValue(_blurShader, _radLoc, &radius, SHADER_UNIFORM_FLOAT);

            DrawTextureRec(_targetA.texture, (Rectangle){0,0,width,-height}, (Vector2){0,0}, WHITE);
        EndShaderMode();
    EndTextureMode();

    BeginDrawing();
        ClearBackground(BLACK);
        
        DrawTextureRec(_targetA.texture, (Rectangle){0,0,width,-height}, (Vector2){0,0}, WHITE);

        BeginBlendMode(BLEND_ADDITIVE);
            BeginShaderMode(_blurShader);
                Vector2 dirV = {0.0f, 1.0f};
                SetShaderValue(_blurShader, _dirLoc, &dirV, SHADER_UNIFORM_VEC2);
                DrawTextureRec(_targetB.texture, (Rectangle){0,0,width,-height}, (Vector2){0,0}, WHITE);
            EndShaderMode();
        EndBlendMode();
        
        DrawFPS(10, 10);
    EndDrawing();
}

void Engine::Run()
{
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
}
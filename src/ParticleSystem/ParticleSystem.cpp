/*
 * @Author: Martin Bonte
 * @Date: 2026-02-15 12:06:16 
 * @Last Modified by: Martin Bonte
 * @Last Modified time: 2026-02-15 12:54:22
 */

#include "ParticleSystem.hpp"
#include "Techniques.hpp"
#include "raylib.h"
#include <raymath.h>

Techniques* techManager;
std::string currentTech = "red";

ParticleSystem::ParticleSystem(int count)
    : _count(count) {
    techManager = new Techniques(count);
    for (int i = 0; i < count; i++) {
        TargetData data = techManager->getParticleData(i, currentTech);
        particles.push_back({ 
            data.position, 
            data.position, 
            data.color, 
            data.color, 
            data.size, 
            data.size,
            (float)GetRandomValue(0, 1000) / 100.0f
        });
    }
}

void ParticleSystem::Update(float deltaTime)
{
    float time = GetTime();

    for (auto& p : particles) {
        p.position = Vector3Lerp(p.position, p.target, 0.05f);

        float waveX = sinf(time * 1.2f + p.noiseSeed) * 0.05f;
        float waveY = cosf(time * 1.5f + p.noiseSeed * 1.0f) * 0.1f;
        float waveZ = sinf(time * 0.8f + p.noiseSeed * 0.5f) * 0.1f;

        p.position.x += waveX;
        p.position.y += waveY;
        p.position.z += waveZ;

        p.color.r += (p.targetColor.r - p.color.r) * 0.05f;
        p.color.g += (p.targetColor.g - p.color.g) * 0.05f;
        p.color.b += (p.targetColor.b - p.color.b) * 0.05f;
        p.color.a += (p.targetColor.a - p.color.a) * 0.05f;
        p.size += (p.targetSize - p.size) * 0.05f;
    }
}

void ParticleSystem::SetTechnique(std::string name)
{
    currentTech = name;
    for (int i = 0; i < _count; i++) {
        TargetData data = techManager->getParticleData(i, currentTech);
        particles[i].target = data.position;
        particles[i].targetColor = data.color;
        particles[i].targetSize = data.size;
    }
}

void ParticleSystem::Draw()
{
    BeginBlendMode(BLEND_ADDITIVE);

    for (auto& p : particles) {
        if (p.color.a > 0)
            DrawCube(p.position, p.size, p.size, p.size, p.color);
    }
    EndBlendMode();
}
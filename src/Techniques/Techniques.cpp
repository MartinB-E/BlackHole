/*
 * @Author: Martin Bonte 
 * @Date: 2026-02-15 12:13:04 
 * @Last Modified by: Martin Bonte
 * @Last Modified time: 2026-02-15 12:56:53
 */

#include "Techniques.hpp"
#include <cmath>

Techniques::Techniques(int count)
    : _count(count)
{
}

TargetData Techniques::getParticleData(int i, std::string technique)
{
    if (technique == "red")     return getRed(i);
    if (technique == "void")    return getVoid(i);
    if (technique == "purple")  return getPurple(i);
    if (technique == "shrine")  return getShrine(i);
    if (technique == "blackhole")  return getBlackHole(i);
    return getRed(i);
}

TargetData Techniques::getRed(int i)
{
    if (i < _count * 0.1f) {
        float r = randF() * 9.0f;
        float theta = randF() * 6.28f;
        float phi = acosf(2.0f * randF() - 1.0f);
        Vector3 pos = { r * sinf(phi) * cosf(theta), r * sinf(phi) * sinf(theta), r * cosf(phi) };
        return { pos, {255, 25, 25, 255}, 0.5f };
    } else if (i < _count * 0.7f) {
        int arm_Count = 3;
        float t = (float)i / _count;
        float angle = t * 15.0f + ((i % arm_Count) * (PI * 2.0f / arm_Count));
        float radius = 2.0f + (t * 40.0f);
        Vector3 pos = { radius * cosf(angle), radius * sinf(angle), (randF() - 0.5f) * (10.0f * t) - i * 0.0002f };
        return { pos, {180, 0, 0, 255}, 0.2f };
    }
    float r = 40.0f + randF() * 60.0f;
    float theta = randF() * 6.28f;
    float phi = acosf(2.0f * randF() - 1.0f);
    Vector3 pos = { r * sinf(phi) * cosf(theta), r * sinf(phi) * sinf(theta), r * cosf(phi) };
    return { pos, {100, 0, 0, 255}, 0.1f };
}

TargetData Techniques::getVoid(int i)
{
    if (i < _count * 0.15f) {
        float angle = randF() * PI * 2.0f;
        Vector3 pos = { 26.0f * cosf(angle), 26.0f * sinf(angle), (randF() - 0.5f) * 1.0f };
        return { pos, WHITE, 0.4f };
    } else {
        float radius = 30.0f + randF() * 90.0f;
        float theta = randF() * PI * 2.0f;
        float phi = acosf(2.0f * randF() - 1.0f);
        Vector3 pos = { radius * sinf(phi) * cosf(theta), radius * sinf(phi) * sinf(theta), radius * cosf(phi) };
        return { pos, {25, 150, 255, 255}, 0.15f };
    }
}

TargetData Techniques::getPurple(int i)
{
    if (randF() > 0.8f) {
        Vector3 pos = { (randF() - 0.5f) * 100.0f, (randF() - 0.5f) * 100.0f, (randF() - 0.5f) * 100.0f };
        return { pos, {128, 128, 180, 255}, 0.2f };
    }
    float r = 20.0f;
    float theta = randF() * PI * 2.0f;
    float phi = acosf(2.0f * randF() - 1.0f);
    Vector3 pos = { r * sinf(phi) * cosf(theta), r * sinf(phi) * sinf(theta), r * cosf(phi) };
    return { pos, {150, 50, 255, 255}, 0.4f };
}

TargetData Techniques::getShrine(int i)
{
    if (i < _count * 0.3f) {
        return { {(randF()-0.5f)*80, -15, (randF()-0.5f)*80}, {100, 0, 0, 255}, 0.2f };
    } else if (i < _count * 0.4f) {
        float px = ((i%4)<2?1.0f:-1.0f)*12.0f;
        float pz = ((i%4)%2==0?1.0f:-1.0f)*8.0f;
        return { {px+(randF()-0.5f)*2, -15+randF()*30, pz+(randF()-0.5f)*2}, {50, 50, 50, 255}, 0.2f };
    } else if (i < _count * 0.6f) {
        float t = randF() * PI * 2.0f;
        float rad = randF() * 30.0f;
        float curve = powf(rad/30.0f, 2.0f) * 10.0f;
        return { {rad*cosf(t), 15.0f - curve + (randF()*2.0f), rad*sinf(t)*0.6f}, {150, 0, 0, 255}, 0.2f };
    }
    return { {0,0,0}, {0,0,0,0}, 0.0f };
}

TargetData Techniques::getBlackHole(int i)
{
    float t = (float)i / _count;

    if (t < 0.20f) {
        float r = randF() * 12.0f;
        float theta = randF() * 2.0f * PI;
        float phi = acosf(2.0f * randF() - 1.0f);
        
        Vector3 pos = { 
            r * sinf(phi) * cosf(theta), 
            r * sinf(phi) * sinf(theta), 
            r * cosf(phi) 
        };

        return { pos, {0, 0, 0, 255}, 0.5f }; 
    }

    if (t < 0.90f) {
        float innerRadius = 16.0f;
        float outerRadius = 50.0f;
        
        float r = innerRadius + powf(randF(), 2.0f) * (outerRadius - innerRadius);
        float theta = randF() * 2.0f * PI;
        
        float y = (randF() - 0.5f) * 1.5f;

        Vector3 pos = { 
            r * cosf(theta), 
            y, 
            r * sinf(theta) 
        };

        float distFactor = (r - innerRadius) / (outerRadius - innerRadius);
        
        unsigned char red = 255;
        unsigned char green = (unsigned char)(255 * (1.0f - distFactor * 0.5f));
        unsigned char blue = (unsigned char)(255 * (1.0f - distFactor * 0.5f));

        return { pos, {red, green, blue, 255}, 0.25f };
    }

    return { {0,0,0}, {0,0,0,0}, 0.0f };
}
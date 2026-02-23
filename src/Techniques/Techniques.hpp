/*
 * @Author: Martin Bonte 
 * @Date: 2026-02-15 12:13:02 
 * @Last Modified by: Martin Bonte
 * @Last Modified time: 2026-02-15 12:49:28
 */

#pragma once
    
    #include <raylib.h>
    #include <string>

struct TargetData {
    Vector3 position;
    Color color;
    float size;
};

class Techniques {
    public:
        Techniques(int count);

        TargetData getParticleData(int i, std::string technique);

    private:
        int _count;

        float randF() { return (float)GetRandomValue(0, 10000) / 10000.0f; }

        TargetData getRed(int i);
        TargetData getVoid(int i);
        TargetData getPurple(int i);
        TargetData getShrine(int i);
        TargetData getBlackHole(int i);
};
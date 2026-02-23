/*
 * @Author: Martin Bonte
 * @Date: 2026-02-15 12:06:12 
 * @Last Modified by: Martin Bonte
 * @Last Modified time: 2026-02-15 12:31:10
 */

#pragma once

    #include <raylib.h>

struct Particle {
    Vector3 position;
    Vector3 target;
    Color color;
    Color targetColor;
    float size;
    float targetSize;
    float noiseSeed;
};
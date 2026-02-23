/*
 * @Author: Martin Bonte
 * @Date: 2026-02-15 12:06:20 
 * @Last Modified by: Martin Bonte
 * @Last Modified time: 2026-02-15 12:25:05
 */

#pragma once
    
    #include "Particle.hpp"
    #include <vector>
    #include <string>

class ParticleSystem {
    public:
        ParticleSystem(int count);

        void Draw();
        void Update(float deltaTime);
        void SetTechnique(std::string name);

    private:
        int _count;
        std::vector<Particle> particles;
};
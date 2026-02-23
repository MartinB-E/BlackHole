/*
 * @Author: Martin Bonte
 * @Date: 2026-02-15 12:06:05 
 * @Last Modified by: Martin Bonte
 * @Last Modified time: 2026-02-15 12:40:44
 */

#pragma once

    #include <memory>
    #include <raylib.h>
    #include "ParticleSystem.hpp"

class Engine {
    public:
        Engine();
        ~Engine();

        void Run();

    private:
        void Draw();
        void Update();

        Shader _blurShader;
        RenderTexture2D _targetA;
        RenderTexture2D _targetB;
        
        int _dirLoc;
        int _resLoc;
        int _radLoc;

        Camera3D _camera;
        Texture2D _particleTexture; 
        std::shared_ptr<ParticleSystem> _ps;
};
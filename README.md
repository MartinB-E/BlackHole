# BlackHole — particle system

A real-time 3D particle system in C++ and raylib: 100,000 particles morph between five procedural formations, rendered with additive blending and a GPU bloom pass.

[À COMPLÉTER : capture — GIF switching between the five formations with keys 1 → 5]

## Features

- **100,000 particles**, each one easing towards a target position, colour and size, with a per-particle noise wobble so the shapes stay alive
- **Five procedural formations**, switched live with the keys `1` to `5`; the particles fly from one shape to the next:
  1. a red core with three spiral arms
  2. a white ring inside a blue sphere of particles
  3. a dense purple sphere with scattered particles
  4. a shrine-like structure (floor, pillars and a curved roof)
  5. a black hole with an accretion disk
- **Bloom post-processing**: the scene is rendered to a texture, blurred with a separable 9-tap Gaussian shader (horizontal then vertical pass) and added back on top
- Free 3D camera and FPS counter

## Tech stack

C++17 · raylib 5.0 (fetched automatically by CMake) · GLSL 330 · CMake

## Build & run

Requirements: CMake ≥ 3.11, a C++17 compiler, Git, and the usual raylib system dependencies on Linux (X11, OpenGL).

```bash
git clone https://github.com/MartinB-E/BlackHole.git
cd BlackHole
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

cd build                 # the shader is loaded from ../shaders
./JJK_ParticleSystem
```

Controls: `1`–`5` change formation, mouse and `W` `A` `S` `D` move the camera, `Esc` quits.

## Architecture

- `Engine` — window, camera, render targets and the two-pass bloom pipeline
- `ParticleSystem` — owns the particles, interpolates them towards their targets every frame and draws them with additive blending
- `Techniques` — pure functions that give the target position, colour and size of particle *i* for each formation (spheres, spirals, rings and disks in polar coordinates)
- `shaders/bloom.frag` — directional Gaussian blur used for both bloom passes

## Context

Personal project, February 2026, built alone. The formations are inspired by the techniques of the manga *Jujutsu Kaisen*.

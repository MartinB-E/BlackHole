cmake_minimum_required(VERSION 3.11)
project(JJK_ParticleSystem)

set(CMAKE_POLICY_DEFAULT_CMP0000 OLD)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)


set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

set(FETCHCONTENT_QUIET OFF) 

message(STATUS "Téléchargement de Raylib... (Patientez, cela peut prendre du temps)")

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        5.0
  GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(raylib)

include_directories(
    src/Engine
    src/Particle
    src/Techniques
    src/ParticleSystem
)

add_executable(JJK_ParticleSystem 
    src/main.cpp
    src/Engine/Engine.cpp
    src/Techniques/Techniques.cpp
    src/ParticleSystem/ParticleSystem.cpp
)


target_link_libraries(JJK_ParticleSystem raylib)

if(WIN32)
    set_target_properties(JJK_ParticleSystem PROPERTIES WIN32_EXECUTABLE ON)
endif()
cmake_minimum_required(VERSION 3.14)
project(PhysicsEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.3.8
)
FetchContent_MakeAvailable(glfw)

find_package(OpenGL REQUIRED)

add_executable(PhysicsEngine 
    src/main.cpp
    src/physics/Vector3.cpp
    src/physics/Particle.cpp
    src/physics/GravityGenerator.cpp
    src/physics/ParticleSpring.cpp
    src/physics/ParticleContact.cpp
    src/physics/ParticleContactResolver.cpp
    src/physics/Camera.cpp
)

target_link_libraries(PhysicsEngine PRIVATE glfw OpenGL::GL)

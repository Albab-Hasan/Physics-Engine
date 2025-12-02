# Physics Engine

I'm building a 3D physics engine in C++ from scratch. The goal is to understand the math and logic behind physical simulations by implementing them myself.

## Getting Started

You'll need CMake and a C++ compiler to build this. I'm using GLFW for window management and OpenGL for rendering.

### Build Instructions

1.  Clone the repo.
2.  Create a build directory: `mkdir build`
3.  Run CMake: `cd build && cmake ..`
4.  Build: `cmake --build .`

## Current Status

I've implemented the core physics system with particle dynamics. The engine can simulate particles with position, velocity, and acceleration. There's a basic gravity simulation that shows a particle falling and bouncing off the ground.

### What's Working
- Vector3 math class for 3D calculations
- Particle class with Euler integration
- Gravity simulation
- Simple collision detection with ground plane
- Basic OpenGL rendering

### Next Steps
- Implement a force accumulator system
- Add multiple particles
- Create 3D sphere rendering
- Build a proper camera system

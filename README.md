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

I've built a working particle physics system that can simulate multiple particles, different types of forces, and collisions. The engine uses a force accumulator pattern and a contact resolution system.

### What's Working
- Vector3 math class for 3D calculations
- Particle class with Euler integration
- Force accumulator system
- Force generator interface
- Gravity and Spring force generators
- Particle contact resolution system
- Multiple particles with random initial conditions
- Collision detection (particle-particle and particle-ground)
- Basic OpenGL rendering

### Recent Progress
Implemented a collision resolution system. Particles now bounce off each other and the ground with a defined coefficient of restitution. The demo shows 10 particles bouncing around in a confined space.

### Next Steps
- Create 3D sphere rendering instead of points
- Build a proper camera system
- Implement more complex force generators (e.g., drag, buoyancy)

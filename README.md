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

I've built a working particle physics system with 3D visualization. The engine supports multiple particles, various forces (gravity, springs), collision resolution, and renders particles as 3D spheres with lighting.

### What's Working
- Vector3 math class for 3D calculations
- Particle class with Euler integration
- Force accumulator system
- Force generator interface
- Gravity and Spring force generators
- Particle contact resolution system
- Multiple particles with random initial conditions
- Collision detection (particle-particle and particle-ground)
- 3D Sphere rendering with lighting

### Recent Progress
Replaced the basic point rendering with 3D spheres. Implemented a procedural sphere mesh generator and enabled OpenGL lighting to give the particles volume and depth.

### Next Steps
- Build a proper camera system
- Implement more complex force generators (e.g., drag, buoyancy)
- Add user interaction (mouse picking)

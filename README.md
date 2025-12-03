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

I've built a working particle physics system that can simulate multiple particles and different types of forces. The engine uses a force accumulator pattern, which makes it easy to add new force generators like gravity and springs.

### What's Working
- Vector3 math class for 3D calculations
- Particle class with Euler integration
- Force accumulator system
- Force generator interface
- Gravity force generator
- Spring force generator
- Multiple particles
- Simple collision detection with ground plane
- Basic OpenGL rendering

### Recent Progress
Implemented a spring force generator based on Hooke's Law. The current demo shows a particle suspended from a fixed point by a spring, bouncing up and down under the influence of gravity and elasticity.

### Next Steps
- Add particle-to-particle collisions
- Create 3D sphere rendering instead of points
- Build a proper camera system

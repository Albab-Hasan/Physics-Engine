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

I've built a working particle physics system with 3D visualization and navigation. The engine supports multiple particles, various forces (gravity, springs, drag), collision resolution, and allows the user to fly around the scene.

### What's Working
- Vector3 math class for 3D calculations
- Particle class with Euler integration
- Force accumulator system
- Force generator interface
- Gravity, Spring, and Drag force generators
- Particle contact resolution system
- Multiple particles with random initial conditions
- Collision detection (particle-particle and particle-ground)
- 3D Sphere rendering with lighting
- First-person fly camera (WASD + Mouse)
- Full screen mode

### Recent Progress
Implemented a drag force generator to simulate air resistance. This adds realism by slowing down particles over time, preventing them from accelerating indefinitely.

### Next Steps
- Implement more complex force generators (e.g., buoyancy)
- Add user interaction (mouse picking)
- Optimize collision detection (spatial partitioning)

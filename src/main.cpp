#include "physics/GravityGenerator.h"
#include "physics/Particle.h"
#include "physics/ParticleSpring.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>


int main() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  GLFWwindow *window = glfwCreateWindow(800, 600, "Physics Engine", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  // Create particles
  Particle p1; // Fixed anchor
  p1.position = Vector3(0.0f, 0.8f, 0.0f);
  p1.setMass(0.0f); // Infinite mass

  Particle p2; // Moving particle
  p2.position = Vector3(0.0f, 0.0f, 0.0f);
  p2.setMass(1.0f);

  // Create force generators
  GravityGenerator gravity(Vector3(0.0f, -9.8f, 0.0f));
  ParticleSpring spring(&p1, 10.0f,
                        0.5f); // Spring constant 10, rest length 0.5

  double lastTime = glfwGetTime();

  while (!glfwWindowShouldClose(window)) {
    double currentTime = glfwGetTime();
    float deltaTime = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    // Update forces
    p2.clearAccumulator();
    gravity.updateForce(&p2, deltaTime);
    spring.updateForce(&p2, deltaTime);

    // Integrate
    p2.integrate(deltaTime);

    // Render
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw spring line
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(p1.position.x, p1.position.y, p1.position.z);
    glVertex3f(p2.position.x, p2.position.y, p2.position.z);
    glEnd();

    // Draw particles
    glPointSize(10.0f);
    glBegin(GL_POINTS);

    // Anchor (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(p1.position.x, p1.position.y, p1.position.z);

    // Bob (White)
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(p2.position.x, p2.position.y, p2.position.z);

    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

#include "physics/GravityGenerator.h"
#include "physics/Particle.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <ctime>
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

  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  std::vector<Particle> particles;
  const int particleCount = 20;

  for (int i = 0; i < particleCount; ++i) {
    Particle p;
    p.position = Vector3((std::rand() % 200 - 100) / 100.0f,
                         (std::rand() % 100 + 50) / 100.0f, 0.0f);
    p.velocity = Vector3((std::rand() % 100 - 50) / 100.0f,
                         (std::rand() % 100 - 50) / 100.0f, 0.0f);
    p.setMass(1.0f);
    particles.push_back(p);
  }

  GravityGenerator gravity(Vector3(0.0f, -9.8f, 0.0f));

  double lastTime = glfwGetTime();

  while (!glfwWindowShouldClose(window)) {
    double currentTime = glfwGetTime();
    float deltaTime = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    for (auto &particle : particles) {
      particle.clearAccumulator();
      gravity.updateForce(&particle, deltaTime);
      particle.integrate(deltaTime);

      if (particle.position.y < -1.0f) {
        particle.position.y = -1.0f;
        particle.velocity.y *= -0.8f;
      }
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(8.0f);
    glBegin(GL_POINTS);
    for (const auto &particle : particles) {
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex3f(particle.position.x, particle.position.y, particle.position.z);
    }
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

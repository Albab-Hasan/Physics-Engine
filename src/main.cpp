#include "physics/Particle.h"
#include <GLFW/glfw3.h>
#include <iostream>


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

  Particle particle;
  particle.position = Vector3(0.0f, 0.5f, 0.0f);
  particle.velocity = Vector3(0.1f, 0.0f, 0.0f);
  particle.acceleration = Vector3(0.0f, -9.8f, 0.0f);
  particle.setMass(1.0f);

  double lastTime = glfwGetTime();

  while (!glfwWindowShouldClose(window)) {
    double currentTime = glfwGetTime();
    float deltaTime = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    particle.integrate(deltaTime);

    if (particle.position.y < -1.0f) {
      particle.position.y = -1.0f;
      particle.velocity.y *= -0.8f;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(particle.position.x, particle.position.y, particle.position.z);
    glEnd();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

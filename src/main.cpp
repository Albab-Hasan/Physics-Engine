#include "physics/GravityGenerator.h"
#include "physics/Particle.h"
#include "physics/ParticleContact.h"
#include "physics/ParticleContactResolver.h"
#include "physics/ParticleSpring.h"
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
  const int particleCount = 10;

  // Create particles with random positions
  for (int i = 0; i < particleCount; ++i) {
    Particle p;
    p.position = Vector3((std::rand() % 180 - 90) / 100.0f,
                         (std::rand() % 100 + 50) / 100.0f, 0.0f);
    p.velocity = Vector3((std::rand() % 100 - 50) / 100.0f,
                         (std::rand() % 100 - 50) / 100.0f, 0.0f);
    p.setMass(1.0f);
    p.damping = 0.99f;
    particles.push_back(p);
  }

  GravityGenerator gravity(Vector3(0.0f, -9.8f, 0.0f));
  ParticleContactResolver resolver(particleCount * 2);

  // Collision data
  std::vector<ParticleContact> contacts;
  const float particleRadius = 0.05f;

  double lastTime = glfwGetTime();

  while (!glfwWindowShouldClose(window)) {
    double currentTime = glfwGetTime();
    float deltaTime = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    // 1. Update forces
    for (auto &particle : particles) {
      particle.clearAccumulator();
      gravity.updateForce(&particle, deltaTime);
    }

    // 2. Integrate
    for (auto &particle : particles) {
      particle.integrate(deltaTime);

      // Simple ground collision (keep particles in bounds)
      if (particle.position.y < -1.0f + particleRadius) {
        particle.position.y = -1.0f + particleRadius;
        particle.velocity.y *= -0.8f;
      }
      if (particle.position.x < -1.0f + particleRadius) {
        particle.position.x = -1.0f + particleRadius;
        particle.velocity.x *= -0.8f;
      }
      if (particle.position.x > 1.0f - particleRadius) {
        particle.position.x = 1.0f - particleRadius;
        particle.velocity.x *= -0.8f;
      }
    }

    // 3. Generate Contacts
    contacts.clear();
    for (size_t i = 0; i < particles.size(); ++i) {
      for (size_t j = i + 1; j < particles.size(); ++j) {
        Vector3 toParticle = particles[i].position - particles[j].position;
        float distance = toParticle.magnitude();
        float overlap = 2 * particleRadius - distance;

        if (overlap > 0) {
          ParticleContact contact;
          contact.particle[0] = &particles[i];
          contact.particle[1] = &particles[j];
          contact.contactNormal = toParticle.normalized();
          contact.penetration = overlap;
          contact.restitution = 0.8f; // Bounciness
          contacts.push_back(contact);
        }
      }
    }

    // 4. Resolve Contacts
    if (!contacts.empty()) {
      resolver.resolveContacts(contacts, deltaTime);
    }

    // Render
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto &particle : particles) {
      glPointSize(particleRadius * 200.0f); // Rough scale for point size
      glBegin(GL_POINTS);
      glColor3f(1.0f, 1.0f, 1.0f);
      glVertex3f(particle.position.x, particle.position.y, particle.position.z);
      glEnd();
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

#include "physics/Camera.h"
#include "physics/GravityGenerator.h"
#include "physics/Particle.h"
#include "physics/ParticleBuoyancy.h"
#include "physics/ParticleContact.h"
#include "physics/ParticleContactResolver.h"
#include "physics/ParticleDrag.h"
#include "physics/ParticleSpring.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Global camera instance
Camera camera(Vector3(0.0f, 2.0f, 10.0f));
float lastX = 400, lastY = 300;
bool firstMouse = true;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  if (height == 0)
    height = 1;
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float aspect = (float)width / (float)height;
  float fovy = 45.0f;
  float zNear = 0.1f;
  float zFar = 100.0f;
  float ymax = zNear * tan(fovy * M_PI / 360.0f);
  float xmax = ymax * aspect;
  glFrustum(-xmax, xmax, -ymax, ymax, zNear, zFar);
  glMatrixMode(GL_MODELVIEW);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset =
      lastY - ypos; // Reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  camera.processMouseMovement(xoffset, yoffset);
}

void processInput(GLFWwindow *window, float deltaTime) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.processKeyboard(0, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.processKeyboard(1, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.processKeyboard(2, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.processKeyboard(3, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    camera.processKeyboard(4, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    camera.processKeyboard(5, deltaTime);
}

void drawSphere(float radius, int slices, int stacks) {
  for (int i = 0; i < stacks; ++i) {
    float lat0 = M_PI * (-0.5 + (float)(i) / stacks);
    float z0 = radius * sin(lat0);
    float zr0 = radius * cos(lat0);

    float lat1 = M_PI * (-0.5 + (float)(i + 1) / stacks);
    float z1 = radius * sin(lat1);
    float zr1 = radius * cos(lat1);

    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= slices; ++j) {
      float lng = 2 * M_PI * (float)(j) / slices;
      float x = cos(lng);
      float y = sin(lng);

      glNormal3f(x * zr0, y * zr0, z0);
      glVertex3f(x * zr0, y * zr0, z0);
      glNormal3f(x * zr1, y * zr1, z1);
      glVertex3f(x * zr1, y * zr1, z1);
    }
    glEnd();
  }
}

int main() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
  const GLFWvidmode *mode = glfwGetVideoMode(primaryMonitor);

  glfwWindowHint(GLFW_RED_BITS, mode->redBits);
  glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
  glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

  GLFWwindow *window = glfwCreateWindow(mode->width, mode->height,
                                        "Physics Engine", primaryMonitor, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  framebuffer_size_callback(window, width, height);

  // Setup Lighting
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);

  GLfloat lightPos[] = {1.0f, 1.0f, 1.0f, 0.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

  GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

  GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

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
  ParticleDrag drag(0.1f, 0.01f);
  float waterHeight = 0.0f;
  ParticleBuoyancy buoyancy(0.05f, 0.001f,
                            waterHeight); // maxDepth, volume, waterHeight
  ParticleContactResolver resolver(particleCount * 2);

  // Collision data
  std::vector<ParticleContact> contacts;
  const float particleRadius = 0.05f;

  double lastTime = glfwGetTime();

  while (!glfwWindowShouldClose(window)) {
    double currentTime = glfwGetTime();
    float deltaTime = static_cast<float>(currentTime - lastTime);
    lastTime = currentTime;

    processInput(window, deltaTime);

    // 1. Update forces
    for (auto &particle : particles) {
      particle.clearAccumulator();
      gravity.updateForce(&particle, deltaTime);
      drag.updateForce(&particle, deltaTime);
      buoyancy.updateForce(&particle, deltaTime);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    camera.apply();

    // Draw Water Plane
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
    glColor4f(0.0f, 0.0f, 1.0f, 0.5f); // Semi-transparent blue
    glVertex3f(-20.0f, waterHeight, -20.0f);
    glVertex3f(-20.0f, waterHeight, 20.0f);
    glVertex3f(20.0f, waterHeight, 20.0f);
    glVertex3f(20.0f, waterHeight, -20.0f);
    glEnd();
    glDisable(GL_BLEND);

    for (const auto &particle : particles) {
      glPushMatrix();
      glTranslatef(particle.position.x, particle.position.y,
                   particle.position.z);
      glColor3f(0.7f, 0.7f, 0.7f); // Gray particles
      drawSphere(particleRadius, 40, 40);
      glPopMatrix();
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

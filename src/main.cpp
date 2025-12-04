#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "physics/Particle.h"
#include "physics/GravityGenerator.h"
#include "physics/ParticleSpring.h"
#include "physics/ParticleContact.h"
#include "physics/ParticleContactResolver.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

    GLFWwindow* window = glfwCreateWindow(800, 600, "Physics Engine", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Setup Lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D

    GLfloat lightPos[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::vector<Particle> particles;
    const int particleCount = 10;
    
    // Create particles with random positions
    for (int i = 0; i < particleCount; ++i) {
        Particle p;
        p.position = Vector3(
            (std::rand() % 180 - 90) / 100.0f,
            (std::rand() % 100 + 50) / 100.0f,
            0.0f
        );
        p.velocity = Vector3(
            (std::rand() % 100 - 50) / 100.0f,
            (std::rand() % 100 - 50) / 100.0f,
            0.0f
        );
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
        for (auto& particle : particles) {
            particle.clearAccumulator();
            gravity.updateForce(&particle, deltaTime);
        }

        // 2. Integrate
        for (auto& particle : particles) {
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear depth buffer too

        for (const auto& particle : particles) {
            glPushMatrix();
            glTranslatef(particle.position.x, particle.position.y, particle.position.z);
            glColor3f(1.0f, 0.5f, 0.0f); // Orange particles
            drawSphere(particleRadius, 20, 20);
            glPopMatrix();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

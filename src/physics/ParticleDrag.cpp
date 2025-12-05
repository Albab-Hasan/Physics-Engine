#include "ParticleDrag.h"
#include "Particle.h"

ParticleDrag::ParticleDrag(float k1, float k2) : k1(k1), k2(k2) {}

void ParticleDrag::updateForce(Particle *particle, float duration) {
  Vector3 force;
  force = particle->velocity;

  // Calculate the total drag coefficient
  float dragCoeff = force.magnitude();
  dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

  // Calculate the final force and apply it
  force.normalize();
  force *= -dragCoeff;
  particle->addForce(force);
}

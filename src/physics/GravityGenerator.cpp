#include "GravityGenerator.h"
#include "Particle.h"

GravityGenerator::GravityGenerator(const Vector3 &gravity) : gravity(gravity) {}

void GravityGenerator::updateForce(Particle *particle, float duration) {
  if (particle->inverseMass <= 0.0f)
    return;

  particle->addForce(gravity * particle->getMass());
}

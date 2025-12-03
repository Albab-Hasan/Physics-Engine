#include "ParticleSpring.h"
#include <cmath>

ParticleSpring::ParticleSpring(Particle *other, float springConstant,
                               float restLength)
    : other(other), springConstant(springConstant), restLength(restLength) {}

void ParticleSpring::updateForce(Particle *particle, float duration) {
  Vector3 force;
  force = particle->position;
  force -= other->position;

  float magnitude = force.magnitude();
  magnitude = std::abs(magnitude - restLength);
  magnitude *= springConstant;

  force.normalize();
  force *= -magnitude;
  particle->addForce(force);
}

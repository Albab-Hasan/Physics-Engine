#include "Particle.h"
#include <cmath>

Particle::Particle()
    : position(0, 0, 0), velocity(0, 0, 0), acceleration(0, 0, 0),
      forceAccum(0, 0, 0), damping(0.995f), inverseMass(1.0f) {}

void Particle::integrate(float duration) {
  if (inverseMass <= 0.0f)
    return;

  position += velocity * duration;

  Vector3 resultingAcc = acceleration;
  resultingAcc += forceAccum * inverseMass;

  velocity += resultingAcc * duration;
  velocity *= std::pow(damping, duration);
}

void Particle::clearAccumulator() { forceAccum = Vector3(0, 0, 0); }

void Particle::addForce(const Vector3 &force) { forceAccum += force; }

void Particle::setMass(float mass) {
  if (mass != 0) {
    inverseMass = 1.0f / mass;
  } else {
    inverseMass = 0;
  }
}

float Particle::getMass() const {
  if (inverseMass == 0) {
    return INFINITY;
  }
  return 1.0f / inverseMass;
}

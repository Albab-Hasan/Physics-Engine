#pragma once
#include "Particle.h"

class ParticleContact {
public:
  Particle *particle[2];
  float restitution;
  Vector3 contactNormal;
  float penetration;

  void resolve(float duration);
  float calculateSeparatingVelocity() const;

private:
  void resolveVelocity(float duration);
  void resolveInterpenetration(float duration);
};

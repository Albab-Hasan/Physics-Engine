#pragma once
#include "Vector3.h"

class Particle {
public:
  Vector3 position;
  Vector3 velocity;
  Vector3 acceleration;
  Vector3 forceAccum;
  float damping;
  float inverseMass;

  Particle();

  void integrate(float duration);
  void setMass(float mass);
  float getMass() const;

  void clearAccumulator();
  void addForce(const Vector3 &force);
};

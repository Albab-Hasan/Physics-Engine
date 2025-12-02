#pragma once
#include "Vector3.h"

class Particle {
public:
  Vector3 position;
  Vector3 velocity;
  Vector3 acceleration;
  float damping;
  float inverseMass;

  Particle();

  void integrate(float duration);
  void setMass(float mass);
  float getMass() const;
};

#pragma once
#include "ForceGenerator.h"
#include "Vector3.h"

class GravityGenerator : public ForceGenerator {
private:
  Vector3 gravity;

public:
  GravityGenerator(const Vector3 &gravity);
  virtual void updateForce(Particle *particle, float duration) override;
};

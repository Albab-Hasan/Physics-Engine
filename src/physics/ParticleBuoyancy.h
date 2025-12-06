#pragma once
#include "ForceGenerator.h"
#include "Vector3.h"

class ParticleBuoyancy : public ForceGenerator {
  float maxDepth;
  float volume;
  float waterHeight;
  float liquidDensity;

public:
  ParticleBuoyancy(float maxDepth, float volume, float waterHeight,
                   float liquidDensity = 1000.0f);
  virtual void updateForce(Particle *particle, float duration);
};

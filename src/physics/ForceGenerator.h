#pragma once

class Particle;

class ForceGenerator {
public:
  virtual ~ForceGenerator() {}
  virtual void updateForce(Particle *particle, float duration) = 0;
};

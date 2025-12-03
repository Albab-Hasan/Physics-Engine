#pragma once
#include "ParticleContact.h"
#include <vector>

class ParticleContactResolver {
protected:
  unsigned iterations;
  unsigned iterationsUsed;

public:
  ParticleContactResolver(unsigned iterations);
  void setIterations(unsigned iterations);
  void resolveContacts(std::vector<ParticleContact> &contacts, float duration);
};

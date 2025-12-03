#include "ParticleContactResolver.h"

ParticleContactResolver::ParticleContactResolver(unsigned iterations)
    : iterations(iterations) {}

void ParticleContactResolver::setIterations(unsigned iterations) {
  this->iterations = iterations;
}

void ParticleContactResolver::resolveContacts(
    std::vector<ParticleContact> &contacts, float duration) {
  iterationsUsed = 0;
  while (iterationsUsed < iterations) {
    // Find the contact with the largest closing velocity
    float max = 0;
    unsigned maxIndex = contacts.size();
    for (unsigned i = 0; i < contacts.size(); i++) {
      float sepVel = contacts[i].calculateSeparatingVelocity();
      if (sepVel < max && (sepVel < 0 || contacts[i].penetration > 0)) {
        max = sepVel;
        maxIndex = i;
      }
    }

    // Do we have anything worth resolving?
    if (maxIndex == contacts.size())
      break;

    // Resolve this contact
    contacts[maxIndex].resolve(duration);

    iterationsUsed++;
  }
}

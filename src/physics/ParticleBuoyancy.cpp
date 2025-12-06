#include "ParticleBuoyancy.h"
#include "Particle.h"

ParticleBuoyancy::ParticleBuoyancy(float maxDepth, float volume,
                                   float waterHeight, float liquidDensity)
    : maxDepth(maxDepth), volume(volume), waterHeight(waterHeight),
      liquidDensity(liquidDensity) {}

void ParticleBuoyancy::updateForce(Particle *particle, float duration) {
  float depth = particle->position.y;

  // Check if we're out of the water
  if (depth >= waterHeight + maxDepth)
    return;

  Vector3 force(0, 0, 0);

  // Check if we're at maximum depth
  if (depth <= waterHeight - maxDepth) {
    force.y = liquidDensity * volume;
    particle->addForce(force);
    return;
  }

  // Otherwise we are partly submerged
  float submergedFactor = (depth - maxDepth - waterHeight) / (2 * maxDepth);
  force.y =
      liquidDensity * volume * submergedFactor *
      -1.0f; // -1 because depth increases downwards usually, but here y is up
  // Wait, let's re-verify the math.
  // If depth = waterHeight + maxDepth (just touching surface from above),
  // factor = 0. Force = 0. Correct. If depth = waterHeight - maxDepth (fully
  // submerged), factor = -2*maxDepth / 2*maxDepth = -1. Force = density *
  // volume. Correct.

  // Actually, let's simplify the factor calculation to be more intuitive.
  // depth is particle Y. waterHeight is water Y.
  // d = (waterHeight + maxDepth - particleY) / (2 * maxDepth)
  // if particleY = waterHeight + maxDepth, d = 0.
  // if particleY = waterHeight - maxDepth, d = 1.

  force.y = liquidDensity * volume *
            ((waterHeight + maxDepth - depth) / (2 * maxDepth));
  particle->addForce(force);
}

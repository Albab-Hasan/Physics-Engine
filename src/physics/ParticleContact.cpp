#include "ParticleContact.h"

void ParticleContact::resolve(float duration) {
  resolveVelocity(duration);
  resolveInterpenetration(duration);
}

float ParticleContact::calculateSeparatingVelocity() const {
  Vector3 relativeVelocity = particle[0]->velocity;
  if (particle[1]) {
    relativeVelocity -= particle[1]->velocity;
  }
  return relativeVelocity * contactNormal; // Dot product
}

void ParticleContact::resolveVelocity(float duration) {
  float separatingVelocity = calculateSeparatingVelocity();

  if (separatingVelocity > 0) {
    // The contact is either separating, or stationary - no impulse required.
    return;
  }

  float newSepVelocity = -separatingVelocity * restitution;
  float deltaVelocity = newSepVelocity - separatingVelocity;

  float totalInverseMass = particle[0]->inverseMass;
  if (particle[1]) {
    totalInverseMass += particle[1]->inverseMass;
  }

  if (totalInverseMass <= 0)
    return;

  float impulse = deltaVelocity / totalInverseMass;
  Vector3 impulsePerIMass = contactNormal * impulse;

  particle[0]->velocity += impulsePerIMass * particle[0]->inverseMass;
  if (particle[1]) {
    particle[1]->velocity += impulsePerIMass * -particle[1]->inverseMass;
  }
}

void ParticleContact::resolveInterpenetration(float duration) {
  if (penetration <= 0)
    return;

  float totalInverseMass = particle[0]->inverseMass;
  if (particle[1]) {
    totalInverseMass += particle[1]->inverseMass;
  }

  if (totalInverseMass <= 0)
    return;

  Vector3 movePerIMass = contactNormal * (penetration / totalInverseMass);

  particle[0]->position += movePerIMass * particle[0]->inverseMass;
  if (particle[1]) {
    particle[1]->position += movePerIMass * -particle[1]->inverseMass;
  }
}

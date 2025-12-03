#pragma once
#include "ForceGenerator.h"
#include "Particle.h"

class ParticleSpring : public ForceGenerator {
private:
    Particle* other;
    float springConstant;
    float restLength;

public:
    ParticleSpring(Particle* other, float springConstant, float restLength);
    virtual void updateForce(Particle* particle, float duration) override;
};

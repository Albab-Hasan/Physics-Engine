#pragma once
#include "ForceGenerator.h"

class ParticleDrag : public ForceGenerator {
    float k1;
    float k2;

public:
    ParticleDrag(float k1, float k2);
    virtual void updateForce(Particle* particle, float duration);
};

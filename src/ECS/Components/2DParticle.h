#include "../Systems/2DParticleSystem.h"

struct 2DparticleSystem : public ECS::BaseComponent {
    ParticleSystem::ParticleSystem system;
    for(;;){
        ParticleSystem::update();
    }

};
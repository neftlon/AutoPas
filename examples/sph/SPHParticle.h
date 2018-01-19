//
// Created by seckler on 19.01.18.
//

#ifndef AUTOPAS_SPHPARTICLE_H
#define AUTOPAS_SPHPARTICLE_H

#include "particles/Particle.h"

namespace autopas {

    class SPHParticle : public Particle {
    public:
        SPHParticle() : Particle() {}

        virtual ~SPHParticle() {}

        SPHParticle(std::array<double, 3> r, std::array<double, 3> v, unsigned long id) : Particle(r, v, id) {}


    private:
        

        double _density;
        double _pressure;
    };
}  // namespace autopas

#endif //AUTOPAS_SPHPARTICLE_H
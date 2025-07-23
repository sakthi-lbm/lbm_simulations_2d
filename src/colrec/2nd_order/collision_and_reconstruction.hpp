#ifndef COLLISION_AND_RECONSTRUCTION_HPP
#define COLLISION_AND_RECONSTRUCTION_HPP

#include <iostream>

#include "var.hpp"

inline void mom_collision(dfloat ux, dfloat uy, dfloat *mxx, dfloat *myy, dfloat *mxy)
{
    const dfloat omegaVar = OMEGA;
    const dfloat omega_m1 = 1.0 - omegaVar;

    *mxx = omega_m1 * (*mxx) + omegaVar * ux * ux;
    *myy = omega_m1 * (*myy) + omegaVar * uy * uy;
    *mxy = omega_m1 * (*mxy) + omegaVar * ux * uy;
}

inline void pop_reconstruction(dfloat rho, dfloat ux, dfloat uy, dfloat mxx, dfloat myy, dfloat mxy, dfloat *fout)
{
    for (size_t q = 0; q < Q; q++)
    {
        // *fout[q] = rho * w[q];
    }
    
}

#endif
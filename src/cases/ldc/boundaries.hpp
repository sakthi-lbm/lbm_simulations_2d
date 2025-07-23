#ifndef BOUNDARIES_HPP
#define BOUNDARIES_HPP

#include "../../var.hpp"

void boundary_definitions(unsigned int *nodeType, size_t x, size_t y)
{
    if (x == 0 && y == 0)
    {
        *nodeType = SOUTH_WEST;
    }
    else if (x == 0 && y == (NY - 1))
    {
        *nodeType = NORTH_WEST;
    }
    else if (x == (NX - 1) && y == 0)
    {
        *nodeType = SOUTH_EAST;
    }
    else if (x == (NX - 1) && y == (NY - 1))
    {
        *nodeType = NORTH_EAST;
    }
    else if (x == 0)
    {
        *nodeType = WEST;
    }
    else if (x == (NX - 1))
    {
        *nodeType = EAST;
    }
    else if (y == 0)
    {
        *nodeType = SOUTH;
    }
    else if (y == (NY - 1))
    {
        *nodeType = NORTH;
    }
    else
    {
        *nodeType = BULK;
    }
}

void boundary_condition(unsigned int nodeType, dfloat (&pop)[Q], dfloat *rhoVar, dfloat *ux, dfloat *uy, dfloat *mxx, dfloat *myy, dfloat *mxy)
{
    switch (nodeType)
    {
    case NORTH:
    {
        const dfloat rhoI = pop[0] + pop[1] + pop[2] + pop[3] + pop[5] + pop[6];
        const dfloat inv_rhoI = 1.0 / rhoI;
        const dfloat mxxI = (pop[1] + pop[3] + pop[5] + pop[6]) * inv_rhoI - cs2;
        const dfloat myyI = (pop[2] + pop[5] + pop[6]) * inv_rhoI - cs2;
        const dfloat mxyI = (pop[5] - pop[6]) * inv_rhoI - cs2;

        *ux = U0;
        *uy = 0.0;

        *rhoVar = 3.0 * rhoI * (4.0 + 3.0 * (1.0 - OMEGA) * myyI) / (9.0 + OMEGA);

        *mxx = 6.0 * rhoI * mxxI / (5.0 * (*rhoVar));
        *mxy = 2.0 * rhoI * mxyI / (*rhoVar);
        *myy = (*rhoVar + 9.0 * rhoI * myyI) / (6.0 * (*rhoVar));

        break;
    }
    default:
        break;
    }
}

#endif

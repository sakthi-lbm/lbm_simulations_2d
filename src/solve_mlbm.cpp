#include <iostream>
#include "solve_mlbm.hpp"

void calculate_moments(unsigned int *nodeType, dfloat *f_in, dfloat *h_fMom)
{

    for (size_t x = 0; x < NX; x++)
    {
        for (size_t y = 0; y < NY; y++)
        {
            dfloat rhoVar = 0;
            dfloat uxVar = 0;
            dfloat uyVar = 0;
            dfloat mxxVar = 0;
            dfloat myyVar = 0;
            dfloat mxyVar = 0;
            dfloat pop[Q];
            const unsigned int node = nodeType[IDX(x, y)];
            for (size_t q = 0; q < Q; q++)
            {
                pop[q] = f_in[FIDX(x, y, q)];
            }

            if (node != BULK)
            {
                boundary_condition(node, pop, &rhoVar, &uxVar, &uyVar, &mxxVar, &myyVar, &mxyVar);
                h_fMom[MIDX(x, y, M_RHO_INDEX)] = rhoVar - RHO_0;
                h_fMom[MIDX(x, y, M_UX_INDEX)] = uxVar;
                h_fMom[MIDX(x, y, M_UY_INDEX)] = uyVar;
                h_fMom[MIDX(x, y, M_MXX_INDEX)] = mxxVar;
                h_fMom[MIDX(x, y, M_MYY_INDEX)] = myyVar;
                h_fMom[MIDX(x, y, M_MXY_INDEX)] = mxyVar;

                // std::cout << x << " " << y << " " << rhoVar << " " << uxVar << " " << uyVar << std::endl;
            }

            else
            {
                const dfloat pop0 = f_in[FIDX(x, y, 0)];
                const dfloat pop1 = f_in[FIDX(x, y, 1)];
                const dfloat pop2 = f_in[FIDX(x, y, 2)];
                const dfloat pop3 = f_in[FIDX(x, y, 3)];
                const dfloat pop4 = f_in[FIDX(x, y, 4)];
                const dfloat pop5 = f_in[FIDX(x, y, 5)];
                const dfloat pop6 = f_in[FIDX(x, y, 6)];
                const dfloat pop7 = f_in[FIDX(x, y, 7)];
                const dfloat pop8 = f_in[FIDX(x, y, 8)];

                rhoVar = pop0 + pop1 + pop2 + pop3 + pop4 + pop5 + pop6 + pop7 + pop8;
                dfloat invRho = 1.0 / rhoVar;

                uxVar = (pop1 - pop3 + pop5 - pop6 - pop7 + pop8) * invRho;
                uyVar = (pop2 - pop4 + pop5 + pop6 - pop7 - pop8) * invRho;

                mxxVar = (pop1 + pop3 + pop5 + pop6 + pop7 + pop8) * invRho - cs2;
                myyVar = (pop2 + pop4 + pop5 + pop6 + pop7 + pop8) * invRho - cs2;
                mxyVar = (pop5 - pop6 + pop7 - pop8) * invRho;

                h_fMom[MIDX(x, y, M_RHO_INDEX)] = rhoVar - RHO_0;
                h_fMom[MIDX(x, y, M_UX_INDEX)] = uxVar;
                h_fMom[MIDX(x, y, M_UY_INDEX)] = uyVar;
                h_fMom[MIDX(x, y, M_MXX_INDEX)] = mxxVar;
                h_fMom[MIDX(x, y, M_MYY_INDEX)] = myyVar;
                h_fMom[MIDX(x, y, M_MXY_INDEX)] = mxyVar;

                // std::cout << x << " " << y << " " << rhoVar << " " << uxVar << " " << uyVar << std::endl;
            }
        }
    }
}

void MomCollisionStreaming(dfloat *h_fMom, dfloat *f_in, dfloat *f_out)
{
    for (size_t x = 0; x < NX; x++)
    {
        for (size_t y = 0; y < NY; y++)
        {

            dfloat rho_var = RHO_0 + h_fMom[MIDX(x, y, M_RHO_INDEX)];
            dfloat ux_var = h_fMom[MIDX(x, y, M_UX_INDEX)];
            dfloat uy_var = h_fMom[MIDX(x, y, M_UY_INDEX)];
            dfloat mxx = h_fMom[MIDX(x, y, M_MXX_INDEX)];
            dfloat myy = h_fMom[MIDX(x, y, M_MYY_INDEX)];
            dfloat mxy = h_fMom[MIDX(x, y, M_MXY_INDEX)];

            mom_collision(ux_var, uy_var, &mxx, &myy, &mxy);

            h_fMom[MIDX(x, y, M_MXX_INDEX)] = mxx;
            h_fMom[MIDX(x, y, M_MYY_INDEX)] = myy;
            h_fMom[MIDX(x, y, M_MXY_INDEX)] = mxy;

            dfloat pop[Q];
            pop_reconstruction(rho_var, ux_var, uy_var, mxx, myy, mxy, pop);
            for (size_t q = 0; q < Q; q++)
            {
                f_out[FIDX(x, y, q)] = pop[q];
            }
        }
    }

    // Streaming
    for (size_t x = 0; x < NX; x++)
    {
        for (size_t y = 0; y < NY; y++)
        {
            int xm1 = (x - 1 + NX) % NX;
            int xp1 = (x + 1) % NX;
            int ym1 = (y - 1 + NY) % NY;
            int yp1 = (y + 1) % NY;

            f_in[FIDX(x, y, 0)] = f_out[FIDX(x, y, 0)];
            f_in[FIDX(x, y, 1)] = f_out[FIDX(xm1, y, 1)];
            f_in[FIDX(x, y, 2)] = f_out[FIDX(x, ym1, 2)];
            f_in[FIDX(x, y, 3)] = f_out[FIDX(xp1, y, 3)];
            f_in[FIDX(x, y, 4)] = f_out[FIDX(x, yp1, 4)];
            f_in[FIDX(x, y, 5)] = f_out[FIDX(xm1, ym1, 5)];
            f_in[FIDX(x, y, 6)] = f_out[FIDX(xp1, ym1, 6)];
            f_in[FIDX(x, y, 7)] = f_out[FIDX(xp1, yp1, 7)];
            f_in[FIDX(x, y, 8)] = f_out[FIDX(xm1, yp1, 8)];
        }
    }
}
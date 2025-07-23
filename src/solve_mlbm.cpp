#include <iostream>
#include "solve_mlbm.hpp"

void MomCollisionStreaming(dfloat *h_fMom, dfloat *f_in, dfloat *f_out)
{
    for (size_t x = 0; x < NX; x++)
    {
        for (size_t y = 0; y < NY; y++)
        {

            dfloat rho_var = h_fMom[MIDX(x, y, M_RHO_INDEX)];
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
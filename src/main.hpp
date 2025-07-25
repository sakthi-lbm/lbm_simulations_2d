#ifndef MAIN_HPP
#define MAIN_HPP

#include "var.hpp"
#include "initialize_lbm.hpp"
#include "solve_mlbm.hpp"
#include "file_utils.hpp"
#include "save_data.hpp"

// Allocate host memory
inline void allocate_host_memory(
    dfloat **f_in,
    dfloat **f_out,
    dfloat **h_fMom,
    dfloat **rho,
    dfloat **ux,
    dfloat **uy,
    unsigned int **nodeType)
{
    *f_in = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_Q));
    *f_out = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_Q));
    *h_fMom = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_MOM));
    *rho = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES));
    *ux = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES));
    *uy = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES));
    *nodeType = static_cast<unsigned int *>(std::malloc(MEM_SIZE_NODETYPE));
}

// Free host memory
inline void free_host_memory(
    dfloat *f_in,
    dfloat *f_out,
    dfloat *h_fMom,
    dfloat *rho,
    dfloat *ux,
    dfloat *uy,
    unsigned int *nodeType)
{
    std::free(f_in);
    std::free(f_out);
    std::free(h_fMom);
    std::free(rho);
    std::free(ux);
    std::free(uy);
    std::free(nodeType);
}

inline void initialize_domain(unsigned int *nodeType, dfloat *h_fMom, dfloat *f_in)
{
    for (size_t x = 0; x < NX; x++)
    {
        for (size_t y = 0; y < NY; y++)
        {
            // boundary_definitions(nodeType, x, y);
            nodeType[IDX(x, y)] = boundary_definitions(x, y);

            dfloat rho_var, ux_var, uy_var;
            dfloat mxx, myy, mxy;
            initialize_moments(&rho_var, &ux_var, &uy_var, &mxx, &myy, &mxy);
            h_fMom[MIDX(x, y, M_RHO_INDEX)] = rho_var - RHO_0;
            h_fMom[MIDX(x, y, M_UX_INDEX)] = ux_var;
            h_fMom[MIDX(x, y, M_UY_INDEX)] = uy_var;
            h_fMom[MIDX(x, y, M_MXX_INDEX)] = mxx;
            h_fMom[MIDX(x, y, M_MYY_INDEX)] = myy;
            h_fMom[MIDX(x, y, M_MXY_INDEX)] = mxy;

            dfloat pop[Q];
            pop_reconstruction(rho_var, ux_var, uy_var, mxx, myy, mxy, pop);
            for (size_t q = 0; q < Q; q++)
            {
                f_in[FIDX(x, y, q)] = pop[q];
            }
        }
    }
}

#endif
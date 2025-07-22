#ifndef MAIN_HPP
#define MAIN_HPP

#include "var.hpp"
#include "definitions.hpp"
// #include<cstdlib>   // for std::malloc, std::free

dfloat *f_in;
dfloat *f_out;
dfloat *h_fMom;
dfloat *rho;
dfloat *ux;
dfloat *uy;
dfloat *mxx;
dfloat *mxy;
dfloat *myy;

// Allocate host memory
inline void allocate_host_memory(
    dfloat **f_in,
    dfloat **f_out,
    dfloat **h_fMom,
    dfloat **rho,
    dfloat **ux,
    dfloat **uy,
    dfloat **mxx,
    dfloat **mxy,
    dfloat **myy)
{
    *f_in = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_Q));
    *f_out = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_Q));
    *h_fMom = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES_MOM));
    *rho = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES));
    *ux = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES));
    *uy = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES));
    *mxx = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES));
    *mxy = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES));
    *myy = static_cast<dfloat *>(std::malloc(MEM_SIZE_NODES));
}

// Free host memory
inline void free_host_memory(
    dfloat *f_in,
    dfloat *f_out,
    dfloat *h_fMom,
    dfloat *rho,
    dfloat *ux,
    dfloat *uy,
    dfloat *mxx,
    dfloat *mxy,
    dfloat *myy)
{
    std::free(f_in);
    std::free(f_out);
    std::free(h_fMom);
    std::free(rho);
    std::free(ux);
    std::free(uy);
    std::free(mxx);
    std::free(mxy);
    std::free(myy);
}

#endif
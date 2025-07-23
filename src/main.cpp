#include <iostream>

#include "var.hpp"
#include "main.hpp"

int main()
{
    dfloat *f_in;
    dfloat *f_out;
    dfloat *h_fMom;
    dfloat *rho;
    dfloat *ux;
    dfloat *uy;

    allocate_host_memory(&f_in, &f_out, &h_fMom, &rho, &ux, &uy);

    // Domain Initialization: Moments and population
    initialize_domain(h_fMom, f_in);

    for (size_t iter = 0; iter < MAX_ITER; iter++)
    {
        MomCollisionStreaming(h_fMom, f_in, f_out);
        std::cout << iter << " " << f_in[FIDX(5, 5, 8)] << " " << f_out[FIDX(5, 5, 8)] << std::endl;
        // std::cout << iter << " " << FIDX(10, 10, 8) << " " << MEM_SIZE_NODES_Q << std::endl;
        // std::cout << "NX=" << NX << ", NY=" << NY << ", Q=" << Q << ", total size=" << NUM_NODES_Q << std::endl;
        // int idx = FIDX(10, 10, 8);
        // // std::assert(idx < NUM_NODES_Q);
        // std::cout << f_in[idx];
    }
    free_host_memory(f_in, f_out, h_fMom, rho, ux, uy);
    return 0;
}
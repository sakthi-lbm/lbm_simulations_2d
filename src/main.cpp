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
    unsigned int *nodeType;

    allocate_host_memory(&f_in, &f_out, &h_fMom, &rho, &ux, &uy, &nodeType);

    // Domain Initialization: Moments and population
    initialize_domain(nodeType, h_fMom, f_in);

    for (size_t iter = 0; iter < MAX_ITER; iter++)
    {
        calculate_moments(*nodeType, f_in, h_fMom);
        MomCollisionStreaming(h_fMom, f_in, f_out);
        std::cout << iter << " " << f_in[FIDX(5, 5, 8)] << " " << f_out[FIDX(5, 5, 8)] << std::endl;
      
    }
    free_host_memory(f_in, f_out, h_fMom, rho, ux, uy, nodeType);
    return 0;
}
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

    for (size_t iter = 0; iter < MAX_ITER; iter++)
    {
        // Domain Initialization
        initialize_domain(h_fMom);

        // std::cout << h_fMom[MIDX(10, 10, M_RHO_INDEX)] << std::endl;

        free_host_memory(f_in, f_out, h_fMom, rho, ux, uy);

        return 0;
    }
}
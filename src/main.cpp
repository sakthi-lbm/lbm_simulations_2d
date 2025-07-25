#include <iostream>

#include "main.hpp"

int main()
{
    create_output_directory();
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
    write_grid();

    for (size_t iter = 0; iter < MAX_ITER; iter++)
    {
        calculate_moments(nodeType, f_in, h_fMom);
        //  std::cout << iter << " " << h_fMom[MIDX(1,NX-1,M_UX_INDEX)] << std::endl;

        MomCollisionStreaming(h_fMom, f_in, f_out);
        // std::cout << iter << " " << f_in[FIDX(5, 5, 8)] << std::endl;

        if (iter % MACR_SAVE == 0)
        {
            write_solution(h_fMom, rho, ux, uy, iter);
        }
        }
    free_host_memory(f_in, f_out, h_fMom, rho, ux, uy, nodeType);
    return 0;
}
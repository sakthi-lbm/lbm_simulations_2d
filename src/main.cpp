#include <iostream>

#include "main.hpp"

int main()
{
    std::cout << "LBM simulation starter" << std::endl;

    std::cout << PI << " " << Nx << ::std::endl;

    for (size_t x = 0; x < Nx; x++)
    {
        for (size_t y = 0; y < Ny; y++)
        {
            std::cout << x << " " << y << " " << IDX(x, y) << std::endl;
            for (size_t q = 0; q < Q; q++)
            {
                std::cout << x << " " << y << " " << q << " " << FIDX(x, y, q) << " " << MIDX(x, y, q) << std::endl;
            }
        }
    }

    allocate_host_memory(&f_in, &f_out, &h_fMom, &rho, &ux, &uy, &mxx, &mxy, &myy);

    free_host_memory(f_in, f_out, h_fMom, rho, ux, uy, mxx, mxy, myy);

    return 0;
}
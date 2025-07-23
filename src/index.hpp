#ifndef INDEX_HPP
#define INDEX_HPP

#include "var.hpp"

#define IDX(x, y) (x + y * NX)
#define FIDX(x, y, q) ((q * NX * NY) + x + (y * NX))
#define MIDX(x,y,var) ((var * NX * NY) + x + (y * NX))

// inline size_t idx(size_t x, size_t y)
// {
//     return x + y * Nx;
// }

// inline size_t fidx(size_t x, size_t y, size_t q)
// {
//     return (q * Nx * Ny) + x + (y * Nx);
// }

#endif
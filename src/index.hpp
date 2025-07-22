#ifndef INDEX_HPP
#define INDEX_HPP

#include "var.hpp"

#define IDX(x, y) (x + y * Nx)
#define FIDX(x, y, q) ((q * Nx * Ny) + x + (y * Nx))
#define MIDX(x,y,var) ((var * Nx * Ny) + x + (y * Nx))

// inline size_t idx(size_t x, size_t y)
// {
//     return x + y * Nx;
// }

// inline size_t fidx(size_t x, size_t y, size_t q)
// {
//     return (q * Nx * Ny) + x + (y * Nx);
// }

#endif
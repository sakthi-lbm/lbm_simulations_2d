#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include "var.hpp"

// Lattice Velocity sets
constexpr unsigned char Q = 9;
constexpr dfloat W0 = 4.0 / 9.0;
constexpr dfloat W1 = 1.0 / 9.0;
constexpr dfloat W2 = 1.0 / 36.0;

constexpr dfloat w[Q] = {W0,
                         W1, W1, W1, W1,
                         W2, W2, W2, W2};

constexpr dfloat as2 = 3.0;
constexpr dfloat cs2 = 1.0 / as2;

constexpr dfloat cx[Q] = {0, 1, 0, -1, 0, 1, -1, -1, 1};
constexpr dfloat cy[Q] = {0, 0, 1, 0, -1, 1, 1, -1, -1};

#endif
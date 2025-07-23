#ifndef VAR_HPP
#define VAR_HPP
#include <cmath>

typedef float dfloat;

#define STR_IMPL(x) #x
#define STR(x) STR_IMPL(x)

#define BC_PROBLEM ldc
#define CASE_DIRECTORY cases
#define CASE_CONSTANTS STR(CASE_DIRECTORY/BC_PROBLEM/constants.hpp)
// #define CASE_BC STR(CASE_DIRECTORY/BC_PROBLEM/boundaries.hpp)
#define CASE_OUTPUTS STR(CASE_DIRECTORY/BC_PROBLEM/outputs.hpp)
#define COLREC "colrec/2nd_order/collision_and_reconstruction.hpp"

#include CASE_CONSTANTS
#include CASE_OUTPUTS


#include "index.hpp"
#include "definitions.hpp"
#include COLREC

#endif
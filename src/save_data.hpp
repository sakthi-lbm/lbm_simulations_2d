#ifndef SAVE_DATA_HPP
#define SAVE_DATA_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream> // std::cout, std::fixed
#include <iomanip>  // std::setprecision

#include "var.hpp"

void write_grid();

void write_solution(dfloat *h_fMom, dfloat *rho, dfloat *ux, dfloat *uy, size_t iter);






#endif
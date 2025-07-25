#ifndef SOLVE_MLBM_HPP
#define SOLVE_MLBM_HPP

#include<iostream>

#include "var.hpp"
#include COLREC
#include CASE_BOUNDARY

void MomCollisionStreaming(dfloat *h_fMom, dfloat *f_in, dfloat *f_out);
void calculate_moments(unsigned int *nodeType, dfloat *f_in, dfloat *h_fMom);

#endif
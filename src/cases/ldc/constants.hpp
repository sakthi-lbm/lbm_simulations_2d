#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include<iostream>
#include "../../var.hpp"

constexpr dfloat delx = 1.0;
constexpr dfloat dely = 1.0;
constexpr int N = 10;
constexpr int Nx = N;
constexpr int Ny = N;

constexpr dfloat Re = 1000;
constexpr dfloat rho0 = 1.0;
constexpr dfloat uo = 0.1;
constexpr dfloat nu = uo * (Nx - 1) / Re;
constexpr dfloat tau = 0.5 + 3.0 * nu;
constexpr dfloat omega = 1.0 / tau;

constexpr int MAX_ITER  = 100000;
constexpr int MACR_SAVE = 5000;
constexpr int RESTART_SAVE = 10000;










#endif
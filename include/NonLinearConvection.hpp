#ifndef NONLINEARCONVECTION_H
#define NONLINEARCONVECTION_H
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include "NavierStokes.hpp"

class NonLinearConvection: public NavierStokes{
public:

public:
    NonLinearConvection();
    NonLinearConvection(double x, int xp, double t, double dt, float c);
    NonLinearConvection(double x, int xp, double y, int yp, double t, double dt, float c);

    void run();
    void print_solution();

    ~NonLinearConvection();
};
#endif
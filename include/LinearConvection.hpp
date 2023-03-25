#ifndef LINEARCONVECTION_H
#define LINEARCONVECTION_H
#include <vector>
#include <numeric>
#include <iostream>
#include "NavierStokes.hpp"

class LinearConvection: public NavierStokes{
public:

public:
    LinearConvection();
    LinearConvection(double x, int xp, double t, double dt, float c);
    LinearConvection(double x, int xp, double y, int yp, double t, double dt, float c);
    
    void run();

    ~LinearConvection();
};
#endif
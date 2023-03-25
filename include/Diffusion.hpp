#ifndef DIFFUSION_H
#define DIFFUSION_H
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include "NavierStokes.hpp"

class Diffusion: public NavierStokes{
public:

public:
    Diffusion();
    Diffusion(double x, int xp, double t, double dt, float c);
    Diffusion(double x, int xp, double y, int yp, double t, double dt, float c);
    
    void run();

    ~Diffusion();
};
#endif
#ifndef BURGER_H
#define BURGER_H
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include "NavierStokes.hpp"

class Burger: public NavierStokes{
public:

public:
    Burger();
    Burger(double x, int xp, double t, double dt, float c);
    Burger(double x, int xp, double y, int yp, double t, double dt, float c);

    void run();
    void print_solution();

    ~Burger();
};
#endif
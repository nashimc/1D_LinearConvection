#pragma once
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include "LinSpace.hpp"

class Diffusion{
public:
    bool _oneD = false;
    bool _twoD = false;

    float _nu;
    double _xDimension;
    int _xPoints;
    double _deltaX = _xDimension / (_xPoints - 1);
    double _yDimension;
    int _yPoints;
    double _deltaY = _yDimension / (_yPoints - 1);

    double _timeSteps;
    double _deltaTime;

    std::vector<double> _xArray;
    std::vector<double> _yArray;
    std::vector<double> _uArray;
    std::vector<double> _uArray_new;
    std::vector<std::vector<double>> _uvArray;
    std::vector<std::vector<double>> _uvArray_new;

    std::vector<std::vector<double>> _iterSolution1D;
    std::vector<std::vector<std::vector<double>>> _iterSolution2D;

    LinSpace _linSpaced;

public:
    Diffusion(const double xDimension, const int xPoints, const double timeSteps, const double deltaTime, const float nu);
    Diffusion(const double xDimension, const int xPoints, const double yDimension, const int yPoints, const double timeSteps, const double deltaTime, const float nu);
    
    void init();
    void initConditions();
    void Run();
    void Solve();
    void printSolution();

    std::vector<double> getSolution1D();
    std::vector<std::vector<double>> getSolution2D();
    std::vector<std::vector<double>> getIterSolution1D();
    std::vector<std::vector<std::vector<double>>> getIterSolution2D();

    ~Diffusion();
};
#pragma once
#include <vector>
#include <numeric>
#include <iostream>
#include "ArrayType.hpp"
#include "LinSpace.hpp"

class NonLinearConvection{
public:
    bool _oneD = false;
    bool _twoD = false;

    float _velocity;
    double _xDimension, _yDimension;
    int _xPoints, _yPoints;
    double _deltaX = _xDimension / (_xPoints - 1);
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

    
    // ArrayType _solutionArray;

public:
    NonLinearConvection(const double xDimension, const int xPoints, const double timeSteps, const double deltaTime, float velocity);
    NonLinearConvection(const double xDimension, const int xPoints, const double yDimension, const int yPoints, const double timeSteps, const double deltaTime,  float velocity);
    
    void init();
    std::vector<double> linSpace(const double start, const double end, const double num);
    void initConditions();
    void hatFunction();
    void Run();
    void Solve();
    void printSolution();

    std::vector<double> getSolution1D();
    std::vector<std::vector<double>> getSolution2D();
    std::vector<std::vector<double>> getIterSolution1D();
    std::vector<std::vector<std::vector<double>>> getIterSolution2D();

    ~NonLinearConvection();
};
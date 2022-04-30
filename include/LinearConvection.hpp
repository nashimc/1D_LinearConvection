#pragma once
#include <vector>
#include <numeric>
#include <iostream>

class LinearConvection{
public:
    bool _oneD = false;
    bool _twoD = false;

    const int _constant = 1;
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

public:
    LinearConvection(const double xDimension, const int xPoints, const double timeSteps, const double deltaTime);
    LinearConvection(const double xDimension, const int xPoints, const double yDimension, const int yPoints, const double timeSteps, const double deltaTime);

    std::vector<double> linSpace(double start, double end, double num);
    void init();
    void solve();
    void printSolution();
    std::vector<double> getSolution();

    ~LinearConvection();
};
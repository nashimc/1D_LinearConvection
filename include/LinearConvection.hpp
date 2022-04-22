#pragma once
#include <vector>
#include <numeric>
#include <iostream>

class LinearConvection{
private:
    bool _oneD = false;
    bool _twoD = false;

    int _constant = 1;
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

    std::vector<double> _vArray;
    std::vector<double> _vArray_new;

public:
    LinearConvection(double xDimension, int xPoints, double timeSteps, double deltaTime);
    LinearConvection(double xDimension, int xPoints, int yPoints, double yDimension, double timeSteps, double deltaTime);

    std::vector<double> linSpace(double start, double end, double num);
    void initBoundary();
    void solve();
    void printSolution();

    std::vector<double> getSolution();

    ~LinearConvection();
};
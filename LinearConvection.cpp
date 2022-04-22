#include "include/LinearConvection.hpp"


LinearConvection::LinearConvection(double xDimension, int xPoints, double timeSteps, double deltaTime):
_xDimension{xDimension},
_xPoints{xPoints},
_timeSteps{timeSteps},
_deltaTime{deltaTime}
{
    _xArray = linSpace(0,_xDimension, _xPoints);

    _uArray.resize(_xPoints);
    std::fill(std::begin(_uArray), std::end(_uArray), 1);
    _uArray[0] = 0;
    _uArray[_xPoints-1] = 0;

    _oneD = true;
}

LinearConvection::LinearConvection(double xDimension, int xPoints, int yPoints, double yDimension, double timeSteps, double deltaTime):
_xDimension{xDimension},
_xPoints{xPoints},
_yDimension{yDimension},
_yPoints{yPoints},
_timeSteps{timeSteps},
_deltaTime{deltaTime}
{
    _xArray = linSpace(0, _xDimension, _xPoints);
    _yArray = linSpace(0, _yDimension, _yPoints);

    _vArray.resize(_yPoints);
    std::fill(std::begin(_vArray), std::end(_vArray), 1);
    _vArray[0] = 0;
    _vArray[_yPoints-1] = 0;

    _twoD = true;
}

LinearConvection::~LinearConvection(){

}

std::vector<double> LinearConvection::linSpace(double start, double end, double num){
    std::vector<double> linSpaceVec;

    double delta = (end - start) / (num - 1);
    
    if (num == 0){
        return linSpaceVec = {};
    }
    if (num == 1){
        linSpaceVec.push_back(start);
        return linSpaceVec;
    }
    for (int i = 0; i < num - 1; ++i){
        linSpaceVec.push_back(start + delta * i);        
    }
    linSpaceVec.push_back(end);      // add last element

    return linSpaceVec;
}

void LinearConvection::initBoundary(){
    if (_oneD == true){
        for (int i = 0; i < _xPoints; ++i){
            if (_xArray[i] >= 0.5 || _xArray[i] <= 1.0){
                _uArray[i] = 2;
            }
        }
    }
    else{}
}

void LinearConvection::solve(){
    initBoundary();
    if (_oneD == true){
        _uArray_new.resize(_xPoints);
        std::fill(std::begin(_uArray_new), std::end(_uArray_new), 1);
        for (int t = 0; t < _timeSteps; ++t){
            for (int i = 0; i < _xPoints; ++i)
            {
                _uArray_new[i] = _uArray[i] - _constant * (_deltaTime / _deltaX) * (_uArray[i] - _uArray[i-1]);
            }
            _uArray = _uArray_new;
        }
    }
    else{}
}


void LinearConvection::printSolution(){
    if (_oneD == true){
        for (int i = 0; i < _uArray_new.size(); ++i){
                std::cout << _uArray_new[i] << std::endl;
            }
    }
    else{}
}

std::vector<double> LinearConvection::getSolution(){
    return _uArray_new;
}
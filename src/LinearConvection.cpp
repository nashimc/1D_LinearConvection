#include "../include/LinearConvection.hpp"


LinearConvection::LinearConvection(const double xDimension, const int xPoints, const double timeSteps, const double deltaTime):
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

    _uArray_new.resize(_xPoints);

    _oneD = true;
}

LinearConvection::LinearConvection(const double xDimension, const int xPoints, const double yDimension, const int yPoints, const double timeSteps, const double deltaTime):
_xDimension{xDimension},
_xPoints{xPoints},
_yDimension{yDimension},
_yPoints{yPoints},
_timeSteps{timeSteps},
_deltaTime{deltaTime}
{
    _xArray = linSpace(0, _xDimension, _xPoints);
    _yArray = linSpace(0, _yDimension, _yPoints);

    _uArray.resize(_xPoints);
    std::fill(std::begin(_uArray), std::end(_uArray), 1);

    _uvArray.push_back(_uArray);                    // push initial u
    for (int i = 0; i < (_yPoints - 1); ++i){       // push u (yPoints-1) times
		_uvArray.push_back(_uArray);    
	}

    _uvArray_new = _uvArray;            

    _twoD = true;
}

LinearConvection::~LinearConvection(){

}

std::vector<double> LinearConvection::linSpace(const double start, const double end, const double num){
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
    linSpaceVec.push_back(end);                     // add last element

    return linSpaceVec;
}

void LinearConvection::init(){
    if (_oneD == true){
        for (int i = 0; i < _xArray.size(); ++i){    
            if (_xArray[i] >= 0.5 && _xArray[i] <= 1.0){
                _uArray[i] = 2;
            }
        }
    }
    if (_twoD == true){
        for (int i = 0; i < _uvArray.size(); ++i){    
            for (int j = 0; j < _uvArray[i].size(); ++j){
                if (_xArray[i] > 0.5 && _xArray[i] < 1){
                    if (_yArray[j] > 0.5 && _yArray[j] < 1){
                        _uvArray[i][j] = 2;
                    }
                }
            }    
        }
    }
} 




void LinearConvection::solve(){
    init();
    if (_oneD == true){        
        std::fill(std::begin(_uArray_new), std::end(_uArray_new), 1);
        for (int t = 0; t < _timeSteps; ++t){
            for (int i = 0; i < _xPoints; ++i)
            {
                _uArray_new[i] = _uArray[i] - _constant * (_deltaTime / _deltaX) * (_uArray[i] - _uArray[i-1]);
            }
            _uArray = _uArray_new;
        }
    }
    if (_twoD == true){
        for (int t = 0; t < _timeSteps; ++t){
            for (int i = 1; i < _uvArray.size(); ++i){    
                for (int j = 1; j < _uvArray[i].size(); ++j){
                    _uvArray_new[i][j] = _uvArray[i][j] - _constant * (_deltaTime / _deltaX) * (_uvArray[i][j] - _uvArray[i-1][j])
                                                        - _constant * (_deltaTime / _deltaY) * (_uvArray[i][j] - _uvArray[i][j-1]); 
                    _uvArray_new[0][j-1] = 2;                       // ---top--
                    _uvArray_new[i][0] = 2;                         // |  le
                    _uvArray_new[_uvArray.size()-1][j] = 2;         // --bot---
                    _uvArray_new[i-1][_uvArray[i].size()-1] = 2;    //    ri  |
                }
            }
            _uvArray = _uvArray_new;       
        }
    }
}


void LinearConvection::printSolution(){
    if (_oneD == true){
        for (int i = 0; i < _uArray_new.size(); ++i){
                std::cout << _uArray_new[i] << std::endl;
            }
    }
    if (_twoD == true){
        for (int i = 0; i < _uvArray.size(); ++i){
            for (auto it = _uvArray[i].begin(); it != _uvArray[i].end(); it++){	
                    std::cout << *it;
		    }
		    std::cout << "\n";
	    }
    }
}

std::vector<double> LinearConvection::getSolution(){
    return _uArray_new;
}
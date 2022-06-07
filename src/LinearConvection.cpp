#include "../include/LinearConvection.hpp"

LinearConvection::LinearConvection(const double xDimension, const int xPoints, const double timeSteps, const double deltaTime, float constant):
_xDimension{xDimension},
_xPoints{xPoints},
_timeSteps{timeSteps},
_deltaTime{deltaTime},
_constant{constant}
{
    _oneD = true;    
    init();
}

LinearConvection::LinearConvection(const double xDimension, const int xPoints, const double yDimension, const int yPoints, const double timeSteps, const double deltaTime, float constant):
_xDimension{xDimension},
_xPoints{xPoints},
_yDimension{yDimension},
_yPoints{yPoints},
_timeSteps{timeSteps},
_deltaTime{deltaTime},
_constant{constant}
{
    _twoD = true;
    init();      
}

LinearConvection::~LinearConvection(){

}

// initialise arrays
void LinearConvection::init(){  
    LinSpace linSpaced;                                     
    if (_oneD == true){        
        _xArray = linSpaced.getLinSpace(0,_xDimension, _xPoints);

        _uArray.resize(_xPoints);                                   // resize arrays
        _uArray_new.resize(_xPoints);                                 
        std::fill(std::begin(_uArray), std::end(_uArray), 1);       // fill arrays to 1
        _uArray_new = _uArray;                                      // copy to new
        _uArray[0] = 0;                                             
        _uArray[_xPoints-1] = 0;        
    }
    if (_twoD == true){
        _xArray = linSpaced.getLinSpace(0, _xDimension, _xPoints);
        _yArray = linSpaced.getLinSpace(0, _yDimension, _yPoints);

        _uArray.resize(_xPoints);                                   // resize arrays
        std::fill(std::begin(_uArray), std::end(_uArray), 1);       // fill u with 1
        for (int i = 0; i < (_yPoints); ++i){                       // push u yPoints times to produce 2D array
            _uvArray.push_back(_uArray);                            
        }
        _uvArray_new = _uvArray;                                    // copy to new
    }
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
    linSpaceVec.push_back(end);                                     // add last element
    return linSpaceVec;
}

void LinearConvection::initConditions(){
    if (_oneD == true){
        for (int i = 0; i < _xArray.size(); ++i){    
            if (_xArray[i] >= 0.5 && _xArray[i] <= 1.0){
                _uArray[i] = 2;
            }
        }
    }
    if (_twoD == true){
        for (int i = 0; i < _uvArray.size(); ++i){                  // for uv matrix, check linspace arrays and adjust index
            for (int j = 0; j < _uvArray[i].size(); ++j){
                if (_xArray[i] > 0.5 && _xArray[i] < 1){
                    if (_yArray[j] > 0.5 && _yArray[j] < 1){
                        _uvArray[i][j] = 2;                         // initial velocity
                    }
                }
            }    
        }
    }
}

void LinearConvection::Run(){
    if (_oneD == true){        
        for (int t = 0; t < _timeSteps; ++t){
            for (int i = 0; i < _xPoints; ++i)
            {
                _uArray_new[i] = _uArray[i] - _constant 
                                            * (_deltaTime / _deltaX) * (_uArray[i] - _uArray[i-1]);
            }
            _iterSolution1D.push_back(_uArray_new);                 // save iterative solution for all timesteps
            _uArray = _uArray_new;
        }
    }
    if (_twoD == true){
        for (int t = 0; t < _timeSteps; ++t){
            for (int i = 1; i < _uvArray.size(); ++i){   
                for (int j = 1; j < _uvArray[i].size(); ++j){
                    _uvArray_new[i][j] = _uvArray[i][j] - _constant 
                                                        * (_deltaTime / _deltaX) * (_uvArray[i][j] - _uvArray[i-1][j])
                                                        - _constant 
                                                        * (_deltaTime / _deltaY) * (_uvArray[i][j] - _uvArray[i][j-1]); 
                    // Boundary Conditions - fills in BC with shift
                    _uvArray_new[0][j-1] = 1;                       // ---top--
                    _uvArray_new[i][0] = 1;                         // |  le
                    _uvArray_new[_uvArray.size()-1][j] = 1;         // --bot---
                    _uvArray_new[i-1][_uvArray[i].size()-1] = 1;    //    ri  |
                }
            }
            _iterSolution2D.push_back(_uvArray_new);                // save iterative solution for all timesteps
            _uvArray = _uvArray_new;       
        }

        // // alternative way to loop through matrix, loops through inner points, then applies BC - 4 sides + 4 corners
        // for (int t = 0; t < _timeSteps; ++t){
        //     for (int i = 1; i < _uvArray.size() - 1; ++i){
        //         for (int j = 1; j < _uvArray[i].size() - 1; ++j){
        //             _uvArray_new[i][j] = _uvArray[i][j] - _constant * (_deltaTime / _deltaX) * (_uvArray[i][j] - _uvArray[i-1][j])
        //                                                 - _constant * (_deltaTime / _deltaY) * (_uvArray[i][j] - _uvArray[i][j-1]);
        //             // Boundary Conditions
        //             _uvArray_new[0][j] = 1;                                     // ---top--
        //             _uvArray_new[i][0] = 1;                                     // |  le
        //             _uvArray_new[_uvArray.size()-1][j] = 1;                     // --bot---
        //             _uvArray_new[i][_uvArray[i].size()-1] = 1;                  //    ri  |
        //             _uvArray_new[0][0] = 1;                                     // top le corner
        //             _uvArray_new[_uvArray.size()-1][0] = 1;                     // bot le corner
        //             _uvArray_new[_uvArray.size()-1][_uvArray[i].size()-1] = 1;  // bot ri corner
        //             _uvArray_new[0][_uvArray[i].size()-1] = 1;                  // top ri corner
        //         }
        //     }
        //     _iterSolution2D.push_back(_uvArray_new);                // save iterative solution for all timesteps
        //     _uvArray = _uvArray_new;       
        // }
    }

}

void LinearConvection::Solve(){
    initConditions();
    Run();
}

void LinearConvection::printSolution(){
    if (_oneD == true){
        for (int i = 0; i < _uArray.size(); ++i){
                std::cout << _uArray[i] << std::endl;
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


std::vector<double> LinearConvection::getSolution1D(){return _uArray;}

std::vector<std::vector<double>> LinearConvection::getSolution2D(){return _uvArray;}

std::vector<std::vector<double>> LinearConvection::getIterSolution1D(){return _iterSolution1D;}
    
std::vector<std::vector<std::vector<double>>> LinearConvection::getIterSolution2D(){return _iterSolution2D;}



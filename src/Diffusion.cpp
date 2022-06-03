#include "../include/Diffusion.hpp"


Diffusion::Diffusion(const double xDimension, const int xPoints, const double timeSteps, const double deltaTime, const float nu):
_xDimension{xDimension},
_xPoints{xPoints},
_timeSteps{timeSteps},
_deltaTime{deltaTime},
_nu{nu}
{
    _oneD = true;
    init();
}

Diffusion::Diffusion(const double xDimension, const int xPoints, const double yDimension, const int yPoints, const double timeSteps, const double deltaTime, const float nu):
_xDimension{xDimension},
_xPoints{xPoints},
_yDimension{yDimension},
_yPoints{yPoints},
_timeSteps{timeSteps},
_deltaTime{deltaTime},
_nu{nu}
{
    _twoD = true;
    init();      
}

Diffusion::~Diffusion(){

}

// initialise arrays
void Diffusion::init(){                                      
    if (_oneD == true){
        _xArray = linSpace(0,_xDimension, _xPoints);

        _uArray.resize(_xPoints);                                   // resize arrays
        _uArray_new.resize(_xPoints);                                 
        std::fill(std::begin(_uArray), std::end(_uArray), 1);       // fill arrays to 1
        _uArray_new = _uArray;                                      // copy to new
        _uArray[0] = 0;                                             
        _uArray[_xPoints-1] = 0;        
    }
    if (_twoD == true){
        _xArray = linSpace(0, _xDimension, _xPoints);
        _yArray = linSpace(0, _yDimension, _yPoints);

        _uArray.resize(_xPoints);                                   // resize arrays
        std::fill(std::begin(_uArray), std::end(_uArray), 1);       // fill u with 1
        for (int i = 0; i < (_yPoints); ++i){                       // push u yPoints times to produce 2D array
            _uvArray.push_back(_uArray);                            
        }
        _uvArray_new = _uvArray;                                    // copy to new
    }
}

std::vector<double> Diffusion::linSpace(const double start, const double end, const double num){
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

void Diffusion::initConditions(){
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

void Diffusion::Run(){
    if (_oneD == true){        
        for (int t = 0; t < _timeSteps; ++t){
            for (int i = 1; i < _xPoints - 1; ++i)
            {
                _uArray_new[i] = _uArray[i] - _nu * (_deltaTime / pow(_deltaX, 2)) * (_uArray[i+1] - 2*_uArray[i] + _uArray[i-1]);
            }
            _iterSolution1D.push_back(_uArray_new);                 // save iterative solution for all timesteps
            _uArray = _uArray_new;
        }
    }
    if (_twoD == true){
        for (int t = 0; t < _timeSteps; ++t){
            for (int i = 1; i < _uvArray.size() - 1; ++i){    
                for (int j = 1; j < _uvArray[i].size() - 1; ++j){
                    _uvArray_new[i][j] = _uvArray[i][j] - _nu * (_deltaTime / pow(_deltaX, 2)) * (_uvArray[i+1][j] - 2*_uvArray[i][j] + _uvArray[i-1][j])
                                                        - _nu * (_deltaTime / pow(_deltaY, 2)) * (_uvArray[i][j+1] - 2*_uvArray[i][j] + _uvArray[i][j-1]); 
                    // // Boundary Conditions
                    // _uvArray_new[0][j-1] = 3;                       // ---top--
                    // _uvArray_new[i][0] = 4;                         // |  le
                    // _uvArray_new[_uvArray.size()-1][j] = 5;         // --bot---
                    // _uvArray_new[i-1][_uvArray[i].size()-1] = 6;    //    ri  |
                }
            }
            _iterSolution2D.push_back(_uvArray_new);                // save iterative solution for all timesteps
            _uvArray = _uvArray_new;       
        }
    }

}

void Diffusion::Solve(){
    initConditions();
    Run();
}

void Diffusion::printSolution(){
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

std::vector<double> Diffusion::getSolution1D(){return _uArray;}

std::vector<std::vector<double>> Diffusion::getSolution2D(){return _uvArray;}

std::vector<std::vector<double>> Diffusion::getIterSolution1D(){return _iterSolution1D;}
    
std::vector<std::vector<std::vector<double>>> Diffusion::getIterSolution2D(){return _iterSolution2D;}


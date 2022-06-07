#pragma once
#include <vector>

// HEADER ONLY
struct LinSpace{
    std::vector<double> _linSpaceVec;

    LinSpace(){};
    std::vector<double> getLinSpace(const double start, const double end, const double num){
        double delta = (end - start) / (num - 1);
        if (num == 0){
        return _linSpaceVec = {};
        }
        if (num == 1){
            _linSpaceVec.push_back(start);
            return _linSpaceVec;
        }
        for (int i = 0; i < num - 1; ++i){
            _linSpaceVec.push_back(start + delta * i);        
        }
        _linSpaceVec.push_back(end);                                     // add last element
        return _linSpaceVec;
    }
    ~LinSpace(){};       
};
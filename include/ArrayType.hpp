#pragma once
#include <vector>

struct ArrayType{
    std::vector<double> oneD;
    std::vector<std::vector<double>> twoD;
    std::vector<std::vector<std::vector<double>>> threeD;
};
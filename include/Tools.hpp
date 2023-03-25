#ifndef TOOLS_H
#define TOOLS_H
#include <iostream>
#include <vector>
#include <string>

struct LinSpace{
    std::vector<double> lin_space_vec;

    LinSpace(){};
    
    std::vector<double> get_lin_space(const double start, const double end, const double num){
        double delta = (end - start) / (num - 1);
        if (num == 0){
        return lin_space_vec = {};
        }
        if (num == 1){
            lin_space_vec.push_back(start);
            return lin_space_vec;
        }
        for (int i = 0; i < num - 1; ++i){
            lin_space_vec.push_back(start + delta * i);        
        }
        lin_space_vec.push_back(end);                                     
        return lin_space_vec;
    }

    ~LinSpace(){};
};

// struct writeToFile{
//     std::ofstream file;  
//     writeToFile(std::string const fileName, std::vector<std::vector<std::vector<double>>> &matrix){ 
//         file.open(fileName);
//         for (auto t = 0; t < matrix.size(); ++t){
//             file << t << ",";
//             for (auto y = 0; y < matrix[t].size(); ++y){
//                 for (auto x = 0; x < matrix[t][y].size(); ++x){
//                     file << matrix[t][y][x] << ",";
//                 }	
//                 file << "\n" << ",";
//             }
//             file << "\n";
// 	    }
//     }    
// };
#endif
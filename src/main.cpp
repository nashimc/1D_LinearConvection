#include <iostream>
#include <vector>
#include <string>
#include "../include/pbPlots.hpp"               // EXTERNAL
#include "../include/supportLib.hpp"            // EXTERNAL
#include "../include/LinearConvection.hpp"
#include "../include/Diffusion.hpp"
#include "../include/NonLinearConvection.hpp"


void writeToFile(std::string const fileName, std::vector<std::vector<std::vector<double>>> &matrix){
    std::ofstream file;   
    file.open(fileName);
    for (auto t = 0; t < matrix.size(); ++t){
        file << t << ",";
		for (auto y = 0; y < matrix[t].size(); ++y){
			for (auto x = 0; x < matrix[t][y].size(); ++x){
				file << matrix[t][y][x] << ",";
			}	
			file << "\n" << ",";
        }
		file << "\n";
	}
}


int main(){

    double x_dimension = 5;
    double x_points = 21;
    double y_dimension = 5;
    double y_points = 21;
    int time_steps = 50;   
    double delta_time = 0.1;
    float lc_constant = 1;
    float diff_nu = 0.3;
    float nlc_velocity = 2;

    LinearConvection lin_conv(x_dimension, x_points, y_dimension, y_points, time_steps, delta_time, lc_constant);
    std::cout << "LinConv Result: \n";  
    lin_conv.run();
    lin_conv.print_solution();
    std::vector<std::vector<std::vector<double>>> lc_timestep_solutions = lin_conv.get_timestep_solutions_2D();
    writeToFile("LinConvResults.csv", lc_timestep_solutions);
    std::cout << "\n";

    Diffusion diff(x_dimension, x_points, y_dimension, y_points, time_steps, delta_time, diff_nu);
    std::cout << "Diff Result: \n";  
    diff.run();
    diff.print_solution();
    std::vector<std::vector<std::vector<double>>> diff_timestep_solutions = diff.get_timestep_solutions_2D();
    writeToFile("DiffResults.csv", diff_timestep_solutions);
    std::cout << "\n";

    NonLinearConvection non_lin_conv(x_dimension, x_points, y_dimension, y_points, time_steps, delta_time, nlc_velocity);
    std::cout << "NonLinConv Result: \n";  
    non_lin_conv.run();
    non_lin_conv.print_solution();
    std::vector<std::vector<std::vector<double>>> nlc_timestep_solutions = non_lin_conv.get_timestep_solutions_2D();
    writeToFile("NonLinConvResults.csv", nlc_timestep_solutions);
    std::cout << "\n";
    

}

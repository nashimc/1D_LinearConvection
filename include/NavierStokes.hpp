#ifndef NAVIERSTOKES_H
#define NAVIERSTOKES_H
#include <vector>
#include <numeric>
#include <iostream>
#include "Tools.hpp"

class NavierStokes{
public:
    bool one_dim = false;
    bool two_dim = false;

    float constant;
    double x_dimension, y_dimension;
    int x_points, y_points;
    double delta_x;
    double delta_y;

    double time_steps;
    double delta_time;

    std::vector<double> x_array;
    std::vector<double> y_array;
    std::vector<double> u_array;
    std::vector<double> u_array_new;
    std::vector<std::vector<double>> uv_array;
    std::vector<std::vector<double>> uv_array_new;
    std::vector<std::vector<double>> vv_array;
    std::vector<std::vector<double>> vv_array_new;

    std::vector<std::vector<double>> timestep_solutions_1D;
    std::vector<std::vector<std::vector<double>>> uv_timestep_solutions_2D;
    std::vector<std::vector<std::vector<double>>> vv_timestep_solutions_2D;

public:
    NavierStokes();
       
    void init_arrays();
    void init_conditions();    
    void boundary_conditions();
    virtual void print_solution();
    std::vector<std::vector<double>> get_timestep_solutions_1D() const {return timestep_solutions_1D;}    
    std::vector<std::vector<std::vector<double>>> get_uv_timestep_solutions_2D() const {return uv_timestep_solutions_2D;}
    std::vector<std::vector<std::vector<double>>> get_vv_timestep_solutions_2D() const {return vv_timestep_solutions_2D;}
    std::vector<double> get_final_solution_1D() const {return u_array;}
    std::vector<std::vector<double>> get_uu_final_solution_2D() const {return uv_array;}
    std::vector<std::vector<double>> get_vv_final_solution_2D() const {return vv_array;}

    ~NavierStokes();
};
#endif
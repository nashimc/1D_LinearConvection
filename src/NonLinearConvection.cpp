#include "../include/NonLinearConvection.hpp"
#include "NonLinearConvection.hpp"

NonLinearConvection::NonLinearConvection(){}

NonLinearConvection::NonLinearConvection(double x, int xp, double t, double dt, float c){
    x_dimension = x;
    x_points = xp;
    time_steps = t;
    delta_time = dt;
    constant = c;
    one_dim = true;
}

NonLinearConvection::NonLinearConvection(double x, int xp, double y, int yp, double t, double dt, float c){
    x_dimension = x;
    x_points = xp;
    y_dimension = y;
    y_points = yp;
    time_steps = t;
    delta_time = dt;
    constant = c;
    two_dim = true;       
}

NonLinearConvection::~NonLinearConvection(){}

/*
Forward differencing in Time and Backward differencing in Space.
For 1D, the convection depends on the cell to the left of the current cell.
For 2D, the convection depends on the cell above and to the left of the current cell
*/

void NonLinearConvection::hat_function(){

}

// TODO
void NonLinearConvection::run()
{
    /*
    uv_array_new[ix, iy] = uv_array[ix, iy] 
                            - c * (del_t / float(del_x)) * (u[ix, iy] - u[ix - 1, iy]) 
                            - c * (del_t / float(del_y)) * (u[ix, iy] - u[ix, iy - 1])

    uv_array_new[ix, iy] = uv_array[ix, iy] 
                            - uv_array[ix, iy] * (del_t / float(del_x)) * (uv_array[ix, iy] - uv_array[ix - 1, iy]) 
                            - vv_array[ix, iy] * (del_t / float(del_y)) * (uv_array[ix, iy] - uv_array[ix, iy - 1])

    vv_array_new[ix, iy] = vv_array[ix, iy] 
                            - uv_array[ix, iy] * (del_t / float(del_x)) * (vv_array[ix, iy] - vv_array[ix - 1, iy]) 
                            - vv_array[ix, iy] * (del_t / float(del_y)) * (vv_array[ix, iy] - vv_array[ix, iy - 1])
    */
    init_arrays();
    init_conditions();
    if (one_dim == true){        
        for (int t = 0; t < time_steps; ++t){
            for (int i = 0; i < x_points; ++i){
                u_array_new[i] = u_array[i] - constant 
                                            * (delta_time / delta_x) * (u_array[i] - u_array[i-1]);
            }
            timestep_solutions_1D.push_back(u_array_new);                 
            u_array = u_array_new;
        }
    }
    if (two_dim == true){
        vv_array = uv_array; 
        vv_array_new = uv_array_new;  
        for (int t = 0; t < time_steps +1; ++t){
            for (int i = 1; i < uv_array.size(); ++i){   
                for (int j = 1; j < uv_array[i].size(); ++j){
                    uv_array_new[i][j] = uv_array[i][j] - constant 
                                                        * (delta_time / delta_x) * (uv_array[i][j] - uv_array[i-1][j])
                                                        - constant 
                                                        * (delta_time / delta_y) * (uv_array[i][j] - uv_array[i][j-1]);
                                                       
                    uv_array_new[0][j-1] = 1;                       // --top--|
                    uv_array_new[i][0] = 1;                         // |  le
                    uv_array_new[uv_array.size()-1][j] = 1;         // |--bot---
                    uv_array_new[i-1][uv_array[i].size()-1] = 1;    //    ri   |
                }
            }
            timestep_solutions_2D.push_back(uv_array_new);               
            uv_array = uv_array_new;       
        }
    }
}
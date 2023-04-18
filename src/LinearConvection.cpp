#include "../include/LinearConvection.hpp"

LinearConvection::LinearConvection(){}

LinearConvection::LinearConvection(double x, int xp, double t, double dt, float c){
    x_dimension = x;
    x_points = xp;
    time_steps = t;
    delta_time = dt;
    constant = c;
    one_dim = true;
}

LinearConvection::LinearConvection(double x, int xp, double y, int yp, double t, double dt, float c){
    x_dimension = x;
    x_points = xp;
    y_dimension = y;
    y_points = yp;
    time_steps = t;
    delta_time = dt;
    constant = c;
    two_dim = true;      
}

LinearConvection::~LinearConvection(){}

/*
Forward differencing in Time and Backward differencing in Space.
For 1D, the convection depends on the cell to the left of the current cell.
For 2D, the convection depends on the cell above and to the left of the current cell
*/
void LinearConvection::run(){    
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
            uv_timestep_solutions_2D.push_back(uv_array_new);               
            uv_array = uv_array_new;       
        }

        /*
        // alternative way to loop through matrix, loops through inner points, then applies BC - 4 sides + 4 corners
        for (int t = 0; t < time_steps; ++t){
            for (int i = 1; i < uv_array.size() - 1; ++i){
                for (int j = 1; j < uv_array[i].size() - 1; ++j){
                    uv_array_new[i][j] = uv_array[i][j] - constant * (delta_time / delta_x) * (uv_array[i][j] - uv_array[i-1][j])
                                                        - constant * (delta_time / delta_y) * (uv_array[i][j] - uv_array[i][j-1]);
                    // Boundary Conditions
                    uv_array_new[0][j] = 1;                                     // ---top--
                    uv_array_new[i][0] = 1;                                     // |  le
                    uv_array_new[uv_array.size()-1][j] = 1;                     // --bot---
                    uv_array_new[i][uv_array[i].size()-1] = 1;                  //    ri  |
                    uv_array_new[0][0] = 1;                                     // top le corner
                    uv_array_new[uv_array.size()-1][0] = 1;                     // bot le corner
                    uv_array_new[uv_array.size()-1][uv_array[i].size()-1] = 1;  // bot ri corner
                    uv_array_new[0][uv_array[i].size()-1] = 1;                  // top ri corner
                }
            }
            current_solution_2D.push_back(uv_array_new);                // save iterative solution for all timesteps
            uv_array = uv_array_new;       
        }
        */
    }
}
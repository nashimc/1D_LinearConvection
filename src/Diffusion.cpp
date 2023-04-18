#include "../include/Diffusion.hpp"

Diffusion::Diffusion(){}

Diffusion::Diffusion(double x, int xp, double t, double dt, float c){
    x_dimension = x;
    x_points = xp;
    time_steps = t;
    delta_time = dt;
    constant = c;
    one_dim = true;
}

Diffusion::Diffusion(double x, int xp, double y, int yp, double t, double dt, float c){
    x_dimension = x;
    x_points = xp;
    y_dimension = y;
    y_points = yp;
    time_steps = t;
    delta_time = dt;
    constant = c;
    two_dim = true;       
}

Diffusion::~Diffusion(){}

/*
Forward differencing in Time and Backward differencing in Space.
For 1D, the convection depends on the cell to the left of the current cell.
For 2D, the convection depends on the cell above and to the left of the current cell
*/
void Diffusion::run(){
    init_arrays();
    init_conditions();
    if (one_dim == true){        
        for (int t = 0; t < time_steps; ++t){
            for (int i = 1; i < x_points - 1; ++i)
            {
                u_array_new[i] = u_array[i] - constant * (delta_time / pow(delta_x, 2)) * (u_array[i+1] - 2*u_array[i] + u_array[i-1]);
            }
            timestep_solutions_1D.push_back(u_array_new);                 // save iterative solution for all timesteps
            u_array = u_array_new;
        }
    }
    if (two_dim == true){
        for (int t = 0; t < time_steps + 1; ++t){
            for (int i = 1; i < uv_array.size() - 1; ++i){    
                for (int j = 1; j < uv_array[i].size() - 1; ++j){
                    uv_array_new[i][j] = uv_array[i][j] - constant * (delta_time / pow(delta_x, 2)) * (uv_array[i+1][j] - 2*uv_array[i][j] + uv_array[i-1][j])
                                                        - constant * (delta_time / pow(delta_y, 2)) * (uv_array[i][j+1] - 2*uv_array[i][j] + uv_array[i][j-1]); 
                    // Boundary Conditions
                    uv_array_new[0][j] = 1;                       // ---top--
                    uv_array_new[i][0] = 1;                         // |  le
                    uv_array_new[uv_array.size()-1][j] = 1;         // --bot---
                    uv_array_new[i-1][uv_array[i].size()-1] = 1;    //    ri  |
                }
            }
            uv_timestep_solutions_2D.push_back(uv_array_new);                // save iterative solution for all timesteps
            uv_array = uv_array_new;       
        }
    }

}
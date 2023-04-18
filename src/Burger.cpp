#include "../include/Burger.hpp"

Burger::Burger(){}

Burger::Burger(double x, int xp, double t, double dt, float c){
    x_dimension = x;
    x_points = xp;
    time_steps = t;
    delta_time = dt;
    constant = c;
    one_dim = true;
}

Burger::Burger(double x, int xp, double y, int yp, double t, double dt, float c){
    x_dimension = x;
    x_points = xp;
    y_dimension = y;
    y_points = yp;
    time_steps = t;
    delta_time = dt;
    constant = c;
    two_dim = true;       
}

Burger::~Burger(){}

/*
Forward differencing in Time and Backward differencing in Space.
For 1D, the convection depends on the cell to the left of the current cell.
For 2D, the convection depends on the cell above and to the left of the current cell
*/
void Burger::run()
{
    init_arrays();
    init_conditions();
    if (one_dim == true){}
    if (two_dim == true){
        vv_array = uv_array; 
        // for (int t = 0; t < time_steps +1; ++t){
        //     for (int i = 1; i < uv_array.size(); ++i){   
        //         for (int j = 1; j < uv_array[i].size(); ++j){
        for (int i = 0; i < uv_array.size(); ++i){
            for (int j = 0; j < uv_array[i].size(); ++j){
                if (x_array[i] > 0.5 && x_array[i] < 1.0){
                    if (y_array[j] > 0.5 && y_array[j] < 1.0){
                        uv_array[i][j] = 2.0;
                        vv_array[i][j] = 2.0;
                    }
                }
            }
        }
        uv_array_new = uv_array; 
        vv_array_new = vv_array;
        for (int t = 0; t < time_steps; t++) {
            for (int i = 1; i < x_points; i++) {
                for (int j = 1; j < y_points; j++) {
                    uv_array_new[i][j] = uv_array[i][j] - uv_array[i][j] * (delta_time / delta_x) * (uv_array[i][j] - uv_array[i - 1][j]) -
                                    vv_array[i][j] * (delta_time / delta_y) * (uv_array[i][j] - uv_array[i][j - 1]);
                    uv_array_new[0][j] = 1.0;
                    uv_array_new[i][y_points - 1] = 1.0;
                    uv_array_new[x_points - 1][j] = 1.0;
                    uv_array_new[i][0] = 1.0;

                    vv_array_new[i][j] = vv_array[i][j] - uv_array[i][j] * (delta_time / delta_x) * (vv_array[i][j] - vv_array[i - 1][j]) -
                                    vv_array[i][j] * (delta_time / delta_y) * (vv_array[i][j] - vv_array[i][j - 1]);
                    vv_array_new[0][j] = 1.0;
                    vv_array_new[i][y_points - 1] = 1.0;
                    vv_array_new[x_points - 1][j] = 1.0;
                    vv_array_new[i][0] = 1.0;
                    }
                }
            uv_timestep_solutions_2D.push_back(uv_array_new);  
            vv_timestep_solutions_2D.push_back(vv_array_new);
            uv_array = uv_array_new;    
            vv_array = vv_array_new;      
        }
    }
}

void Burger::print_solution(){
    if (one_dim == true){
        for (int i = 0; i < u_array.size(); ++i){
                std::cout << u_array[i] << std::endl;
            }
    }
    if (two_dim == true){
        for (int i = 0; i < uv_array.size(); ++i){
            for (auto it = uv_array[i].begin(); it != uv_array[i].end(); it++){	
                std::cout << *it;
		    }
		    std::cout << "\n";
	    }
        std::cout << "\n" << std::endl;
        for (int i = 0; i < vv_array.size(); ++i){
            for (auto it = vv_array[i].begin(); it != vv_array[i].end(); it++){	
                std::cout << *it;
		    }
		    std::cout << "\n";
	    }
    }
}
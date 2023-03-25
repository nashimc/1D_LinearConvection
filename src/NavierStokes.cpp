#include "../include/NavierStokes.hpp"

NavierStokes::NavierStokes(){}

NavierStokes::~NavierStokes(){}

/* 
Initialise arrays
*/
void NavierStokes::init_arrays(){
    delta_x = x_dimension / (x_points - 1);
    delta_y = y_dimension / (y_points - 1);  
    LinSpace lin_space;                                     
    if (one_dim == true){        
        x_array = lin_space.get_lin_space(0, x_dimension, x_points);

        u_array.resize(x_points);                                   
        u_array_new.resize(x_points);                                 
        std::fill(std::begin(u_array), std::end(u_array), 1);       
        u_array_new = u_array;                                      
        u_array[0] = 0;                                             
        u_array[x_points-1] = 0;        
    }
    if (two_dim == true){
        x_array = lin_space.get_lin_space(0, x_dimension, x_points);
        y_array = lin_space.get_lin_space(0, y_dimension, y_points);

        u_array.resize(x_points);                                  
        std::fill(std::begin(u_array), std::end(u_array), 1);       
        for (int i = 0; i < (y_points); ++i){                       
            uv_array.push_back(u_array);                            
        }
        uv_array_new = uv_array;                                           
    }
}

/* 
Initial velocity conditions
*/
void NavierStokes::init_conditions(){
    if (one_dim == true){
        for (int i = 0; i < x_array.size(); ++i){    
            if (x_array[i] >= 0.5 && x_array[i] <= 1.0){
                u_array[i] = 2;                                     
            }
        }
    }
    if (two_dim == true){
        for (int i = 0; i < uv_array.size(); ++i){                  
            for (int j = 0; j < uv_array[i].size(); ++j){
                if (x_array[i] > 0.5 && x_array[i] < 1){
                    if (y_array[j] > 0.5 && y_array[j] < 1){
                        uv_array[i][j] = 2;                         
                    }
                }
            }    
        }
    }
}

/* 
Wall boundary conditions - not used. To be implemented another time in different class
*/
void NavierStokes::boundary_conditions(){
    if (one_dim == true){}
    if (two_dim == true){
        for (int i = 0; i < uv_array.size(); ++i){   
            for (int j = 0; j < uv_array[i].size(); ++j){
                uv_array_new[0][j] = 1;                       // ---top---
                uv_array_new[i][0] = 1;                       // |  le
                uv_array_new[uv_array.size()][j] = 1;         // ---bot---
                uv_array_new[i][uv_array[i].size()] = 1;      //    ri   |
            }
        }   
    }
}

void NavierStokes::print_solution(){
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
    }
}
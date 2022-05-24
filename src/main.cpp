#include <iostream>
#include "../include/pbPlots.hpp"
#include "../include/supportLib.hpp"
#include "../include/LinearConvection.hpp"


int main(){

    // double xDimension = 2;
    // double numberOfPoints = 21;
    // int timeSteps = 50;   
    // double deltaTime = 0.01;

    // LinearConvection oneD(xDimension, numberOfPoints, timeSteps, deltaTime);
    // oneD.solve();


    // // plot to graph
    // std::vector<double> x;
    // double n = 0;
    // for (int i = 0; i < numberOfPoints; ++i){
    //     x.push_back(n);     
    //     ++n;
    // }
    // std::vector<double> y = oneD.getSolution();


    double xDimension = 4;
    double numberOfXPoints = 42;
    double yDimension = 2;
    double numberOfYPoints = 21;
    int timeSteps = 10;   
    double deltaTime = 0.005;

    LinearConvection twoD(xDimension, numberOfXPoints, yDimension, numberOfYPoints, timeSteps, deltaTime);

    // for (auto it = twoD._xArray.begin(); it != twoD._xArray.end(); it++){
    //     std::cout << *it << " ";
    // }
	// std::cout << "\n";

    // for (int i = 0; i < twoD._uvArray.size(); ++i){
	// 	for (auto it = twoD._uvArray[i].begin(); it != twoD._uvArray[i].end(); it++){	
	// 			std::cout << *it;
	// 	}
	// 	std::cout << "\n";
	// }

    // // get 2d solution
    // std::cout << "\n";
    // std::cout << "init: \n";
    // twoD.init();    
    // for (int i = 0; i < twoD._uvArray.size(); ++i){
	// 	for (auto it = twoD._uvArray[i].begin(); it != twoD._uvArray[i].end(); it++){	
	// 			std::cout << *it;
	// 	}
	// 	std::cout << "\n";
	// }
    

    std::cout << "\n";
    std::cout << "iterSolve: \n";
    twoD.iterSolve();
    std::vector<std::vector<std::vector<double>>> iterSolveSolution2D = twoD.getIterSolution2D();

    for (auto t = 0; t < iterSolveSolution2D.size(); ++t){
		for (auto y = 0; y < iterSolveSolution2D[t].size(); ++y){
			for (auto x = 0; x < iterSolveSolution2D[t][y].size(); ++x){
				std::cout << iterSolveSolution2D[t][y][x]<< "\t";
			}	
			std::cout << "\n";
		}
		std::cout << "\n";
	}


    












    // if (x.size() == y.size()){
    //     RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    //     StringReference *errorMessage = new StringReference();
    //     DrawScatterPlot(imageRef, 600, 400, &x, &y, errorMessage);
    //     std::vector<double> *pngData = ConvertToPNG(imageRef->image);
    //     WriteToFile(pngData, "plot.png");
    //     DeleteImage(imageRef->image);
    //     delete errorMessage;
    // }

    // return 0;
}


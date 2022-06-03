#include <iostream>
#include "../include/pbPlots.hpp"
#include "../include/supportLib.hpp"
#include "../include/LinearConvection.hpp"
#include "../include/Diffusion.hpp"


int main(){

    // double xDimension = 2;
    // double numberOfPoints = 21;
    // int timeSteps = 50;   
    // double deltaTime = 0.01;

    // LinearConvection oneD(xDimension, numberOfPoints, timeSteps, deltaTime);
    // oneD.solve();




    double xDimension = 5;
    double numberOfXPoints = 21;
    double yDimension = 5;
    double numberOfYPoints = 21;
    int timeSteps = 2;   
    double deltaTime = 0.005;
    double nu = 0.3;

    LinearConvection twoD_LC(xDimension, numberOfXPoints, yDimension, numberOfYPoints, timeSteps, deltaTime);
    // Diffusion twoD(xDimension, numberOfXPoints, yDimension, numberOfYPoints, timeSteps, deltaTime, nu);

    std::cout << "\n";
    std::cout << "\n";
    std::cout << "LC solve: \n";
    twoD_LC.Solve();
    for (int i = 0; i < twoD_LC._uvArray.size(); ++i){
		for (auto it = twoD_LC._uvArray[i].begin(); it != twoD_LC._uvArray[i].end(); it++){	
				std::cout << *it;
		}
		std::cout << "\n";
	}

    std::vector<std::vector<std::vector<double>>> iterSolution2D_LC = twoD_LC.getIterSolution2D();
    std::ofstream file_LC;
    file_LC.open("LinConvResults.csv");
    for (auto t = 0; t < iterSolution2D_LC.size(); ++t){
        file_LC << t << ",";
		for (auto y = 0; y < iterSolution2D_LC[t].size(); ++y){
			for (auto x = 0; x < iterSolution2D_LC[t][y].size(); ++x){
				file_LC << iterSolution2D_LC[t][y][x] << ",";
			}	
			file_LC << "\n" << ",";
		}
		file_LC << "\n";
	}

    // std::cout << "\n";
    // std::cout << "\n";
    // std::cout << "LC solve: \n";
    // twoD.Solve();
    // for (int i = 0; i < twoD._uvArray.size(); ++i){
	// 	for (auto it = twoD._uvArray[i].begin(); it != twoD._uvArray[i].end(); it++){	
	// 			std::cout << *it;
	// 	}
	// 	std::cout << "\n";
	// }

    // std::vector<std::vector<std::vector<double>>> iterSolution2D = twoD.getIterSolution2D();
    // std::ofstream file;
    // file.open("LinConvResults.csv");
    // // file.open("DiffResults.csv");
    // for (auto t = 0; t < iterSolution2D.size(); ++t){
    //     file << t << ",";
	// 	for (auto y = 0; y < iterSolution2D[t].size(); ++y){
	// 		for (auto x = 0; x < iterSolution2D[t][y].size(); ++x){
	// 			file << iterSolution2D[t][y][x] << ",";
	// 		}	
	// 		file << "\n" << ",";
	// 	}
	// 	file << "\n";
	// }





    // // 1D Check
    // for (auto it = oneD._xArray.begin(); it != oneD._xArray.end(); it++){
    //     std::cout << *it << " ";
    // }
	// std::cout << "\n";
    // // 2D Check
    // for (int i = 0; i < twoD._uvArray.size(); ++i){
	// 	for (auto it = twoD._uvArray[i].begin(); it != twoD._uvArray[i].end(); it++){	
	// 			std::cout << *it;
	// 	}
	// 	std::cout << "\n";
	// }

    // // get 2d iter print
    // for (auto t = 0; t < iterSolution2D.size(); ++t){
    //     std::cout << t << ",\t\t";
	// 	for (auto y = 0; y < iterSolution2D[t].size(); ++y){
	// 		for (auto x = 0; x < iterSolution2D[t][y].size(); ++x){
	// 			std::cout << iterSolution2D[t][y][x] << ",\t\t";
	// 		}	
	// 		std::cout << "\n";
	// 	}
	// 	std::cout << "\n";
	// }

    // // plot to graph
    // std::vector<double> x;
    // double n = 0;
    // for (int i = 0; i < numberOfPoints; ++i){
    //     x.push_back(n);     
    //     ++n;
    // }
    // std::vector<double> y = oneD.getSolution();


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


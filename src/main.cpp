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


    double xDimension = 5;
    double numberOfXPoints = 101;
    double yDimension = 5;
    double numberOfYPoints = 101;
    int timeSteps = 100;   
    double deltaTime = 0.005;

    LinearConvection twoD(xDimension, numberOfXPoints, yDimension, numberOfYPoints, timeSteps, deltaTime);

    std::cout << "\n";
    std::cout << "\n";
    std::cout << "solve: \n";
    twoD.Solve();
    for (int i = 0; i < twoD._uvArray.size(); ++i){
		for (auto it = twoD._uvArray[i].begin(); it != twoD._uvArray[i].end(); it++){	
				std::cout << *it;
		}
		std::cout << "\n";
	}

    std::vector<std::vector<std::vector<double>>> iterSolution2D = twoD.getIterSolution2D();
    std::ofstream file;
    file.open("results.csv");
    for (auto t = 0; t < iterSolution2D.size(); ++t){
        file << t << ",";
		for (auto y = 0; y < iterSolution2D[t].size(); ++y){
			for (auto x = 0; x < iterSolution2D[t][y].size(); ++x){
				file << iterSolution2D[t][y][x] << ",";
			}	
			file << "\n" << ",";
		}
		file << "\n";
	}







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


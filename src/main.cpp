#include <iostream>
#include <vector>
#include <string>
#include "../include/pbPlots.hpp"
#include "../include/supportLib.hpp"
#include "../include/ArrayType.hpp"
#include "../include/LinearConvection.hpp"
#include "../include/Diffusion.hpp"


void writeMatrix(std::string const fileName, std::vector<std::vector<std::vector<double>>> &matrix){
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

    double xDimension = 5;
    double numberOfXPoints = 21;
    double yDimension = 5;
    double numberOfYPoints = 21;
    int timeSteps = 10;   
    double deltaTime = 0.005;
    float lc_constant = 1;
    float diff_nu = 0.3;

    LinearConvection twoD_LC(xDimension, numberOfXPoints, yDimension, numberOfYPoints, timeSteps, deltaTime, lc_constant);
    Diffusion twoD_Diff(xDimension, numberOfXPoints, yDimension, numberOfYPoints, timeSteps, deltaTime, diff_nu);

    std::cout << "LinConv Result: \n";
    twoD_LC.Solve();
    twoD_LC.printSolution();

    std::cout << "Diff Result: \n";
    twoD_Diff.Solve();
    twoD_Diff.printSolution();

    std::vector<std::vector<std::vector<double>>> iterSolution2D_LC = twoD_LC.getIterSolution2D();
    writeMatrix("LinConvResults.csv", iterSolution2D_LC);

    std::vector<std::vector<std::vector<double>>> iterSolution2D_Diff = twoD_Diff.getIterSolution2D();
    writeMatrix("DiffResults.csv", iterSolution2D_Diff); 








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



#include<iostream>
#include "include/pbPlots.hpp"
#include "include/supportLib.hpp"
#include "include/LinearConvection.hpp"


int main(){

    double xDimension = 2;
    double numberOfPoints = 21;
    int timeSteps = 50;   
    double deltaTime = 0.01;

    LinearConvection oneD(xDimension, numberOfPoints, timeSteps, deltaTime);
    oneD.solve();


    // plot to graph
    std::vector<double> x;
    double n = 0;
    for (int i = 0; i < numberOfPoints; ++i){
        x.push_back(n);     
        ++n;
    }
    std::vector<double> y = oneD.getSolution();

    if (x.size() == y.size()){
        RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
        StringReference *errorMessage = new StringReference();
        DrawScatterPlot(imageRef, 600, 400, &x, &y, errorMessage);
        std::vector<double> *pngData = ConvertToPNG(imageRef->image);
        WriteToFile(pngData, "plot.png");
        DeleteImage(imageRef->image);
        delete errorMessage;
    }

     

    return 0;
}


#include "ExoAnalysis/WR_lite/interface/neuralNet.h"

#include <list>
#include <string>
#include <math.h> 
#include <iostream>
#include <fstream>
#include <sstream>

//Initialize the neural net with the folder where the weights are stored
neuralNet::neuralNet(std::string fileName) {
	extractMatrix(fileName+"/normInfo.txt", &normInfo[0][0], 2);
	
	extractMatrix(fileName+"/weights_0.txt", &weight0[0][0], 8);//, 15, 50);
	extractMatrix(fileName+"/biases_0.txt", &bias0[0][0], 1);
	extractMatrix(fileName+"/weights_1.txt", &weight1[0][0], 20);
	extractMatrix(fileName+"/biases_1.txt", &bias1[0][0], 1);
	extractMatrix(fileName+"/weights_2.txt", &weight2[0][0], 20);
	extractMatrix(fileName+"/biases_2.txt", &bias2[0][0], 1);
	
	weights[0] = &weight0[0][0];
	weights[1] = &weight1[0][0];
	weights[2] = &weight2[0][0];
	
	biases[0] = &bias0[0][0];
	biases[1] = &bias1[0][0];
	biases[2] = &bias2[0][0];

}

//Make predictions with the neural net
void neuralNet::predict(double * inputVal, double * outputVal, int dim){

    double innerVal1[20][dim];
	double innerVal2[20][dim];
	double inputCopy[dim][8];
	
	//Copy input to a new array and normalize the contents
	copyMatrix(inputVal, &inputCopy[0][0], dim, 8);
	normalize(&inputCopy[0][0], 8, dim);
	
	//Start working through the network layers
	matrixMult(weights[0], &inputCopy[0][0], &innerVal1[0][0], 20, dim, 8);
	matrixAdd(&innerVal1[0][0], biases[0], 20, dim);
	
	leakyReLU(&innerVal1[0][0], 20, dim);
	copyMatrix(&innerVal1[0][0], &innerVal2[0][0], 20, dim);

	for(int x=1; x<2; x++){
		matrixMult(weights[x], &innerVal2[0][0], &innerVal1[0][0], 20, dim, 20);
		matrixAdd(&innerVal1[0][0], biases[x], 20, dim);
		leakyReLU(&innerVal1[0][0], 20, dim);
		copyMatrix(&innerVal1[0][0], &innerVal2[0][0], 20, dim);
	}

	matrixMult(weights[2], &innerVal2[0][0], &innerVal1[0][0], 1, dim, 20);
	matrixAdd(&innerVal1[0][0], biases[2], 1, dim);
	sigmoid(&innerVal1[0][0], 1, dim);
	
	//Copy output to a new array
	copyMatrix(&innerVal1[0][0], outputVal, 1, dim);
	//Round predictions to 0.0 or 1.0
	roundPredictions(outputVal, 1, dim);
	
}

//Read a file into an array
void neuralNet::extractMatrix(std::string fileName, double * matrix, int dim1){
	
	std::fstream file (fileName ,std::ios_base::in);
	std::string line;

	int y = 0;
	while(getline(file,line)) {
		std::stringstream   linestream(line);
		std::string         value;
		int x = 0;
		while(getline(linestream,value,',')) {
			*(matrix + x + (y * dim1)) = atof(value.c_str());
			x++;
		}
		y++;
	}
}

//Multiply two arrays
void neuralNet::matrixMult(double * a, double * b, double * c, int dim1, int dim2, int dim3){
	for(int x=0; x<dim1; x++){
		for(int y=0; y<dim2; y++){
			*(c + y + (x * dim2)) = 0.0;
			for(int z=0; z<dim3; z++){
				*(c + y + (x * dim2)) += *(a + z + (x * dim3)) * *(b + y + (z * dim2));
				
			}
		}
	}
}	
   
//Add two arrays   
void neuralNet::matrixAdd(double * a, double * b, int dim1, int dim2){
    for(int x=0; x<dim1; x++){
        for(int y=0; y<dim2; y++){

			
			(*(a + y + (x * dim2))) = *(a + y + (x * dim2)) + *(b + x);

		}
	}
}

//Apply the leakyReLU activation function with a slope of 0.1	
void neuralNet::leakyReLU(double * a, int dim1, int dim2){
    for(int x=0; x<dim1; x++){
        for(int y=0; y<dim2; y++){
            if(*(a + y + (x * dim2))<0){    
                *(a + y + (x * dim2)) = *(a + y + (x * dim2)) * 0.2;
            } else {
                *(a + y + (x * dim2))= *(a + y + (x * dim2));
			}
		}
	}
}

//Apply the sigmoid activation function
void neuralNet::sigmoid(double * a, int dim1, int dim2){
	std::cout << "Sigmoid" << std::endl;
	for(int x=0; x<dim1; x++){
        for(int y=0; y<dim2; y++){
			std::cout << *(a + y + (x * dim2)) << "->";
			*(a + y + (x * dim2)) = exp(*(a + y + (x * dim2)))/(exp(*(a + y + (x * dim2)))+1);
			std::cout <<  *(a + y + (x * dim2)) << std::endl;
		}
	}
}
    
//Round predictions to 0 or 1	
void neuralNet::roundPredictions(double * a, int dim1, int dim2){
    std::cout << "Round" << std::endl;
	for(int x=0; x<dim1; x++){
        for(int y=0; y<dim2; y++){
			std::cout << *(a + y + (x * dim2)) << "->";
            if(*(a + y + (x * dim2))<0.5){
                *(a + y + (x * dim2)) = 0.0;
			} else {
                *(a + y + (x * dim2)) = 1.0;
			}
			std::cout <<  *(a + y + (x * dim2)) << std::endl;
		}
	}
}

//Copy the contents of an array into another
void neuralNet::copyMatrix(double * a, double * b, int dim1, int dim2){
	for(int x=0;x<dim1;x++){
		for(int y =0; y<dim2;y++){
			 *(b + y + (x * dim2)) = *(a + y + (x * dim2));
		}
	}
}

//Normalize the input array
void neuralNet::normalize(double * a, int dim1, int dim2){
	std::cout << "Normalize" << std::endl;
	for(int x=0; x<dim1; x++){
        for(int y=0; y<dim2; y++){
			std::cout << *(a + y + (x * dim2)) << "->";
            *(a + y + (x * dim2)) = (*(a + y + (x * dim2)) - normInfo[x][0])/normInfo[x][1];
			std::cout <<  *(a + y + (x * dim2)) << std::endl;
		}
	}
}    
#include "ExoAnalysis/WR-lite/interface/neuralNet.h"

#include <list>
#include <string>
#include <math.h> 
#include <iostream>
#include <fstream>
#include <sstream>


neuralNet::neuralNet(std::string fileName) {

	//normInfo[15][2] = {};
	extractMatrix(fileName+"/normInfo.txt", &normInfo[0][0], 2);
	
	
	//weight0[50][15] = {};

	extractMatrix(fileName+"/weights_0.txt", &weight0[0][0], 15);//, 15, 50);
	
	
	
	//bias0[50][1] = {};

	extractMatrix(fileName+"/biases_0.txt", &bias0[0][0], 1);//, 1, 50);
	//weight1[50][50] = {};

	extractMatrix(fileName+"/weights_1.txt", &weight1[0][0], 50);//, 50, 50);
	//bias1[50][1] = {};

	extractMatrix(fileName+"/biases_1.txt", &bias1[0][0], 1);//, 1, 50);
	//weight2[50][50] = {};

	extractMatrix(fileName+"/weights_2.txt", &weight2[0][0], 50);//, 50, 50);
	//bias2[50][1] = {};

	extractMatrix(fileName+"/biases_2.txt", &bias2[0][0], 1);//, 1, 50);
	//weight3[50][50] = {};

	extractMatrix(fileName+"/weights_3.txt", &weight3[0][0], 50);//, 50, 50);
	//bias3[50][1] = {};

	extractMatrix(fileName+"/biases_3.txt", &bias3[0][0], 1);//, 1, 50);
	//weight4[50][50] = {};

	extractMatrix(fileName+"/weights_4.txt", &weight4[0][0], 50);//, 50, 50);
	//bias4[50][1] = {};

	extractMatrix(fileName+"/biases_4.txt", &bias4[0][0], 1);//, 1, 50);
	//weight5[1][50] = {};

	extractMatrix(fileName+"/weights_5.txt", &weight5[0][0], 50);//, 50, 1);
	//bias5[1][1] = {};

	extractMatrix(fileName+"/biases_5.txt", &bias5[0][0], 1);//, 1, 1);

	
	
	weights[0] = &weight0[0][0];
	weights[1] = &weight1[0][0];
	weights[2] = &weight2[0][0];
	weights[3] = &weight3[0][0];
	weights[4] = &weight4[0][0];
	weights[5] = &weight5[0][0];
	
	biases[0] = &bias0[0][0];
	biases[1] = &bias1[0][0];
	biases[2] = &bias2[0][0];
	biases[3] = &bias3[0][0];
	biases[4] = &bias4[0][0];
	biases[5] = &bias5[0][0];



}

void neuralNet::predict(double * inputVal, double * outputVal, int dim){


	double innerVal1[50][dim];// = {0.0};

	double innerVal2[50][dim];// = {0.0};
	
	double inputCopy[dim][15];
	
	copyMatrix(inputVal, &inputCopy[0][0], dim, 15);
	normalize(&inputCopy[0][0], dim, 15);
	
	
	
	matrixMult(weights[0], &inputCopy[0][0], &innerVal1[0][0], 50, dim, 15);
	matrixAdd(&innerVal1[0][0], biases[0], 50, dim);
	leakyReLU(&innerVal1[0][0], 50, dim);
	copyMatrix(&innerVal1[0][0], &innerVal2[0][0], 50, dim);


	

	for(int x=1; x<5; x++){

		matrixMult(weights[x], &innerVal2[0][0], &innerVal1[0][0], 50, dim, 50);
		matrixAdd(&innerVal1[0][0], biases[x], 50, dim);
		leakyReLU(&innerVal1[0][0], 50, dim);
		copyMatrix(&innerVal1[0][0], &innerVal2[0][0], 50, dim);
	}

	matrixMult(weights[5], &innerVal2[0][0], &innerVal1[0][0], 1, dim, 50);
	
	matrixAdd(&innerVal1[0][0], biases[5], 1, dim);
	sigmoid(&innerVal1[0][0], 1, dim);
	copyMatrix(&innerVal1[0][0], outputVal, 1, dim);
	roundPredictions(outputVal, 1, dim);
	
}

void neuralNet::extractMatrix(std::string fileName, double * matrix, int dim1){

	
	std::fstream file (fileName ,std::ios_base::in);
	std::string line;

	
	int y = 0;
	while(getline(file,line))
	{

	
		std::stringstream   linestream(line);
		std::string         value;
		int x = 0;
		while(getline(linestream,value,','))
		{

			*(matrix + x + (y * dim1)) = atof(value.c_str());
	
			x++;
		}
		y++;
	}
}


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
    
void neuralNet::matrixAdd(double * a, double * b, int dim1, int dim2){
    for(int x=0; x<dim1; x++){
        for(int y=0; y<dim2; y++){

			
			(*(a + y + (x * dim2))) = *(a + y + (x * dim2)) + *(b + x);

		}
	}
}	
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

void neuralNet::sigmoid(double * a, int dim1, int dim2){
    for(int x=0; x<dim1; x++){
        for(int y=0; y<dim2; y++){
            *(a + y + (x * dim2)) = exp(*(a + y + (x * dim2)))/(exp(*(a + y + (x * dim2)))+1);
		}
	}
}
    
void neuralNet::roundPredictions(double * a, int dim1, int dim2){
    for(int x=0; x<dim1; x++){
        for(int y=0; y<dim2; y++){
            if(*(a + y + (x * dim2))<0.5){
                *(a + y + (x * dim2)) = 0.0;
			} else {
                *(a + y + (x * dim2)) = 1.0;
			}
		}
	}
}

void neuralNet::copyMatrix(double * a, double * b, int dim1, int dim2){
	for(int x=0;x<dim1;x++){
		for(int y =0; y<dim2;y++){
			 *(b + y + (x * dim2)) = *(a + y + (x * dim2));
		}
	}
}

void neuralNet::normalize(double * a, int dim1, int dim2){
	for(int x=0; x<dim1; x++){
        for(int y=0; y<dim2; y++){
            *(a + y + (x * dim2)) = (*(a + y + (x * dim2)) - normInfo[x][0])/normInfo[x][1];
		}
	}
}
       

       

#include <list>
#include <string>
#include <math.h> 
#include <iostream>
#include <fstream>


class neuralNet {
	public:
		neuralNet(std::string fileName);
		void predict(double * inputVal, double * outputVal, int dim);
		
	private:
	
		double * weights[6]; //store addresses of weight arrays
		double * biases[6]; //store addresses of bias arrays
		
		double normInfo[15][2];
		
		double weight0[50][15];
		double bias0[50][1];
		double weight1[50][50];
		double bias1[50][1];
		double weight2[50][50];
		double bias2[50][1];
		double weight3[50][50];
		double bias3[50][1];
		double weight4[50][50];
		double bias4[50][1];
		double weight5[1][50];
		double bias5[1][1];
	
	
		void extractMatrix(std::string fileName, double * matrix, int dim1);
		void matrixMult(double * a, double * b, double * c, int dim1, int dim2, int dim3);
		void matrixAdd(double * a, double * b, int dim1, int dim2);
		void leakyReLU(double * a, int dim1, int dim2);
		void sigmoid(double * a, int dim1, int dim2);
		void roundPredictions(double * a, int dim1, int dim2);
		void copyMatrix(double * a, double * b, int dim1, int dim2);
		void normalize(double * a, int dim1, int dim2);
};


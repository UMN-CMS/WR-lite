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
		double * weights[3]; //store addresses of weight arrays
		double * biases[3]; //store addresses of bias arrays
		
		double normInfo[8][2];
		
		double weight0[20][8];
		double bias0[20][1];
		double weight1[20][20];
		double bias1[20][1];
		double weight2[1][20];
		double bias2[1][1];
	
		void extractMatrix(std::string fileName, double * matrix, int dim1);
		void matrixMult(double * a, double * b, double * c, int dim1, int dim2, int dim3);
		void matrixAdd(double * a, double * b, int dim1, int dim2);
		void leakyReLU(double * a, int dim1, int dim2);
		void sigmoid(double * a, int dim1, int dim2);
		void roundPredictions(double * a, int dim1, int dim2);
		void copyMatrix(double * a, double * b, int dim1, int dim2);
		void normalize(double * a, int dim1, int dim2);
};


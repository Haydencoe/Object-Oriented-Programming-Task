

//Hayden Coe 309219
//Object-Orinated Programming, CMP2090M-1

#pragma once

#include "Matrix.h"

class BinaryImage : public Matrix
{

public:
	BinaryImage();
	BinaryImage(int M, int N);
	BinaryImage(int M, int N, double* input_data, double threshold);
	~BinaryImage();

	BinaryImage(const BinaryImage& other);
	BinaryImage operator-(const BinaryImage& other);

private:
	double threshold;


};     
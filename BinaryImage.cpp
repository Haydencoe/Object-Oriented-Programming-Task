

//Hayden Coe 309219
//Object-Orinated Programming, CMP2090M-1

#include "BinaryImage.h"
#include "Matrix.h"


BinaryImage::BinaryImage() : Matrix()
{}

BinaryImage::BinaryImage(int M, int N) : Matrix(M, N)
{}

// The constructor that contains rows, columns, an array to be inputted and threshold for binary conversion.
BinaryImage::BinaryImage(int M, int N, double* input_data, double threshold) : Matrix(M, N, input_data)
{

	for (int i = 0; i < M * N; i++)
	{
		if (theData[i] > threshold)
		{
			theData[i] = 1;
		}
		else
		{
			theData[i] = 0;
		}
	}
}

// Destructor deletes memory that's declared in BinaryImage.
BinaryImage::~BinaryImage()
{
	delete[] theData;
	theData = 0;
}


BinaryImage::BinaryImage(const BinaryImage& other) : Matrix(other)
{
	threshold = other.threshold;
}

//binary operator minus
BinaryImage BinaryImage::operator-(const BinaryImage& other)
{
	
	BinaryImage temp(other.M, other.N, other.theData, threshold);

	for (int i = 0; i < temp.M * temp.N; i++)
	{
		if (temp.theData[i] == other.theData[i])
		{
			temp.theData[i] = 0;
		}
		else
		{
			temp.theData[i] = 1;
		}
	}
	return temp;

}



//Hayden Coe 309219
//Object-Orinated Programming, CMP2090M-1
#include "Matrix.h"
#include <iostream>


Matrix::Matrix()
{
	M = 1;
	N = 1;

	theData = new double[M*N];

	for (int i = 0; i < M*N; i++)
	{
		theData[i] = 255;
	}
}

//Blank constructor 
Matrix::Matrix(int sizeR, int sizeC)
{
	M = sizeC;
	N = sizeR;

	theData = new double[M*N];

	for (int i = 0; i < M *N; i++)
	{
		theData[i] = 0;
	}
}

//Constructor with rows, columns and an array for the input 
Matrix::Matrix(int sizeR, int sizeC, double* input_data)
{
	M = sizeR; // assigns M to the number of rows
	N = sizeC; // assigns N to the number of columns

	theData = new double[M * N]; // the memory of the data is allocated to rows x columns

	for (int i = 0; i < (M * N); i++)
		theData[i] = input_data[i];  //loops until all the inputted array are set to the data 
}

//Copy constructor what creates a temp matrix object for the copied data 
Matrix::Matrix(const Matrix& objectName)
{
	
	M = objectName.M;
	N = objectName.N;

	theData = new double[M * N];

	for (int i = 0; i < (M * N); i++)
		theData[i] = objectName.theData[i];

}

// The Destructor will delete the data that had been created by the object.
Matrix::~Matrix()
{
	
	delete[] theData;
	theData = 0;

}

//Operator for equals 
Matrix Matrix::operator=(const Matrix& other)
{
		//delete existing data info
	delete[] theData;
	M = other.M;
	N = other.N;

	//reserve memory for new array
	theData = new double[M*N];

	//this pointer refers to the current object
	for (int x = 0; x < (M *N); x++)
	{
		this->theData[x] = other.theData[x];
	}

	return *this;
}


// Operator for minus
Matrix Matrix::operator-(const Matrix& other)
{
	
	Matrix temp;
	temp.M = other.M;
	temp.N = other.N;

	temp.theData = new double[temp.M * temp.N];

	for (int i = 0; i < (temp.M * temp.N); i++)
	{
		temp.theData[i] = this->theData[i] - other.theData[i];
	}

	return temp;
}

// Operator () with two value coordinates that return the value that's in that position  
double Matrix::operator()(int i, int j)
{
	
	return theData[i*N + j];
}


// get method returns a value from the location in the array
double Matrix::get(int i, int j)
{


	return theData[i * N + j];
}

//set method sets the inputted value to the correct position
void Matrix::set(int i, int j, double val)
{


	theData[i * N + j] = val;


}

//getData returns a pointer to a place in memory
double* Matrix::getData()
{
	return theData;
}



//The getBlock adds each value in the positions and adds it to a matrix 
Matrix Matrix::getBlock(int startColumn, int endColumn, int startRow, int endRow)
{
	int rows = (endRow - startRow) + 1;
	int columns = (endColumn - startColumn) + 1;

	double* temporaryData = new double[rows * columns];
	int count = 0;

	for (int i = startRow; i <= endRow; i++)
	{

		for (int j = startColumn; j <= endColumn; j++)
		{
			
			temporaryData[count] = theData[(i * N) + j];
			count++;
			
		}
	}

	Matrix returnMatrix(rows, columns, temporaryData);
	delete[] temporaryData;

	return returnMatrix; //returns the filled matrix
}


//The setBlock puts the values inside the block 
void Matrix::setBlock(Matrix block, int startColumn, int startRow)
{
	int i = startRow;
	int j = startColumn;
	
	int N = 512;

	int count = 0;
	for (int i = startRow; i < startRow + 32; i++)
	{
		for (int j = startColumn; j < startColumn + 32; j++)
		{
			
			this->theData[i * N + j] = block.theData[count];
			
			count++;
		}
	}
}

// function for the NC.
double Matrix::NC(Matrix block)
{
	double firstMean = mean(); 
	double secondMean = block.mean();
	double sumOne = 0;  
	double sumTwo = 0; 
	double sumThree = 0;
	
	for (int i = 0; i < M*N; i++)
	{
		double A = theData[i] - firstMean;
		double B = block.theData[i] - secondMean;
		sumOne += A * B;
		sumTwo += pow(A, 2);
		sumThree += pow(B, 2);
	}
	
	return sumOne / sqrt(sumTwo*sumThree);
}

// function for finding the mean of a matrix.
double Matrix::mean()
{
	double sum = 0;
	for (int i = 0; i < M*N; i++)
		sum += theData[i];
	return sum / (M*N);
}

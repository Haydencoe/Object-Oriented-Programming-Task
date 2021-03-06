// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
//Hayden Coe 309219
//Object-Orinated Programming, CMP2090M-1

#pragma once
#include <iostream>


class Matrix
{
public:
	Matrix();
	Matrix(int sizeR, int sizeC);
	Matrix(int sizeR, int sizeC, double* input_data);
	Matrix(const Matrix& objectName);
	~Matrix();

	Matrix operator=(const Matrix& other);
	Matrix operator-(const Matrix& other);

	double operator()(int i, int j);

	double get(int i, int j); 
	void set(int i, int j, double value);
	double* getData();
	
	Matrix getBlock(int startColumn, int endColumn, int startRow, int endRow);
	void setBlock(Matrix block, int startColomn, int startRow);

	double NC(Matrix block);
	double mean();

protected:
	int M, N;
	double *theData;
};



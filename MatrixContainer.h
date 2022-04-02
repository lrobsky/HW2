#pragma once
#include <matrix.h>
#include <iostream>
using std::ostream;

template<int row, int col, typename T = int>
class MatrixContainer
{
	Matrix<row, col, T>* dynamicContainer; // Matrix<row, col, T> or T*** 
	static int count;


public:


	MatrixContainer() // default constructor
	{

	}


	~MatrixContainer()
	{

	}
	void addMatrix(const Matrix<row, col, T>& mat)
	{
		dynamicContainer[count++] = &mat; // unsure
	}

	void removeLastMatrix()
	{
		dynamicContainer[count--] = NULL; //unsure

	}


};

template<int row, int col, typename T > int MatrixContainer<row, col, T>::count = 0;
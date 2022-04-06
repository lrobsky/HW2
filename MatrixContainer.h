#ifndef MATRIX_CONTAINER_H
#define MATRIX_CONTAINER_H
#include "matrix.h"
#include <iostream>
using std::ostream;

template<int row, int col, typename T = int>
class MatrixContainer
{
	Matrix<row, col, T>** dynamicArray; 
	 int count;
	 int arrayLength;


public:


	MatrixContainer(): count(0),arrayLength(1)   // default constructor
	{
		dynamicArray = new Matrix<row, col, T>*[1];
	}
	MatrixContainer(const MatrixContainer<row, col, T>& other) // need to fix memory leak in code
	{
		if (this != &other)
		{

			delete[] dynamicArray;
			dynamicArray = new Matrix<row, col, T>*[count];
			for (int i = 0; i < count; i++)
			{
				dynamicArray[i] = &(other.getDynamicArray()[i]);
			}
		}
	}

	MatrixContainer<row, col, T>& operator=(const MatrixContainer<row, col, T>& other)
	{
		delete[] dynamicArray;
		dynamicArray = new Matrix<row, col, T>*[count];
		for (int i = 0; i < count; i++)
		{
			dynamicArray[i] = &(other.getDynamicArray()[i]);
		}
		return *this;
	}

	~MatrixContainer()
	{
		for (int i = 0; i < count; i++)
		{
			delete dynamicArray[i];
		}
		delete[] dynamicArray;
	}
	void addMatrix(Matrix<row, col, T>& mat)
	{
		dynamicArray[count++] = &mat; 
		fixArray();
	}

	void removeLastMatrix()
	{
		delete dynamicArray[--count];
		fixArray();

	}

	Matrix<row, col, T> mulMatAtIndexByScalar(int index, const T scalar)
	{
		Matrix<row, col, T> temp = index;
		temp = temp * scalar;
		return temp;
	}

	Matrix<row, col, T> addMatricesAtIndexes(const int firstIndex, const int secondIndex) const
	{
		Matrix<row, col, T> tempMatrix = (*dynamicArray[firstIndex]) + (*dynamicArray[secondIndex]);
		return tempMatrix;
	}

	Matrix<row, col, T>** getDynamicArray()
	{
		return dynamicArray;
	}
	int limit()
	{
		return arrayLength;
	}

	friend ostream& operator<< (ostream& out, const MatrixContainer<row, col, T>& mat)
	{
		for (int i = 0; i < mat.count; i++)
		{
			out << *(mat.dynamicArray[i]);
		}
		return out;
	}

	int size()
	{
		return count;
	}

	void fixArray()
	{
		if (count==arrayLength)
		{
			Matrix<row, col, T>** tempArray = new Matrix<row, col, T>*[arrayLength * 2];
			for (int i = 0; i < count; i++)
			{
				tempArray[i] = dynamicArray[i];
			}
			delete dynamicArray;
			dynamicArray = tempArray;
			arrayLength *= 2;
		}
		else if(arrayLength>=count*4)
		{
			Matrix<row, col, T>** tempArray = new Matrix<row, col, T>*[arrayLength / 2];
			for (int i = 0; i < count; i++)
			{
				tempArray[i] = dynamicArray[i];
			}
			delete dynamicArray;
			dynamicArray = tempArray;
			arrayLength /= 2;
		}
	}
};





#endif
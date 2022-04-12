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


	MatrixContainer() : count(0), arrayLength(1)   // default constructor
	{
		dynamicArray = new Matrix<row, col, T>*[1];
	}
	MatrixContainer<row, col, T>& operator=(const MatrixContainer<row, col, T>& other) // assigment operator
	
	{
		if (this != &other)
		{
			this->arrayLength = other.arrayLength();
			this->count = other.count();
			freeArray();
			dynamicArray = new Matrix<row, col, T>*[count];
			for (int i = 0; i < count; i++)
			{
				Matrix<row, col, T>* tempMatrix = new Matrix<row, col, T>();
				*tempMatrix = other.DynamicArray[i]; // using overloaded assigment operator from matrix.h 
				dynamicArray[i] = tempMatrix;
			}
		}
	}

	MatrixContainer(const MatrixContainer<row, col, T>& other) // copy constructor
	{
		this->arrayLength = other.arrayLength();
		this->count = other.count();
		dynamicArray = new Matrix<row, col, T>*[arrayLength];
		for (int i = 0; i < count; i++)
		{
			Matrix<row,col,T>* tempMatrix = new Matrix<row, col, T>();
			*tempMatrix = other.DynamicArray[i]; // using overloaded assigment operator from matrix.h 
			dynamicArray[i] = tempMatrix;
		}
		return *this;
	}
	~MatrixContainer()
	{
		freeArray();
	}
	void freeArray()
	{
		for (int i = 0; i < count; i++)
		{
			if (dynamicArray[i] != NULL)
			{
				delete dynamicArray[i];
			}
		}
		delete[] dynamicArray;
	}
	void addMatrix(Matrix<row, col, T>& mat)
	{
		Matrix<row, col, T>* newMat = new Matrix<row, col, T>();
		*newMat = mat;
		dynamicArray[count++] = newMat;
		fixArray();
	}

	void removeLastMatrix()
	{
		Matrix<row, col, T>* temp = dynamicArray[--count];
		delete temp;
		dynamicArray[count] = NULL;
		fixArray();

	}

	Matrix<row, col, T> mulMatAtIndexByScalar(int index, const T scalar)
	{
		Matrix<row, col, T> temp = *dynamicArray[index];
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
		out << "There are " << mat.count << " matrices in the container. The matrices:" << std::endl;
		for (int i = 0; i < mat.count; i++)
		{
			out << *(mat.dynamicArray[i]);
			out << std::endl;
		}
		return out;
	}

	int size()
	{
		return count;
	}

	void fixArray()
	{
		if (count == arrayLength)
		{
			Matrix<row, col, T>** tempArray = new Matrix<row, col, T>*[arrayLength * 2];
			for (int i = 0; i < count; i++)
			{
				tempArray[i] = dynamicArray[i];
			}
			delete[] dynamicArray;
			dynamicArray = tempArray;
			arrayLength *= 2;
		}
		else if (arrayLength >= count * 4)
		{
			Matrix<row, col, T>** tempArray = new Matrix<row, col, T>*[arrayLength / 2];
			for (int i = 0; i < count; i++)
			{
				tempArray[i] = dynamicArray[i];
			}
			delete[] dynamicArray;
			dynamicArray = tempArray;
			arrayLength /= 2;
		}
	}
};





#endif
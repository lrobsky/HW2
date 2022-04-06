#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using std::ostream;

template <int row, int col, typename T = int > 
class Matrix
{

	T** data;



public:

	Matrix(const T defaultValue = 0)
	{
		memoryAllocate();
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				data[i][j] = defaultValue;
			}
		}

	}

	Matrix(const Matrix<row, col, T>& other)// copy constructor
	{
		memoryAllocate();
		initMatrix(other);

	}

	~Matrix() // destuctor
	{
		freeMemory();
	}

	void initMatrix(const Matrix<row, col, T>& other) // intialize matrix with values from another matrix
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				this->data[i][j] = other.getData()[i][j];

			}
		}
	}

	Matrix<row, col, T>& operator=(const Matrix<row, col, T>& other)// assigment operator
	{
		if (this != &other)
		{
			initMatrix(other);

		}
		return *this;
	}

	T* getDiag(int& length) const // WORKING
	{
		length = std::min(row, col);
		T* diagArray = new T[length];
		for (int i = 0; i < length; i++)
		{
			diagArray[i] = data[i][i];
		}
		return diagArray;

	}

	T** getData() const
	{
		return data;
	}


	friend Matrix<row, col, T> operator+(const Matrix<row, col, T>& mat1, const Matrix<row, col, T>& mat2)
	{
		Matrix<row, col, T> temp = mat1;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				temp.data[i][j] += (mat2.data)[i][j];
			}
		}
		return temp;
	}
	friend Matrix<row, col, T> operator+(const Matrix<row, col, T>& mat1, const T value)
	{
		Matrix<row, col, T> temp(value);
		return temp + mat1;
	}
	friend Matrix<row, col, T> operator+(const T value, const Matrix<row, col, T>& mat) 
	{
		Matrix<row, col, T> temp(value);
		return temp + mat;
	}

	friend Matrix<row, col, T> operator-(const Matrix<row, col, T>& mat1, const Matrix<row, col, T>& mat2) 
	{
		Matrix<row, col, T> temp = mat1;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				temp.data[i][j] -= (mat2.data)[i][j];
			}
		}
		return temp;
	}

	Matrix<row, col, T> operator-(const T value) const
	{
		Matrix<row, col, T> temp(value);
		return (*this) - temp;
	}
	friend Matrix<row, col, T> operator-(const T value, const Matrix<row, col, T>& mat) 
	{
		Matrix<row, col, T> temp(value);
		return temp - mat;
	}
	Matrix<row, col, T> operator-()// unary
	{
		Matrix<row, col, T> temp = *this;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				data[i][j] *= -1;
			}
		}

		return temp;
	}
	Matrix<row, col, T> getIdentityMatrix() const // identity
	{
		
		Matrix<row, col, T> id ;
		for (int i = 0; i < row; i++)
		{
			id.getData()[i][i] = 1;
		}
		return id;
	}

	Matrix<row, col, T> operator++(int) // postfix
	{
		Matrix<row, col, T> temp = *this;// usage of copy constructor?
		++(*this);
		return temp;
	}

	Matrix<row, col, T>& operator++() // prefix
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				data[i][j]++;
			}
		}
		return *this;
	}

	Matrix<row, col, T> operator--(int) //  postfix
	{
		Matrix<row, col, T> temp = *this;
		--(*this);
		return temp;
	}

	Matrix<row, col, T>& operator--() //prefix
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				data[i][j]--;
			}
		}
		return *this;
	}

	friend ostream& operator<< (ostream& out, const Matrix<row, col, T>& mat1)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				out << mat1.data[i][j] << " ";
			}
			out << std::endl;
		}
		return out;
	}

	T& operator()(const int row, const int col) const
	{
		return data[row][col];
	}

	bool operator==(Matrix<row, col, T>&other)
	{
		T** temp = other.getArray();
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				
				if (std::abs(data[i][j] - temp[i][j])>DBL_EPSILON) // If values are not equal return 0/false.
				{
					return 0;
				}
			}
		}
		return 1;
	}

	bool operator!=(Matrix<row, col, T>&other)
	{

		if (*this == other)
		{
			return 0;
		}
		return 1;
	}

	Matrix<row, col, T> operator*(T scalar)
	{
		Matrix<row, col, T> temp = *this;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				temp.data[i][j] *= scalar;
			}
		}
		return temp;
	}

	operator T() const // 
	{
		T temp = 0;
		for (int i = 0; i < std::min(row, col); i++)
		{
			temp += data[i][i];
		}
		return temp;
	}

	void memoryAllocate()
	{
		data = new T * [row];
		for (int i = 0; i < row; i++)
		{
			data[i] = new T[col];
		}
	}
	void freeMemory()
	{
			return;
		for (int i = 0; i < row; i++)
		{
			delete[] data[i];
		}
			delete[] data;
		
		
	}
};

	

	//broken code section

	//friend Matrix <row, col, T> operator*(Matrix <row1, col1, T>& mat1, Matrix <row2, col2, T>& mat2) // template parameters might be incorrect
		//{
		//	if (col1 != row2)
		//	{
		//		error("cant multiply matrixes");
		//	}
		//	Matrix <row, col, T> temp;

		//	for (int i = 0; i < row1; i++)
		//	{
		//		for (int j = 0; j < col2; j++)
		//		{

		//			for (int k = 0; k < col1; k++)
		//			{
		//				temp.data[i][j] += mat1.data[i][k] * mat2.data[k][j];
		//			}

		//		}
		//	}
		//	return temp;
		//}

#endif

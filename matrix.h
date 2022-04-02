#pragma once
#include <iostream>
using std::ostream;

template <int row, int col, typename T = int > 
class Matrix
{
	
	T** data;



public:

	Matrix(T defaultValue = 0) // default constructor - set every cell to default value
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

	Matrix(Matrix<row, col, T>& other)// copy constructor
	{
		initMatrix(other);
	}

	~Matrix() // destuctor
	{
		freeMemory();
	}

	void initMatrix(const Matrix<row, col, T>& other) // intialize matrix with values from another matrix
	{
		//freeMemory(data); 
		//memoryAllocate(data);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				data[i][j] = other[i][j];// CHECK LATER
			}
		}
	}

	Matrix<row, col, T>& operator=(Matrix<row, col, T>& other)// assigment operator
	{
		if (this != &other)
		{
			initMatrix(other);
		}
		return *this;
	}

	int& getDiag(int& length) const
	{
		return length = std::min(row, col);
		
	}

	T** getdata() const
	{
		return data;
	}
	


	Matrix<row, col, T> operator+(int value)
	{
	  Matrix<row, col, T> temp1(value); 
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				temp1.data[i][j] = temp1.data[i][j] + this->data[i][j];
			}
		 }
		return temp1;

	}
	friend Matrix<row, col, T> operator+(const Matrix<row, col, T>& mat1, const Matrix<row, col, T>& mat2)
	{
		Matrix<row, col, T> temp = mat1;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				temp.data[i][j] += (mat2.data)[i][j]; // swap friend with getArray function?
			}
		}
		return temp;
	}
	friend Matrix<row, col, T> operator-(const Matrix<row, col, T>& mat1, const Matrix<row, col, T>& mat2)
	{
		Matrix<row, col, T> temp = mat1;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				temp.data[i][j] -= (mat2.data)[i][j]; // swap friend with getArray() function?
			}
		}
		return temp;
	}

	//Matrix<row, col, T> operator-(const matrix<row, col, T>& other);

	Matrix<row, col, T>& getIdentityMatrix() const // identity
	{
		if (row != col) // CHECK LATER
		{
			throw("error");
		}
		Matrix<row, col, T> id;
		for (int i = 0; i < row; i++)
		{
			id.getdata()[i][i] = 1;
		}
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

	

	friend ostream& operator<<(ostream& out, const Matrix<row, col, T>& mat1);

	T& operator()(int row, int col)
	{
		return data[row][col];
	}

	bool operator==(Matrix<row, col, T>& other)
	{
		if (row != col)// change later - check if both matrixes have same measurments
		{
			throw("error");
		}
		T** temp = other.getArray();
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (data[i][j] != temp[i][j])
				{
					return 0
				}
			}
		}
		return 1;
	}

	bool operator!=(Matrix<row, col, T>& other)
	{
		
		if (*this == other)
		{
			return 0;
		}
		return 1;
	}

	Matrix <row, col, T>& operator*(int scalar) //
	{
		Matrix<row, col, T> temp = mat1;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				temp.data[i][j] *= scalar; // swap friend with getArray() function?
			}
		}
		return temp;
	}

	friend Matrix <row, col, T> operator*(Matrix <row1, col1, T>& mat1, Matrix <row2, col2, T>& mat2) // template parameters might be incorrect
	{
		if (col1 != row2)
		{
			error("cant multiply matrixes");
		}
		Matrix <row, col, T> temp;


		for (int i = 0; i < row1; i++)
		{
			for (int j = 0; j < col2; j++)
			{

				for (int k = 0; k < col1; k++)
				{
					temp.data[i][j] += mat1.data[i][k] * mat2.data[k][j];
				}

			}
		}
		return temp;
	}

	 operator T() const
	{
		T temp = 0;
		for (int i = 0; i < getDiag(); i++)
		{
			temp += data[i][i];
		}
		return temp;
	}

	void memoryAllocate()
	{
		data = new T*[row];
		for (int i = 0; i < row; i++)
		{
			data[i] = new T[col];	
		}
	}
	void freeMemory(T** data)
	{
		for (int i = 0; i < row; i++)
		{
			delete[] data[i];
		}
		delete[] data;
	}
};

template<int row, int col, typename T>
ostream& operator<< (ostream & out, const Matrix<row,col,T>& mat1)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			out << mat1.data[i][j] << " ";
		}
		out << endl;
	}
	return out;
}
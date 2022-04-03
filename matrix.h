#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using std::ostream;

template <int row, int col, typename T = int > 
class Matrix
{
	
	T** data;



public:

	 Matrix(T defaultValue=0) // WORKING
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

	Matrix& operator=(const Matrix<row, col, T>& other)// assigment operator
	{
		if (this != &other)
		{
			initMatrix(other);

		}
		return *this;
	}

	int& getDiag(int& length) const // WORKING
	{
		return length = std::min(row, col);
		
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

	Matrix operator-()
	{
		return *this * (-1);
	}

	Matrix& getIdentityMatrix() const // identity
	{
		if (row != col) // CHECK LATER
		{
			throw("error");
		}
		Matrix<row, col, T> id;
		for (int i = 0; i < row; i++)
		{
			id.getData()[i][i] = 1;
		}
	}

	Matrix operator++(int) // postfix
	{
		Matrix<row, col, T> temp = *this;// usage of copy constructor?
		++(*this);
		return temp;
	}

	Matrix& operator++() // prefix
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

	Matrix operator--(int) //  postfix
	{
		Matrix<row, col, T> temp = *this;
		--(*this);
		return temp;
	}

	Matrix& operator--() //prefix
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

	

	template <int row, int col, typename T > friend ostream& operator<<(ostream& out, const Matrix<row, col, T>& mat1);

	T& operator()(int row, int col)
	{
		return data[row][col];
	}

	bool operator==(Matrix<row, col, T>& other)
	{
		T** temp = other.getArray();
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (data[i][j] != temp[i][j])
				{
					return 0;
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

	Matrix& operator*(int scalar) //
	{
		Matrix<row, col, T> temp = *this;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				temp.data[i][j] *= scalar; // swap friend with getArray() function?
			}
		}
		return temp;
	}

	 explicit operator T() const // not working properly*******
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
		data = new T*[row];
		for (int i = 0; i < row; i++)
		{
			data[i] = new T[col];	
		}
	}
	void freeMemory()
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
		out << std::endl;
	}
	return out;
}

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
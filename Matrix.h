#pragma once
#include <string>


class Matrix {
	int columns;
	int rows;
	double** data;
public:

	Matrix();
	Matrix(int num, int in_columns, int in_rows);

//2-dimensional array with numbers into a class object.
	Matrix(const int* array, int row, int col);

//copy constructor
	Matrix(const Matrix& source);

//copy assignment operator
	Matrix& operator=(const Matrix& source);

//move constructor
	Matrix(Matrix&& source);

//move operator
	Matrix& operator=(Matrix&& source) noexcept;

//+operator
	const Matrix operator+(Matrix& right_obj) const;

//-operator
	const Matrix operator-(Matrix& right_obj) const;

//*operator (obj)
	const Matrix operator*(Matrix& right_obj) const;

//*operator (num)
	const Matrix operator*(int mult_num) const;

//'/'operator (obj)
	const Matrix operator/(Matrix& right_obj) const;
	
//'/'operator (num)
	const Matrix operator/(int divisor_number) const;

//+=operator
	Matrix& operator+=(Matrix& right_obj);

//-=operator
	Matrix& operator-=(Matrix& right_obj);


//string to array conversion ctor
	Matrix(const char* char_array);
	~Matrix();
	
	void print_array();

	std::string to_string(const Matrix& source);
};


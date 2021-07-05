#pragma once
#include <string>


class Matrix {
	int rows;
	int columns;
	double** data;
public:

	Matrix();
	Matrix(int num, int in_rows, int in_columns);

//2-dimensional array with numbers into a class object.
	Matrix(const int* array, int in_rows, int in_columns);

//copy constructor
	Matrix(const Matrix& source);

//move constructor
	Matrix(Matrix&& source);

//string to array conversion ctor
	Matrix(const char* char_array);
//destructor
	~Matrix();


//copy assignment operator
	Matrix& operator=(const Matrix& source);

//move operator
	Matrix& operator=(Matrix&& source) noexcept;


//+operator (obj)
	const Matrix operator+(Matrix& right_obj) const;

//+operator (num)
	const Matrix operator+(double inc_num) const;

//+operator (string)
	const Matrix operator+(const char* str) const;

//-operator (obj)
	const Matrix operator-(Matrix& right_obj) const;

//-operator (num)
	const Matrix operator-(double decr_num) const;

//-operator (string)
	const Matrix operator-(const char* str) const;

//*operator (obj)
	const Matrix operator*(Matrix& right_obj) const;

//*operator (num)
	const Matrix operator*(double mult_num) const;

//*operator (string)
	const Matrix operator*(const char* str) const;

//'/'operator (obj)
	const Matrix operator/(Matrix right_obj) const;
	
//'/'operator (num)
	const Matrix operator/(double divisor_number) const;

//'/'operator (string)
	const Matrix operator/(const char* str) const;


//+=operator (obj)
	Matrix& operator+=(Matrix& right_obj);

//+=operator (num)
	Matrix& operator+=(double inc_num);

//-=operator (obj)
	Matrix& operator-=(Matrix& right_obj);

//-=operator (num)
	Matrix& operator-=(double decr_num);

//*=operator (obj)
	Matrix operator*=(Matrix& right_obj);

//*=operator (num)
	Matrix operator*=(double mult_num);

//'/'=operator (obj)
	Matrix operator/=(Matrix right_obj);

//'/'*=operator (num)
	Matrix operator/=(double divisor_number);


//>operator
	bool operator>(const Matrix& right_obj);

//<operator
	bool operator<(const Matrix& right_obj);

//>=operator
	bool operator>=(const Matrix& right_obj);

//<=operator
	bool operator<=(const Matrix& right_obj);

//==operator
	bool operator==(const Matrix& right_obj);

//!=operator
	bool operator!=(const Matrix& right_obj);

	void print_array();

	std::string to_string(const Matrix& source);
};


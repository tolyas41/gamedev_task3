#pragma once
#include <string>
#include <cstddef>

class Matrix {
	int rows;
	int columns;
	double** data;
public:

	Matrix();
	Matrix(int num, int in_rows, int in_columns);

//2-dimensional array with numbers into a class object.
	Matrix(const double* array, int in_rows, int in_columns);

//copy constructor
	Matrix(const Matrix& source);

//move constructor
	Matrix(Matrix&& source);

//string to array conversion ctor
	Matrix(const char* char_array);

	Matrix(std::nullptr_t ptr);
//destructor
	~Matrix();


//copy assignment operator
	Matrix& operator=(const Matrix& source);

//move operator
	Matrix& operator=(Matrix&& source) noexcept;


//+operator (obj)
	const Matrix operator+(Matrix& right_obj) const;

//+operator (num)
	const Matrix operator+(int additionValue) const;

//+operator (string)
	const Matrix operator+(const char* str) const;

//-operator (obj)
	const Matrix operator-(Matrix& right_obj) const;

//-operator (num)
	const Matrix operator-(int subtractionValue) const;

//-operator (string)
	const Matrix operator-(const char* str) const;

//*operator (obj)
	const Matrix operator*(Matrix& right_obj) const;

//*operator (num)
	const Matrix operator*(int multiplicationValue) const;

//*operator (string)
	const Matrix operator*(const char* str) const;

//'/'operator (obj)
	const Matrix operator/(Matrix right_obj) const;
	
//'/'operator (num)
	const Matrix operator/(int divisionValue) const;

//'/'operator (string)
	const Matrix operator/(const char* str) const;


//+=operator (obj)
	Matrix& operator+=(Matrix& right_obj);

//+=operator (num)
	Matrix& operator+=(int additionValue);

//-=operator (obj)
	Matrix& operator-=(Matrix& right_obj);

//-=operator (num)
	Matrix& operator-=(int subtractionValue);

//*=operator (obj)
	Matrix operator*=(Matrix& right_obj);

//*=operator (num)
	Matrix operator*=(int multiplicationValue);

//'/'=operator (obj)
	Matrix operator/=(Matrix right_obj);

//'/'*=operator (num)
	Matrix operator/=(int divisionValue);


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
	double dataSumm(const Matrix& obj);
	int checkOverflow(int valueLeft, int valueRight, const std::string& operation) const;

};


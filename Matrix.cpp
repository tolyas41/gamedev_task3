#include "Matrix.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <float.h>

Matrix::Matrix()
	: columns(0), rows(0), data(nullptr) {
}

//2. Contain a type conversion constructor that converts the 
//directly specified numerical constant with a sign into a class object.

Matrix::Matrix(std::nullptr_t ptr) {
	rows = 0;
	columns = 0;
	data = ptr;
}

Matrix::Matrix(int num, int in_rows, int in_columns)
	: rows(in_rows), columns(in_columns) {
		data = new double* [rows];					
		for (int i = 0; i < rows; i++) {
			data[i] = new double[columns];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				data[i][j] = num;
			}
		}		
}

//3. Contain a type conversion constructor that converts a directly specified 
//2-dimensional array with numbers into a class object.

Matrix::Matrix(const double* array, int in_rows, int in_columns)
	: rows(in_rows), columns(in_columns) {
		data = new double* [rows];
		for (int i = 0; i < rows; i++) {
			data[i] = new double[columns];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				data[i][j] = array[i * columns + j];
			}	
		}
}

//destructor
Matrix::~Matrix() {
	for (int i = 0; i < rows; i++) {
		delete[] data[i];
	}
	delete[] data;
}

//deep copy constructor
Matrix::Matrix(const Matrix& source) 
	: rows(source.rows), columns(source.columns) {
		data = new double* [rows];
		for (int i = 0; i < rows; i++) {
			data[i] = new double[columns];
		}
		
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				data[i][j] = source.data[i][j];
			}
		}	
}

//move constructor
Matrix::Matrix(Matrix&& source) 
	: rows(source.rows), columns(source.columns), data(source.data) {
		source.rows = 0;
		source.columns = 0;
		source.data = nullptr;
}

//string to array conversion ctor
Matrix::Matrix(const char* char_array) {

	int str_length = 0;
	bool isValid = true;

	while (char_array[str_length] != '\0') {
		str_length++;
	}
	if (char_array[0] != '[' || char_array[str_length - 1] != ']') {
		isValid = false;
	}
	if (isValid) {
		int str_cols = 1;
		for (int i = 1; i < str_length - 1; i++) {
			if (char_array[i] == ';') {
					str_cols++;
					if (char_array[i + 1] != ' ' && (char_array[i + 1] < '0' || char_array[i + 1] > '9')) {
						isValid = false;
					}
				}
			}
		int str_columns = 1;
		int prev_str_columns = 1;
		bool first_semicolon_pass = false;
		for (int i = 1; i <= str_length - 1; i++) {
			if (char_array[i] == ',') {
				str_columns++;
				if (char_array[i + 1] < '0' || char_array[i + 1] > '9') {
					isValid = false;
				}
			}
			if ((char_array[i] == ';' || char_array[i] == ']') && first_semicolon_pass) {
				if (prev_str_columns != str_columns) {
					isValid = false;
				}
			}
			if (char_array[i] == ';') {
				first_semicolon_pass = true;
				prev_str_columns = str_columns;
				str_columns = 1;
			}
		}

		if (isValid) {
			std::vector < std::vector<int> > temp_vec(str_cols, std::vector<int>(str_columns, 0));
			for (int i = 0, j = 0, k = 1; k < str_length - 1 && isValid; k++) {
				switch (char_array[k]) {
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					temp_vec[i][j] = temp_vec[i][j] * 10 + char_array[k] - '0';
					break;
				case ',':
					j++;
					break;
				case ';':
					i++;
					j = 0;
					break;
				case ' ':
					break;
				default:
					isValid = false;
					break;
				}
			}
			if (isValid) {
				rows = str_cols;
				columns = str_columns;
				data = new double* [rows];
				for (int i = 0; i < rows; i++) {
					data[i] = new double[columns];
				}
				int k = 0;
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < columns; j++) {
						data[i][j] = temp_vec[i][j];
					}
				}
			}
		}
	}
	if (isValid == false) {
		rows = 0;
		columns = 0;
		data = nullptr;
		std::cout << "\n==INVALID STRING==\n";
	}
}

//copy assignment operator
Matrix& Matrix::operator=(const Matrix& source) {
	if (this != &source) {
		for (int i = 0; i < rows; i++) {
			delete[] data[i];
		}
		delete[] data;
		rows = source.rows;
		columns = source.columns;
		data = new double* [rows];
		for (int i = 0; i < rows; i++) {
			data[i] = new double[columns];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				data[i][j] = source.data[i][j];
			}		
		}	
	}
	return *this;
}

//move operator
Matrix& Matrix::operator=(Matrix&& source) noexcept {
	if (this != &source) {
		for (int i = 0; i < rows; i++) {
			delete[] data[i];
		}
		delete[] data;
		rows = source.rows;
		columns = source.columns;
		data = source.data;

		source.rows = 0;
		source.columns = 0;
		source.data = nullptr;
	}
	return *this;
}

//print every element of the object's array
void Matrix::print_array() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			std::cout << std::fixed << std::setprecision(1) << std::setw(4) << data[i][j];
			if (j != columns - 1) {
				std::cout << " | ";
			}
		}
		std::cout << "\n";
	}
}

//object to string converter
std::string Matrix::to_string(const Matrix& source) {
	std::string temp;
	temp += "[";
	for (int i = 0; i < source.rows; i++) {
		if (i != 0) {
			temp += "; ";
		}
		for (int j = 0; j < source.columns; j++) {
			temp += std::to_string(data[i][j]);
			if (j != source.columns - 1) {
				temp += ",";
			}
		}
	}
	temp += "]";
	return temp;
}

//+operator (obj)
const Matrix Matrix::operator+(Matrix& right_obj) const {
	if (rows == right_obj.rows && columns == right_obj.columns) {
		Matrix result (0, rows, columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				result.data[i][j] = checkOverflowAddition(data[i][j], right_obj.data[i][j]);
			}
		}
		return result;
	}
	else {
		std::cout << "\nmatrices are not consistent!\n";
		return nullptr;
	}
}

//+operator (num)
const Matrix Matrix::operator+(int additionValue) const {
	Matrix result(0, rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			result.data[i][j] = checkOverflowAddition(data[i][j], additionValue);
		}
	}
	return result;
}

//+operator (string)
const Matrix Matrix::operator+(const char* str) const {
	return *this + std::stoi(str);
}

//-operator (obj)
const Matrix Matrix::operator-(Matrix& right_obj) const {
	if (rows == right_obj.rows && columns == right_obj.columns) {
		Matrix result (0, rows, columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				result.data[i][j] = checkOverflowSubtraction(data[i][j], right_obj.data[i][j]);
			}
		}
		return result;
	}
	else {
		std::cout << "\nmatrices are not consistent!\n";
		return nullptr;
	}
}

//-operator (num)
const Matrix Matrix::operator-(int subtractionValue) const {
	Matrix result(0, rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			result.data[i][j] = checkOverflowSubtraction(data[i][j], subtractionValue);
		}
	}
	return result;
}

//-operator (string)
const Matrix Matrix::operator-(const char* str) const {
	return *this - std::stoi(str);
}

//*operator (obj)
const Matrix Matrix::operator*(Matrix& right_obj) const {
	if (columns == right_obj.rows) {
		Matrix result(0, rows, right_obj.columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < right_obj.columns; j++) {
				for (int m = 0; m < right_obj.rows; m++) {
					result.data[i][j] += data[i][m] * right_obj.data[m][j];
				}
			}
		}
		return result;
	}
	else {
		std::cout << "\nmatrices are not consistent!\n";
		return nullptr;
	}
}

//*operator (num)
const Matrix Matrix::operator*(int multiplicationValue) const {
	Matrix result(0, rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			result.data[i][j] = data[i][j] * multiplicationValue;
		}
	}
	return result;
}

//*operator (string)
const Matrix Matrix::operator*(const char* str) const {
	return *this * std::stoi(str);
}

//'/'operator (obj)
const Matrix Matrix::operator/(Matrix right_obj) const {
	if (right_obj.columns == right_obj.rows) {
		Matrix inverse_matrix(0, right_obj.columns, right_obj.columns);
		for (int i = 0; i < right_obj.columns; i++) {
			inverse_matrix.data[i][i] = 1;
		}
		//straight
		for (int i = 0; i < right_obj.rows; i++) {
			double diagonal = right_obj.data[i][i];
			for (int j = 0; j < right_obj.columns; j++) {
				right_obj.data[i][j] /= diagonal;
				inverse_matrix.data[i][j] /= diagonal;
			}
			for (int k = i + 1; k < right_obj.columns; k++) {
				double element_below_diagonal = right_obj.data[k][i];
				for (int m = 0; m < right_obj.columns; m++) {
					right_obj.data[k][m] -= (right_obj.data[i][m] * element_below_diagonal);
					inverse_matrix.data[k][m] -= (inverse_matrix.data[i][m] * element_below_diagonal);
				}
			}
		}
		//reverse
		for (int i = right_obj.rows - 1; i > 0; i--) {
			for (int k = i - 1; k >= 0; k--) {
				double element_above_diagonal = right_obj.data[k][i];
				for (int m = right_obj.columns - 1; m >= 0; m--) {
					right_obj.data[k][m] -= (right_obj.data[i][m] * element_above_diagonal);
					inverse_matrix.data[k][m] -= (inverse_matrix.data[i][m] * element_above_diagonal);
				}
			}
		}
		return *this * inverse_matrix;
	}
	else {
		std::cout << "divisor matrix is not square!";
		return nullptr;
	}
}

//'/'operator (num)
const Matrix Matrix::operator/(int divisionValue) const {
	Matrix result(0, rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (divisionValue != 0) {
				result.data[i][j] = data[i][j] / divisionValue;
			}
			else {
				result.data[i][j] = 0;
			}
		}
	}
	return result;
}

//'/'operator (string)
const Matrix Matrix::operator/(const char* str) const {
	return *this / std::stoi(str);
}

//+=operator (obj)
Matrix& Matrix::operator+=(Matrix& right_obj) {
	*this = *this + right_obj;
	return *this;
}

//+=operator (num)
Matrix& Matrix::operator+=(int additionValue) {
	*this = *this + additionValue;
	return *this;
}

//-=operator (obj)
Matrix& Matrix::operator-=(Matrix& right_obj) {
	*this = *this - right_obj;
	return *this;
}

//-=operator (num)
Matrix& Matrix::operator-=(int subtractionValue) {
	*this = *this - subtractionValue;
	return *this;
}

//*=operator (obj)
Matrix Matrix::operator*=(Matrix& right_obj) {
	*this = *this * right_obj;
	return *this;
}

//*=operator (num)
Matrix Matrix::operator*=(int multiplicationValue) {
	*this = *this * multiplicationValue;
	return *this;
}

//'/'=operator (obj)
Matrix Matrix::operator/=(Matrix right_obj) {
	*this = *this / right_obj;
	return *this;
}

//'/'=operator (num)
Matrix Matrix::operator/=(int divisionValue) {
	*this = *this / divisionValue;
	return *this;
}

//>operator
bool Matrix::operator>(const Matrix& right_obj) {
	return dataSumm(*this) > dataSumm(right_obj);
}

//<operator
bool Matrix::operator<(const Matrix& right_obj) {
	return dataSumm(*this) < dataSumm(right_obj);
}

//>=operator
bool Matrix::operator>=(const Matrix& right_obj) {
	return dataSumm(*this) >= dataSumm(right_obj);
}

//<=operator
bool Matrix::operator<=(const Matrix& right_obj) {
	return dataSumm(*this) <= dataSumm(right_obj);
}

//==operator
bool Matrix::operator==(const Matrix& right_obj) {
	return dataSumm(*this) == dataSumm(right_obj);
}

//!=operator
bool Matrix::operator!=(const Matrix& right_obj) {
	return dataSumm(*this) != dataSumm(right_obj);
}

int Matrix::checkOverflowAddition(int valueLeft, int valueRight) const {
	if ((valueRight >= 0 && valueLeft > INT_MAX - valueRight) ||
		(valueRight <= 0 && valueLeft < INT_MIN - valueRight)) {
		std::cout << "\nint variable overflow!\n";
		return 0;
	}
	else {
		return valueLeft + valueRight;
	}
}

int Matrix::checkOverflowSubtraction(int valueLeft, int valueRight) const {
	if ((valueRight <= 0 && valueLeft > INT_MAX + valueRight) ||
		(valueRight >= 0 && valueLeft < INT_MIN + valueRight)) {
		std::cout << "\nint variable overflow!\n";
		return 0;
	}
	else {
		return valueLeft - valueRight;
	}
}

double Matrix::dataSumm(const Matrix& obj) {
	double summ{};
	for (int i = 0; i < obj.rows; i++) {
		for (int j = 0; j < obj.columns; j++) {
			summ += obj.data[i][j];
		}
	}
	return summ;
}

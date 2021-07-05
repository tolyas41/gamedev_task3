#include "Matrix.h"
#include <iostream>
#include <vector>
#include <iomanip>

Matrix::Matrix()
	: columns(0), rows(0), data(nullptr) {
}

//2. Contain a type conversion constructor that converts the 
//directly specified numerical constant with a sign into a class object.

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

Matrix::Matrix(const int* array, int in_rows, int in_columns)
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

	int str_numbers_length = 0;
	bool valid_str_numbers = true;

	while (char_array[str_numbers_length] != '\0') {
		str_numbers_length++;
	}
	if (char_array[0] != '[' || char_array[str_numbers_length - 1] != ']') {
		valid_str_numbers = false;
	}
	if (valid_str_numbers) {
		int str_cols = 1;
		for (int i = 1; i < str_numbers_length - 1; i++) {
			if (char_array[i] == ';') {
					str_cols++;
					if (char_array[i + 1] != ' ' && (char_array[i + 1] < '0' || char_array[i + 1] > '9')) {
						valid_str_numbers = false;
					}
				}
			}
		int str_columns = 1;
		int prev_str_columns = 1;
		bool first_semicolon_pass = false;
		for (int i = 1; i <= str_numbers_length - 1; i++) {
			if (char_array[i] == ',') {
				str_columns++;
				if (char_array[i + 1] < '0' || char_array[i + 1] > '9') {
					valid_str_numbers = false;
				}
			}
			if ((char_array[i] == ';' || char_array[i] == ']') && first_semicolon_pass) {
				if (prev_str_columns != str_columns) {
					valid_str_numbers = false;
				}
			}
			if (char_array[i] == ';') {
				first_semicolon_pass = true;
				prev_str_columns = str_columns;
				str_columns = 1;
			}
		}

		if (valid_str_numbers) {
			std::vector < std::vector<int> > temp_vec(str_cols, std::vector<int>(str_columns, 0));
			for (int i = 0, j = 0, k = 1; k < str_numbers_length - 1 && valid_str_numbers; k++) {
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
					valid_str_numbers = false;
					break;
				}
			}
			if (valid_str_numbers) {
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
	if (valid_str_numbers == false) {
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
		Matrix obj_to_return (0, rows, columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				obj_to_return.data[i][j] = data[i][j] + right_obj.data[i][j];
			}
		}
		return obj_to_return;
	}
	else {
		int overflow_rows;
		int overflow_columns;
		if (rows > right_obj.rows) {
			overflow_rows = rows;
		}
		else {
			overflow_rows = right_obj.rows;
		}
		if (columns > right_obj.columns) {
			overflow_columns = columns;
		}
		else {
			overflow_columns = right_obj.columns;
		}

		Matrix overflowobj(0, overflow_rows, overflow_columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				overflowobj.data[i][j] += data [i][j];
			}
		}
		for (int i = 0; i < right_obj.rows; i++) {
			for (int j = 0; j < right_obj.columns; j++) {
				overflowobj.data[i][j] += right_obj.data [i][j];
			}
		}
		return overflowobj;
	}
}

//+operator (num)
const Matrix Matrix::operator+(double inc_num) const {
	Matrix obj_to_return(0, rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			obj_to_return.data[i][j] = data[i][j] + inc_num;
		}
	}
	return obj_to_return;
}

//+operator (string)
const Matrix Matrix::operator+(const char* str) const {
	Matrix obj_to_return;
	Matrix str_obj(str);
	obj_to_return = *this + str_obj;
	return obj_to_return;
}

//-operator (obj)
const Matrix Matrix::operator-(Matrix& right_obj) const {
	if (rows == right_obj.rows && columns == right_obj.columns) {
		Matrix obj_to_return (0, rows, columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				obj_to_return.data[i][j] = data[i][j] - right_obj.data[i][j];
			}
		}
		return obj_to_return;
	}
	else {
		int overflow_rows;
		int overflow_columns;
		if (rows > right_obj.rows) {
			overflow_rows = rows;
		}
		else {
			overflow_rows = right_obj.rows;
		}
		if (columns > right_obj.columns) {
			overflow_columns = columns;
		}
		else {
			overflow_columns = right_obj.columns;
		}

		Matrix overflowobj(0, overflow_rows, overflow_columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				overflowobj.data[i][j] += data [i][j];
			}
		}
		for (int i = 0; i < right_obj.rows; i++) {
			for (int j = 0; j < right_obj.columns; j++) {
				overflowobj.data[i][j] -= right_obj.data [i][j];
			}
		}
		return overflowobj;
	}
}

//-operator (num)
const Matrix Matrix::operator-(double decr_num) const {
	Matrix obj_to_return(0, rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			obj_to_return.data[i][j] = data[i][j] - decr_num;
		}
	}
	return obj_to_return;
}

//-operator (string)
const Matrix Matrix::operator-(const char* str) const {
	Matrix obj_to_return;
	Matrix str_obj(str);
	obj_to_return = *this - str_obj;
	return obj_to_return;
}

//*operator (obj)
const Matrix Matrix::operator*(Matrix& right_obj) const {
	if (rows == right_obj.rows && columns == right_obj.columns) {
		Matrix obj_to_return(0, rows, columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				for (int m = 0; m < rows; m++) {
					obj_to_return.data[i][j] += data[i][m] * right_obj.data[m][j];
				}
			}
		}
		return obj_to_return;
	}
	else if (columns == right_obj.rows) {
		Matrix obj_to_return(0, rows, right_obj.columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < right_obj.columns; j++) {
				for (int m = 0; m < right_obj.rows; m++) {
					obj_to_return.data[i][j] += data[i][m] * right_obj.data[m][j];
				}
			}
		}
		return obj_to_return;
	}
	else {
		std::cout << "\nmatrices are not consistent!\n";
		Matrix nullobj(0, 0, 0);
		return nullobj;
	}
}

//*operator (num)
const Matrix Matrix::operator*(double mult_num) const {
	Matrix obj_to_return(0, rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			obj_to_return.data[i][j] = data[i][j] * mult_num;
		}
	}
	return obj_to_return;
}

//*operator (string)
const Matrix Matrix::operator*(const char* str) const {
	Matrix obj_to_return;
	Matrix str_obj(str);
	obj_to_return = *this * str_obj;
	return obj_to_return;
}


//'/'operator (obj)
const Matrix Matrix::operator/(Matrix right_obj) const {
	if (right_obj.columns == right_obj.rows) {
		Matrix tempor = right_obj;
		Matrix inverse_matrix(0, right_obj.columns, right_obj.columns);
		for (int i = 0; i < right_obj.columns; i++) {
			inverse_matrix.data[i][i] = 1;
		}
		for (int i = 0; i < right_obj.rows; i++) {
			double temp = right_obj.data[i][i];
			for (int j = 0; j < right_obj.columns; j++) {
				right_obj.data[i][j] /= temp;
				inverse_matrix.data[i][j] /= temp;
			}
			for (int ii = i + 1; ii < right_obj.columns; ii++) {
				double temp2 = right_obj.data[ii][i];
				for (int jj = 0; jj < right_obj.columns; jj++) {
					right_obj.data[ii][jj] -= (right_obj.data[i][jj] * temp2);
					inverse_matrix.data[ii][jj] -= (inverse_matrix.data[i][jj] * temp2);
				}
			}
		}
		for (int i = right_obj.rows - 1; i > 0; i--) {
			for (int ii = i - 1; ii >= 0; ii--) {
				double temp2 = right_obj.data[ii][i];
				for (int jj = right_obj.columns - 1; jj >= 0; jj--) {
					right_obj.data[ii][jj] -= (right_obj.data[i][jj] * temp2);
					inverse_matrix.data[ii][jj] -= (inverse_matrix.data[i][jj] * temp2);
				}
			}
		}
		Matrix result = *this * inverse_matrix;
		return result;
	}
	else {
		std::cout << "divisor matrix is not square!";
		Matrix null_obj;
		return null_obj;
	}
}


//'/'operator (num)
const Matrix Matrix::operator/(double divisor_number) const {
	Matrix obj_to_return(0, rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (divisor_number != 0) {
				obj_to_return.data[i][j] = data[i][j] / divisor_number;
			}
			else {
				obj_to_return.data[i][j] = 0;
			}
		}
	}
	return obj_to_return;
}

//'/'operator (string)
const Matrix Matrix::operator/(const char* str) const {
	Matrix obj_to_return;
	Matrix str_obj(str);
	obj_to_return = *this / str_obj;
	return obj_to_return;
}

//+=operator (obj)
Matrix& Matrix::operator+=(Matrix& right_obj) {
	if (rows == right_obj.rows && columns == right_obj.columns) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				data[i][j] += right_obj.data[i][j];
			}
		}
		return *this;
	}
	else {
		int overflow_rows;
		int overflow_columns;
		if (rows > right_obj.rows) {
			overflow_rows = rows;
		}
		else {
			overflow_rows = right_obj.rows;
		}
		if (columns > right_obj.columns) {
			overflow_columns = columns;
		}
		else {
			overflow_columns = right_obj.columns;
		}

		Matrix overflowobj(0, overflow_rows, overflow_columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				overflowobj.data[i][j] += data[i][j];
			}
		}
		for (int i = 0; i < right_obj.rows; i++) {
			for (int j = 0; j < right_obj.columns; j++) {
				overflowobj.data[i][j] += right_obj.data[i][j];
				
			}
		}
		*this = overflowobj;
		return *this;
	}
}

//+=operator (num)
Matrix& Matrix::operator+=(double inc_num) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			data[i][j] += inc_num;
		}
	}
	return *this;
}

//-=operator (obj)
Matrix& Matrix::operator-=(Matrix& right_obj) {
	if (rows == right_obj.rows && columns == right_obj.columns) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				data[i][j] -= right_obj.data[i][j];
			}
		}
		return *this;
	}
	else {
		int overflow_rows;
		int overflow_columns;
		if (rows > right_obj.rows) {
			overflow_rows = rows;
		}
		else {
			overflow_rows = right_obj.rows;
		}
		if (columns > right_obj.columns) {
			overflow_columns = columns;
		}
		else {
			overflow_columns = right_obj.columns;
		}

		Matrix overflowobj(0, overflow_rows, overflow_columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				overflowobj.data[i][j] += data[i][j];
			}
		}
		for (int i = 0; i < right_obj.rows; i++) {
			for (int j = 0; j < right_obj.columns; j++) {
				overflowobj.data[i][j] -= right_obj.data[i][j];
				
			}
		}
		*this = overflowobj;
		return *this;
	}
}

//-=operator (num)
Matrix& Matrix::operator-=(double decr_num) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			data[i][j] -= decr_num;
		}
	}
	return *this;
}

//*=operator (obj)
Matrix Matrix::operator*=(Matrix& right_obj) {
	if (rows == right_obj.rows && columns == right_obj.columns) {
		Matrix obj_to_return(0, rows, columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				for (int m = 0; m < rows; m++) {
					obj_to_return.data[i][j] += data[i][m] * right_obj.data[m][j];
				}
			}
		}
		*this = obj_to_return;
		return *this;
	}
	else if (columns == right_obj.rows) {
		Matrix obj_to_return(0, rows, right_obj.columns);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < right_obj.columns; j++) {
				for (int m = 0; m < right_obj.rows; m++) {
					obj_to_return.data[i][j] += data[i][m] * right_obj.data[m][j];
				}
			}
		}
		*this = obj_to_return;
		return *this;
	}
	else {
		std::cout << "\nmatrices are not consistent!\n";
		Matrix nullobj(0, 0, 0);
		return nullobj;
	}
}

//*=operator (num)
Matrix Matrix::operator*=(double mult_num) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			data[i][j] *= mult_num;
		}
	}
	return *this;
}

//'/'=operator (obj)
Matrix Matrix::operator/=(Matrix right_obj) {
	if (right_obj.columns == right_obj.rows) {
		Matrix tempor = right_obj;
		Matrix inverse_matrix(0, right_obj.columns, right_obj.columns);
		for (int i = 0; i < right_obj.columns; i++) {
			inverse_matrix.data[i][i] = 1;
		}
		for (int i = 0; i < right_obj.rows; i++) {
			double temp = right_obj.data[i][i];
			for (int j = 0; j < right_obj.columns; j++) {
				right_obj.data[i][j] /= temp;
				inverse_matrix.data[i][j] /= temp;
			}
			for (int ii = i + 1; ii < right_obj.columns; ii++) {
				double temp2 = right_obj.data[ii][i];
				for (int jj = 0; jj < right_obj.columns; jj++) {
					right_obj.data[ii][jj] -= (right_obj.data[i][jj] * temp2);
					inverse_matrix.data[ii][jj] -= (inverse_matrix.data[i][jj] * temp2);
				}
			}
		}
		for (int i = right_obj.rows - 1; i > 0; i--) {
			for (int ii = i - 1; ii >= 0; ii--) {
				double temp2 = right_obj.data[ii][i];
				for (int jj = right_obj.columns - 1; jj >= 0; jj--) {
					right_obj.data[ii][jj] -= (right_obj.data[i][jj] * temp2);
					inverse_matrix.data[ii][jj] -= (inverse_matrix.data[i][jj] * temp2);
				}
			}
		}
		*this = (*this * inverse_matrix);
		return *this;
	}
	else {
		std::cout << "divisor matrix is not square!";
		Matrix null_obj;
		return null_obj;
	}
}

//'/'=operator (num)
Matrix Matrix::operator/=(double divisor_number) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (divisor_number != 0) {
				data[i][j] /= divisor_number;
			}
			else {
				data[i][j] = 0;
			}
		}
	}
	return *this;
}

//>operator
bool Matrix::operator>(const Matrix& right_obj) {
	double summ_left{};
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			summ_left += data[i][j];
		}
	}
	double summ_right{};
	for (int i = 0; i < right_obj.rows; i++) {
		for (int j = 0; j < right_obj.columns; j++) {
			summ_right += right_obj.data[i][j];
		}
	}
	return summ_left > summ_right;
}

//<operator
bool Matrix::operator<(const Matrix& right_obj) {
	double summ_left{};
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			summ_left += data[i][j];
		}
	}
	double summ_right{};
	for (int i = 0; i < right_obj.rows; i++) {
		for (int j = 0; j < right_obj.columns; j++) {
			summ_right += right_obj.data[i][j];
		}
	}
	return summ_left < summ_right;
}

//>=operator
bool Matrix::operator>=(const Matrix& right_obj) {
	double summ_left{};
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			summ_left += data[i][j];
		}
	}
	double summ_right{};
	for (int i = 0; i < right_obj.rows; i++) {
		for (int j = 0; j < right_obj.columns; j++) {
			summ_right += right_obj.data[i][j];
		}
	}
	return summ_left >= summ_right;
}

//<=operator
bool Matrix::operator<=(const Matrix& right_obj) {
	double summ_left{};
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			summ_left += data[i][j];
		}
	}
	double summ_right{};
	for (int i = 0; i < right_obj.rows; i++) {
		for (int j = 0; j < right_obj.columns; j++) {
			summ_right += right_obj.data[i][j];
		}
	}
	return summ_left <= summ_right;
}

//==operator
bool Matrix::operator==(const Matrix& right_obj) {
	double summ_left{};
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			summ_left += data[i][j];
		}
	}
	double summ_right{};
	for (int i = 0; i < right_obj.rows; i++) {
		for (int j = 0; j < right_obj.columns; j++) {
			summ_right += right_obj.data[i][j];
		}
	}
	return summ_left == summ_right;
}

//!=operator
bool Matrix::operator!=(const Matrix& right_obj) {
	double summ_left{};
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			summ_left += data[i][j];
		}
	}
	double summ_right{};
	for (int i = 0; i < right_obj.rows; i++) {
		for (int j = 0; j < right_obj.columns; j++) {
			summ_right += right_obj.data[i][j];
		}
	}
	return summ_left != summ_right;
}

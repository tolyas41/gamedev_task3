#include "Matrix.h"
#include <iostream>
#include <vector>

Matrix::Matrix()
	: rows(0), columns(0), data(nullptr) {
}

//2. Contain a type conversion constructor that converts the 
//directly specified numerical constant with a sign into a class object.

Matrix::Matrix(int num, int in_columns, int in_rows) 
	: columns(in_columns), rows(in_rows) {
		data = new double* [columns];					
		for (int i = 0; i < columns; i++) {
			data[i] = new double[rows];
		}
		
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				data[i][j] = num;
			}
		}		
}

//3. Contain a type conversion constructor that converts a directly specified 
//2-dimensional array with numbers into a class object.

Matrix::Matrix(const int* array, int in_columns, int in_rows)
	: columns(in_columns), rows(in_rows) {
		data = new double* [columns];		  
		for (int i = 0; i < columns; i++) {
			data[i] = new double[rows];
		}
			
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				data[i][j] = array[i * rows + j];
			}	
		}
}

//destructor
Matrix::~Matrix() {
	for (int i = 0; i < columns; i++) {
		delete[] data[i];
	}
	delete[] data;
}

//deep copy constructor
Matrix::Matrix(const Matrix& source) 
	: columns(source.columns), rows(source.rows) {
		data = new double* [columns];
		for (int i = 0; i < columns; i++) {
			data[i] = new double[rows];
		}
		
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				data[i][j] = source.data[i][j];
			}
		}	
}

//move constructor
Matrix::Matrix(Matrix&& source) 
	: columns(source.columns), rows(source.rows), data(source.data) {
		source.columns = 0;
		source.rows = 0;
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
		int str_rows = 1;
		int prev_str_rows = 1;
		bool first_semicolon_pass = false;
		for (int i = 1; i <= str_numbers_length - 1; i++) {
			if (char_array[i] == ',') {
				str_rows++;
				if (char_array[i + 1] < '0' || char_array[i + 1] > '9') {
					valid_str_numbers = false;
				}
			}
			if ((char_array[i] == ';' || char_array[i] == ']') && first_semicolon_pass) {
				if (prev_str_rows != str_rows) {
					valid_str_numbers = false;
				}
			}
			if (char_array[i] == ';') {
				first_semicolon_pass = true;
				prev_str_rows = str_rows;
				str_rows = 1;
			}
		}

		if (valid_str_numbers) {
			std::vector < std::vector<int> > temp_vec(str_cols, std::vector<int>(str_rows, 0));
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
				columns = str_cols;
				rows = str_rows;
				data = new double* [columns];
				for (int i = 0; i < columns; i++) {
					data[i] = new double[rows];
				}
				int k = 0;
				for (int i = 0; i < columns; i++) {
					for (int j = 0; j < rows; j++) {
						data[i][j] = temp_vec[i][j];
					}
				}
			}
		}
	}
	if (valid_str_numbers == false) {
		columns = 0;
		rows = 0;
		data = nullptr;
		std::cout << "\n==INVALID STRING==\n";
	}
}

//copy assignment operator
Matrix& Matrix::operator=(const Matrix& source) {
	if (this != &source) {
		for (int i = 0; i < columns; i++) {
			delete[] data[i];
		}
		delete[] data;
		columns = source.columns;
		rows = source.rows;
		data = new double* [columns];
		for (int i = 0; i < columns; i++) {
			data[i] = new double[rows];
		}
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				data[i][j] = source.data[i][j];
			}		
		}	
	}
	return *this;
}

//move operator
Matrix& Matrix::operator=(Matrix&& source) noexcept {
	if (this != &source) {
		for (int i = 0; i < columns; i++) {
			delete[] data[i];
		}
		delete[] data;
		columns = source.columns;
		rows = source.rows;
		data = source.data;

		source.columns = 0;
		source.rows = 0;
		source.data = nullptr;
	}
	return *this;
}

//print every element of the object's array
void Matrix::print_array() {
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			std::cout << data[i][j];
			if (j != rows - 1) {
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
	for (int i = 0; i < source.columns; i++) {
		if (i != 0) {
			temp += "; ";
		}
		for (int j = 0; j < source.rows; j++) {
			temp += std::to_string(data[i][j]);
			if (j != source.rows - 1) {
				temp += ",";
			}
		}
	}
	temp += "]";
	return temp;
}

//+operator (obj)
const Matrix Matrix::operator+(Matrix& right_obj) const {
	if (columns == right_obj.columns && rows == right_obj.rows) {
		Matrix obj_to_return (0, columns, rows);
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				obj_to_return.data[i][j] = data[i][j] + right_obj.data[i][j];
			}
		}
		return obj_to_return;
	}
	else {
		int overflow_columns;
		int overflow_rows;
		if (columns > right_obj.columns) {
			overflow_columns = columns;
		}
		else {
			overflow_columns = right_obj.columns;
		}
		if (rows > right_obj.rows) {
			overflow_rows = rows;
		}
		else {
			overflow_rows = right_obj.rows;
		}

		Matrix overflowobj(0, overflow_columns, overflow_rows);
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				overflowobj.data[i][j] += data [i][j];
			}
		}
		for (int i = 0; i < right_obj.columns; i++) {
			for (int j = 0; j < right_obj.rows; j++) {
				overflowobj.data[i][j] += right_obj.data [i][j];
			}
		}
		return overflowobj;
	}
}

//+operator (num)
const Matrix Matrix::operator+(double inc_num) const {
	Matrix obj_to_return(0, columns, rows);
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
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
	if (columns == right_obj.columns && rows == right_obj.rows) {
		Matrix obj_to_return (0, columns, rows);
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				obj_to_return.data[i][j] = data[i][j] - right_obj.data[i][j];
			}
		}
		return obj_to_return;
	}
	else {
		int overflow_columns;
		int overflow_rows;
		if (columns > right_obj.columns) {
			overflow_columns = columns;
		}
		else {
			overflow_columns = right_obj.columns;
		}
		if (rows > right_obj.rows) {
			overflow_rows = rows;
		}
		else {
			overflow_rows = right_obj.rows;
		}

		Matrix overflowobj(0, overflow_columns, overflow_rows);
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				overflowobj.data[i][j] += data [i][j];
			}
		}
		for (int i = 0; i < right_obj.columns; i++) {
			for (int j = 0; j < right_obj.rows; j++) {
				overflowobj.data[i][j] -= right_obj.data [i][j];
			}
		}
		return overflowobj;
	}
}

//-operator (num)
const Matrix Matrix::operator-(double decr_num) const {
	Matrix obj_to_return(0, columns, rows);
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
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
	if (columns == right_obj.columns && rows == right_obj.rows) {
		Matrix obj_to_return(0, columns, rows);
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				obj_to_return.data[i][j] = data[i][j] * right_obj.data[i][j];
			}
		}
		return obj_to_return;
	}
	else {
		int overflow_columns;
		int overflow_rows;
		if (columns > right_obj.columns) {
			overflow_columns = columns;
		}
		else {
			overflow_columns = right_obj.columns;
		}
		if (rows > right_obj.rows) {
			overflow_rows = rows;
		}
		else {
			overflow_rows = right_obj.rows;
		}

		Matrix overflowobj(0, overflow_columns, overflow_rows);
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				overflowobj.data[i][j] += data[i][j];
			}
		}
		for (int i = 0; i < right_obj.columns; i++) {
			for (int j = 0; j < right_obj.rows; j++) {
				overflowobj.data[i][j] *= right_obj.data[i][j];
			}
		}
		return overflowobj;
	}
}

//*operator (num)
const Matrix Matrix::operator*(double mult_num) const {
	Matrix obj_to_return(0, columns, rows);
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
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
const Matrix Matrix::operator/(Matrix& right_obj) const {
	if (columns == right_obj.columns && rows == right_obj.rows) {
		Matrix obj_to_return(0, columns, rows);
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				if (right_obj.data[i][j] != 0) {
					obj_to_return.data[i][j] = data[i][j] / right_obj.data[i][j];
				}
				else {
					obj_to_return.data[i][j] = 0;
				}
			}
		}
		return obj_to_return;
	}
	else {
		int overflow_columns;
		int overflow_rows;
		if (columns > right_obj.columns) {
			overflow_columns = columns;
		}
		else {
			overflow_columns = right_obj.columns;
		}
		if (rows > right_obj.rows) {
			overflow_rows = rows;
		}
		else {
			overflow_rows = right_obj.rows;
		}

		Matrix overflowobj(0, overflow_columns, overflow_rows);
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				overflowobj.data[i][j] += data[i][j];
			}
		}
		for (int i = 0; i < right_obj.columns; i++) {
			for (int j = 0; j < right_obj.rows; j++) {
				if (right_obj.data[i][j] != 0) {
					overflowobj.data[i][j] /= right_obj.data[i][j];
				}
				else {
					overflowobj.data[i][j] = 0;
				}
			}
		}
		return overflowobj;
	}
}

//'/'operator (num)
const Matrix Matrix::operator/(double divisor_number) const {
	Matrix obj_to_return(0, columns, rows);
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
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
	if (columns == right_obj.columns && rows == right_obj.rows) {
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				data[i][j] += right_obj.data[i][j];
			}
		}
		return *this;
	}
	else {
		int overflow_columns;
		int overflow_rows;
		if (columns > right_obj.columns) {
			overflow_columns = columns;
		}
		else {
			overflow_columns = right_obj.columns;
		}
		if (rows > right_obj.rows) {
			overflow_rows = rows;
		}
		else {
			overflow_rows = right_obj.rows;
		}

		Matrix overflowobj(0, overflow_columns, overflow_rows);
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				overflowobj.data[i][j] += data[i][j];
			}
		}
		for (int i = 0; i < right_obj.columns; i++) {
			for (int j = 0; j < right_obj.rows; j++) {
				overflowobj.data[i][j] += right_obj.data[i][j];
				
			}
		}
		*this = overflowobj;
		return *this;
	}
}

//+=operator (num)
Matrix& Matrix::operator+=(double inc_num) {
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			data[i][j] += inc_num;
		}
	}
	return *this;
}

//-=operator (obj)
Matrix& Matrix::operator-=(Matrix& right_obj) {
	if (columns == right_obj.columns && rows == right_obj.rows) {
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				data[i][j] -= right_obj.data[i][j];
			}
		}
		return *this;
	}
	else {
		int overflow_columns;
		int overflow_rows;
		if (columns > right_obj.columns) {
			overflow_columns = columns;
		}
		else {
			overflow_columns = right_obj.columns;
		}
		if (rows > right_obj.rows) {
			overflow_rows = rows;
		}
		else {
			overflow_rows = right_obj.rows;
		}

		Matrix overflowobj(0, overflow_columns, overflow_rows);
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				overflowobj.data[i][j] += data[i][j];
			}
		}
		for (int i = 0; i < right_obj.columns; i++) {
			for (int j = 0; j < right_obj.rows; j++) {
				overflowobj.data[i][j] -= right_obj.data[i][j];
				
			}
		}
		*this = overflowobj;
		return *this;
	}
}

//-=operator (num)
Matrix& Matrix::operator-=(double decr_num) {
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			data[i][j] -= decr_num;
		}
	}
	return *this;
}

//*=operator (obj)
Matrix Matrix::operator*=(Matrix& right_obj) {
	if (columns == right_obj.columns && rows == right_obj.rows) {
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				data[i][j] *= right_obj.data[i][j];
			}
		}
		return *this;
	}
	else {
		int overflow_columns;
		int overflow_rows;
		if (columns > right_obj.columns) {
			overflow_columns = columns;
		}
		else {
			overflow_columns = right_obj.columns;
		}
		if (rows > right_obj.rows) {
			overflow_rows = rows;
		}
		else {
			overflow_rows = right_obj.rows;
		}

		Matrix overflowobj(0, overflow_columns, overflow_rows);
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				overflowobj.data[i][j] += data[i][j];
			}
		}
		for (int i = 0; i < right_obj.columns; i++) {
			for (int j = 0; j < right_obj.rows; j++) {
				overflowobj.data[i][j] *= right_obj.data[i][j];

			}
		}
		*this = overflowobj;
		return *this;
	}
}

//*=operator (num)
Matrix Matrix::operator*=(double mult_num) {
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			data[i][j] *= mult_num;
		}
	}
	return *this;
}

//'/'=operator (obj)
Matrix Matrix::operator/=(Matrix& right_obj) {
	if (columns == right_obj.columns && rows == right_obj.rows) {
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				if (right_obj.data[i][j] != 0) {
					data[i][j] /= right_obj.data[i][j];
				}
				else {
					data[i][j] = 0;
				}
			}
		}
		return *this;
	}
	else {
		int overflow_columns;
		int overflow_rows;
		if (columns > right_obj.columns) {
			overflow_columns = columns;
		}
		else {
			overflow_columns = right_obj.columns;
		}
		if (rows > right_obj.rows) {
			overflow_rows = rows;
		}
		else {
			overflow_rows = right_obj.rows;
		}

		Matrix overflowobj(0, overflow_columns, overflow_rows);
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				overflowobj.data[i][j] += data[i][j];
			}
		}
		for (int i = 0; i < right_obj.columns; i++) {
			for (int j = 0; j < right_obj.rows; j++) {
				if (right_obj.data[i][j] != 0) {
					overflowobj.data[i][j] /= right_obj.data[i][j];
				}
				else {
					overflowobj.data[i][j] = 0;
				}
			}
		}
		*this = overflowobj;
		return *this;
	}
}

//'/'=operator (num)
Matrix Matrix::operator/=(double divisor_number) {
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
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
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			summ_left += data[i][j];
		}
	}
	double summ_right{};
	for (int i = 0; i < right_obj.columns; i++) {
		for (int j = 0; j < right_obj.rows; j++) {
			summ_right += right_obj.data[i][j];
		}
	}
	return summ_left > summ_right;
}

//<operator
bool Matrix::operator<(const Matrix& right_obj) {
	double summ_left{};
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			summ_left += data[i][j];
		}
	}
	double summ_right{};
	for (int i = 0; i < right_obj.columns; i++) {
		for (int j = 0; j < right_obj.rows; j++) {
			summ_right += right_obj.data[i][j];
		}
	}
	return summ_left < summ_right;
}

//>=operator
bool Matrix::operator>=(const Matrix& right_obj) {
	double summ_left{};
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			summ_left += data[i][j];
		}
	}
	double summ_right{};
	for (int i = 0; i < right_obj.columns; i++) {
		for (int j = 0; j < right_obj.rows; j++) {
			summ_right += right_obj.data[i][j];
		}
	}
	return summ_left >= summ_right;
}

//<=operator
bool Matrix::operator<=(const Matrix& right_obj) {
	double summ_left{};
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			summ_left += data[i][j];
		}
	}
	double summ_right{};
	for (int i = 0; i < right_obj.columns; i++) {
		for (int j = 0; j < right_obj.rows; j++) {
			summ_right += right_obj.data[i][j];
		}
	}
	return summ_left <= summ_right;
}

//==operator
bool Matrix::operator==(const Matrix& right_obj) {
	double summ_left{};
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			summ_left += data[i][j];
		}
	}
	double summ_right{};
	for (int i = 0; i < right_obj.columns; i++) {
		for (int j = 0; j < right_obj.rows; j++) {
			summ_right += right_obj.data[i][j];
		}
	}
	return summ_left == summ_right;
}

//!=operator
bool Matrix::operator!=(const Matrix& right_obj) {
	double summ_left{};
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			summ_left += data[i][j];
		}
	}
	double summ_right{};
	for (int i = 0; i < right_obj.columns; i++) {
		for (int j = 0; j < right_obj.rows; j++) {
			summ_right += right_obj.data[i][j];
		}
	}
	return summ_left != summ_right;
}

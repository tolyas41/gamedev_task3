#include "Matrix.h"
#include <vector>
#include <iostream>


int main() {

//2. Contain a type conversion constructor that converts the 
//directly specified numerical constant with a sign into a class object.

	Matrix* num_const_obj = new Matrix(5, 9, 3);
	std::cout << "2. num object : \n\n";						
	num_const_obj->print_array();

//4. Implement the correct work with objects of the developed class when copying, moving and initializing.

	std::cout << "\n\ncopy constructor : \n\n";
	Matrix copied_obj(*num_const_obj);
	delete num_const_obj;
	copied_obj.print_array();
		
	std::cout << "\nmove constructor : \n\n";
	Matrix move_ctr_obj(Matrix(1, 2, 2));
	move_ctr_obj.print_array();

	std::cout << "\n\ncopy assignment operator : \n\n";
	Matrix copy_assign_obj;								   
	Matrix random_object(123, 3, 3);						 
	copy_assign_obj = random_object;
	copy_assign_obj.print_array();

	std::cout << "\n\nmove assignment operator : \n\n";
	Matrix move_assign_obj;
	move_assign_obj = Matrix(2, 3, 3);
	move_assign_obj.print_array();

//5. Contain the function of converting the internal structure of the object to a string, 
// so that later you can intuitively show the result on the screen. String format: 
// [a,b; c,d; …], where a, b, c, d, … – numbers.

	Matrix object_tobeconvert(303, 3, 3);
	std::string string_array = object_tobeconvert.to_string(object_tobeconvert);
	std::cout << "\nobject was converted to a string : " << std::endl;
	std::cout << string_array << std::endl;

//6. Contain a type conversion constructor that converts the directly specified 
//character type string (char *), which is a string representation of a mathematical 
//object, into a class object. The conversion process must verify that the input is correct.
//String format :
//[a,b; c,d; …]

	char str_numbers[] = "[101,202,303; 404,505,606; 9,8,7]";
	std::cout << "\nchar array convert to object`s array : \n\n";
	Matrix* string_to_math = new Matrix(str_numbers);
	string_to_math->print_array();
	delete string_to_math;

//3. Contain a type conversion constructor that converts a directly specified 
//2-dimensional array with numbers into a class object.

	std::cout << "\ndirectly specified 2d array was converted to object`s array : \n\n";
	int spec_array[4][3] = { {1,2,3},{4,5,6},{7,8,9},{10,11,12} };

	Matrix obj_from_spec_array(*spec_array, 4, 3);				   
	obj_from_spec_array.print_array();


//checking operators...

//+operator (obj)
	{
		std::cout << "\n\n+operator (obj) check : \n";
		Matrix summ_obj;
		Matrix a_obj(55, 2, 2);
		Matrix b_obj(11, 3, 3);
		Matrix c_obj(4, 4, 4);
		summ_obj = a_obj + b_obj + c_obj;

		std::cout << "\na_obj : \n";
		a_obj.print_array();

		std::cout << "\nb_obj : \n";
		b_obj.print_array();

		std::cout << "\nc_obj : \n";
		c_obj.print_array();

		std::cout << "\nsumm_obj (a + b + c): \n";
		summ_obj.print_array();
	}

//+operator (num)
	{
		std::cout << "\n\n+operator (num) check : \n";
		Matrix summ_obj;
		Matrix a_obj(55, 2, 2);
		summ_obj = a_obj + 3;

		std::cout << "\na_obj : \n";
		a_obj.print_array();

		std::cout << "\nsumm_obj (a + 3): \n";
		summ_obj.print_array();
	}

//-operator (obj)
	{
		std::cout << "\n\n-operator (obj) check : \n";
		Matrix subtr_obj;
		Matrix a_obj(55, 4, 4);
		Matrix b_obj(11, 3, 3);
		Matrix c_obj(4, 4, 4);
		subtr_obj = a_obj - b_obj - c_obj;

		std::cout << "\na_obj : \n";
		a_obj.print_array();

		std::cout << "\nb_obj : \n";
		b_obj.print_array();

		std::cout << "\nc_obj : \n";
		c_obj.print_array();

		std::cout << "\nsubtr_obj (a - b - c): \n";
		subtr_obj.print_array();
	}

//-operator (num)
	{
		std::cout << "\n\n-operator (num) check : \n";
		Matrix subtr_obj;
		Matrix a_obj(55, 4, 4);
		subtr_obj = a_obj - 4;

		std::cout << "\na_obj : \n";
		a_obj.print_array();

		std::cout << "\nsubtr_obj (a - 4): \n";
		subtr_obj.print_array();
	}

//*operator with object
	{
		std::cout << "\n\n*operator check (obj): \n";
		Matrix mult_obj;
		Matrix a_obj(2, 3, 3);
		Matrix b_obj(3, 3, 3);
		Matrix c_obj(4, 4, 5);
		mult_obj = a_obj * b_obj;

		std::cout << "\na_obj : \n";
		a_obj.print_array();

		std::cout << "\nb_obj : \n";
		b_obj.print_array();

		std::cout << "\nc_obj : \n";
		c_obj.print_array();

		std::cout << "\nmult_obj (a * b * c): \n";
		mult_obj.print_array();

	}

//*operator with num const
	{
		std::cout << "\n\n*operator check (num): \n";
		Matrix mult_num;
		Matrix a_obj(1, 3, 3);
		mult_num = a_obj * 2 * 3;

		std::cout << "\na_obj : \n";
		a_obj.print_array();

		std::cout << "\nmult_num (a * 2 * 3): \n";
		mult_num.print_array();

	}

//'/'operator with obj
	{
		std::cout << "\n\n/operator check (obj): \n";
		Matrix div_obj;
		Matrix a_obj(23, 3, 3);
		Matrix b_obj(2, 4, 3);
		Matrix c_obj(0, 1, 3);
		div_obj = a_obj / b_obj / c_obj;

		std::cout << "\na_obj : \n";
		a_obj.print_array();

		std::cout << "\nb_obj : \n";
		b_obj.print_array();

		std::cout << "\nc_obj : \n";
		c_obj.print_array();

		std::cout << "\ndiv_obj (a / b / c): \n";
		div_obj.print_array();

	}
//'/'operator with num
	{
		std::cout << "\n\n/operator check (num): \n";
		Matrix div_num;
		Matrix a_obj(66, 3, 3);
		div_num = a_obj / 2 / 3;

		std::cout << "\na_obj : \n";
		a_obj.print_array();

		std::cout << "\ndiv_num (a / 2 / 3) : \n";
		div_num.print_array();

	}

//+=operator
	{
		std::cout << "\n\n+=operator check : \n";
		Matrix a_obj(55, 3, 3);
		Matrix b_obj(12, 4, 3);
		Matrix c_obj(4, 3, 4);
		a_obj += b_obj += c_obj += c_obj;

		std::cout << "\na_obj : \n";
		a_obj.print_array();

		std::cout << "\nb_obj : \n";
		b_obj.print_array();

		std::cout << "\nc_obj : \n";
		c_obj.print_array();

	}
//-=operator
	{
		std::cout << "\n\n-=operator check : \n";
		Matrix a_obj(55, 3, 3);
		Matrix b_obj(12, 4, 3);
		Matrix c_obj(4, 3, 4);
		a_obj -= b_obj -= c_obj;

		std::cout << "\na_obj : \n";
		a_obj.print_array();

		std::cout << "\nb_obj : \n";
		b_obj.print_array();

		std::cout << "\nc_obj : \n";
		c_obj.print_array();

	}

//*=operator with object
	{
		std::cout << "\n\n*=operator check (obj): \n";
		Matrix a_obj(2, 3, 3);
		Matrix b_obj(3, 3, 3);
		Matrix c_obj(4, 4, 5);
		a_obj *= b_obj;
		b_obj *= c_obj;

		std::cout << "\na_obj : \n";
		a_obj.print_array();

		std::cout << "\nb_obj : \n";
		b_obj.print_array();

		std::cout << "\nc_obj : \n";
		c_obj.print_array();

	}

//*=operator with num const
	{
		std::cout << "\n\n*=operator check (num): \n";
		Matrix a_obj(1, 3, 3);
		a_obj *= 3;

		std::cout << "\na_obj : \n";
		a_obj.print_array();

	}

//'/'=operator with object
	{
		std::cout << "\n\n/=operator check (obj): \n";
		Matrix a_obj(2, 3, 3);
		Matrix b_obj(3, 3, 3);
		Matrix c_obj(4, 4, 5);
		a_obj /= b_obj;
		b_obj /= c_obj;

		std::cout << "\na_obj : \n";
		a_obj.print_array();

		std::cout << "\nb_obj : \n";
		b_obj.print_array();

		std::cout << "\nc_obj : \n";
		c_obj.print_array();

	}

//'/'=operator with num const
	{
		std::cout << "\n\n/=operator check (num): \n";
		Matrix a_obj(1, 3, 3);
		a_obj /= 3;

		std::cout << "\na_obj : (1 / 3)\n";
		a_obj.print_array();

	}

//+operator (string)
	{
		std::cout << "\n\n+operator (string): \n";
		Matrix a_obj;
		Matrix b_obj(3, 3, 3);
		a_obj = b_obj + "[123,123; 33,33]";

		std::cout << "\na_obj : \n";
		a_obj.print_array();

		std::cout << "\nb_obj : \n";
		b_obj.print_array();

	}

//*operator (string)
	{
		std::cout << "\n\n*operator (string): \n";
		Matrix a_obj;
		Matrix b_obj(3, 3, 3);
		a_obj = b_obj * "[123,123; 33,33]";

		std::cout << "\na_obj : \n";
		a_obj.print_array();

		std::cout << "\nb_obj : \n";
		b_obj.print_array();

	}

//'/'*operator (string)
	{
		std::cout << "\n\n/operator (string): \n";
		Matrix a_obj;
		Matrix b_obj(3, 3, 3);
		a_obj = b_obj / "[3,2; 4,5]";

		std::cout << "\na_obj : \n";
		a_obj.print_array();

		std::cout << "\nb_obj : \n";
		b_obj.print_array();

	}

//>operator
	{
		std::cout << "\n\n>operator (string): \n";
		Matrix a_obj(3, 3, 3);
		Matrix b_obj(6, 3, 3);

		std::cout << (a_obj > b_obj) << "\n";
		a_obj.print_array();

		std::cout << "\nb_obj : \n";
		b_obj.print_array();

	}

//*operator with object
{
	std::cout << "\n\n*operator check (obj): \n";
	Matrix mult_obj;
	Matrix a_obj(2, 3, 2);
	Matrix b_obj(3, 4, 3);
	Matrix c_obj(4, 3, 3);
	mult_obj = a_obj * b_obj;

	std::cout << "\na_obj : \n";
	a_obj.print_array();

	std::cout << "\nb_obj : \n";
	b_obj.print_array();

	std::cout << "\nc_obj : \n";
	c_obj.print_array();

	std::cout << "\nmult_obj (a * b * c): \n";
	mult_obj.print_array();

}



	return 0;
}
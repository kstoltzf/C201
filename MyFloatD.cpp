//Kyle Stoltzfus
//C201 5:30 - 7:20
//Homework 6
//MyFloat2.cpp
/*             MyFloat
           ---------------
A C++ class definition that creates a data type MyFloat. This data type allows 
for the use and manipulation of small floats between 0 and 1, and provides 
accuracy to 20 digits in calculations. MyFloatD.cpp improves on the previous 
class definition in MyFloat2.cpp by changing this class to a dynamically 
implemented class. MyFloat objects are now dynamically created to the size
the user needs unless a size is not given. In this case, the default size 
of 10 digits is used.

Changes:

MyFloat() : Changed to allow dynamic memory allocation. Creates a MyFloat of default size 10

= : Overloaded assignment operator that allows the assignment of strings to a MyFloat. For
	example, "MyFloat X = 0.456;" is a legal declaration. Changed to allow use of dynamic
	memory allocation for MyFloat.

>> : Changed to allow dynamic memory allocation for MyFloat

+ : Changed to allow overloaded addition operator to handle dynamically created MyFloats

== : Changed to allow overloaded equality operator to handle dynamically created MyFloats

int MaxDigits() : Changed to allow dynamic memory allocation for MyFloat

> : Changed to allow overloaded greater than operator to handle dynamically created MyFloats

Additions:

=	: Overloaded "=" that allows the use of the assignment operator in the code 
      to assign the value of one MyFloat into another MyFloat

MyFloat(const MyFloat &S) : A copy constructor that copies the elements of one
							MyFloat into another MyFloat

MyFloat(unsigned MaximumLength) : A constructor that creates a MyFloat of any
								  length the user needs

~MyFloat() : class destructor that reallocates memory back to the operating system
*/

#include <iostream>
#include <ctype.h>
#include <string.h>
using namespace std;

class MyFloat
{
	private:
		enum {DEFAULT = 10};
		char * Number;  //Pointer to create dynamic char
		int NumberOfDigits; //Number of digits in Number array
		int Max_Digits;  //Maximum number of digits
						 //Set to 0 if memory allocation error
	public:
		int MaxDigits();    //Returns the maximum number of digits 
		                          //possible in a MyFloat
		int Digits();       //Returns the number of digits in a MyFloat
		~MyFloat();               //Class destructor
		MyFloat();                //Default constructor
		MyFloat(const MyFloat &MyFloat2); //Class copy constructor
		MyFloat(unsigned MaximumLength);  //Class constructor that allows
		//the creation of a MyFloat of any size
		MyFloat& operator+ (MyFloat &MyFloat2);  //Adds two MyFloats together 
		                                  //and returns the result as a MyFloat
		char operator== (MyFloat &MyFloat2);    //Compares two MyFloats to
		                                        //see if they are equal
		MyFloat& operator= (const char Source[]);      //Stores the value 
		   //on the right hand side of the assignment operator in a MyFloat
		MyFloat& operator= (const MyFloat &MyFloat2);  //Stores the value 
		   //on the right hand side of the assignment operator in a MyFloat
		char operator> (const MyFloat &Float1);       //Compares two MyFloats 
		                                 //to determine which one is bigger
		friend ostream& operator<< (ostream& Output, const MyFloat &Float1);  
		//Allows the use of the insertion operator
		friend istream& operator>> (istream& Input, MyFloat &Float1);         
		//Allows the use of the extraction operator
};

/***************~MyFloat()******************************************
This is the class destructor. This function is called automatically when an
instance of the MyFloat class goes out of scope. In particular, the destructor
is called to return dynamically allocated storage when a function is exited. 
Storage for the local variables and the parameters passed by value will be 
deallocated. This destructor prevents memory leaks from occurring. 
*******************************************************************/
MyFloat::~MyFloat()
{
	delete Number; //deallocate dynamic storage of Number
}

/******************** operator<< *********************************
Action: This function allow the use of the insertion operator in the code of any 
program implementing the MyFloat class. For example, it is now legal to have code 
like the following: cout << any MyFloat variable. This code will display the 
contents of the array Number[] on the screen. Also allows for cascading.
Parameters:
In: The MyFloat Float1 on the right hand side of the insertion operator which 
holds the data that is to be displayed on the screen. This data is passed in by 
constant reference. This allows the function to access the data but does not 
allow it to make changes to the data.
Out: The data that is to be displayed on the screen stored in the ostream 
variable Output.
This data is passed back by reference.
Returns: The data that is to be diplayed on the screen stored in the ostream
variable Output. This data is returned by reference. This allows for cascading.
*****************************************************************/
ostream& operator<< (ostream& Output, const MyFloat &Float1)
{
	if (Float1.NumberOfDigits == 0)  //There was an error in input
		Output << "0.?";

	else
	{
		Output << "0.";

		for (char i = 0; i < Float1.NumberOfDigits; ++i)
			Output << short int(Float1.Number[i]);   //Needs to be typecast as 
		                                            //an int or it will display
	}//the characters with the ASCII values 0 - 9 that are in the array Number[]
	
	return Output;  //needed to allow cascading
}

/******************** operator>> ***************************
Action: This function allows the use of the extraction operator in the code of any
program implementing the MyFloat class. For example, it is now legal to have code 
like the following: cin >> any MyFloat variable. This code will fill the data 
members Number[] and NumberOfDigits. The NumberOfDigits cannot exceed the Max_Digits of
the MyFloat passed into the function. It also allows cascading. In order to simplify 
any functions that use the data in Number[], the input is converted from a char to an 
int before it is stored in Number[] so that Number[] holds the actual int value wanted 
and not the ASCII value of that int as a char. This is done by subtracting the ASCII value 
of 0, which is 48. For example, the int 2 has an ASCII value of 50. By subtracting the
char 0 with an ASCII value of 48, a char with an ASCII value of 2 is created and 
stored in Number[].
Parameters:
In: The data entered by the user stored in the istream variable Input. This data is 
passed in by reference.
Out: The MyFloat Float1 which now contains the data entered by the user. This data 
is passed back by reference.
Returns: The data entered by the user and stored in the istream variable Input. 
This data is returned by reference. This allows for cascading.
************************************************************/
istream& operator>> (istream& Input, MyFloat &Float1)
{
	char Ch;
	Float1.NumberOfDigits = 0;

	Input.get(Ch);

	while (Ch == '0' || isspace(Ch))
		Input.get(Ch);

	if (Ch == '.')
	{
		Input.get(Ch);

		while (isdigit(Ch) && Float1.NumberOfDigits < Float1.Max_Digits)
		{
			Float1.Number[Float1.NumberOfDigits] = Ch - '0';
			++ Float1.NumberOfDigits;
			Input.get(Ch);
		}

		Float1.Max_Digits = Float1.NumberOfDigits;
	}

	else
		Float1.NumberOfDigits = 0; //error in input

	Input.putback(Ch);  //needed for test program to run correctly

	return Input;  //allows cascading
}

/*******************MaxDigits**************************************
Action: This function returns the maximum number of digits in a MyFloat.
Parameters: None
Returns: The variable Max_Digits that is filled when any constructor is called
******************************************************************/
int MyFloat::MaxDigits()
{
	return Max_Digits;
}

/************************Digits**********************************
Action: This function returns the number of digits in a MyFloat.
Parameters: None
Returns: The NumberOfDigits in a MyFloat as determined by the read function.
*****************************************************************/
int MyFloat::Digits()
{
	return NumberOfDigits;  //Typecasts the char variable NumberOfDigits
	                        //to an int for display in standard output
}

/*******************MyFloat (constructor) ***************************
Action: This function is the default constructor. Every time a MyFloat 
variable with no parameters is created,this constructor sets NumberOfDigits = 0,
sets Max_Digits = DEFAULT, dynamically creates an char array of DEFAULT size that 
Number points to, and fills the Number array with 0s.
Parameters: None
Returns: Nothing
********************************************************************/
MyFloat::MyFloat()
{
	NumberOfDigits = 0;
	Max_Digits = DEFAULT;

	Number = new(nothrow) char[Max_Digits + 1];

	if (Number == NULL)
		NumberOfDigits = 0; //memory allocation error

	else
	{
		for (char i = 0; i <= Max_Digits; ++i)  //Fills the entire array
			Number[i] = 0;                   //Number[] with zeroes
	}
}

/*******************MyFloat (constructor) ***************************
Action: This function is the constructor that allows for the creation of a MyFloat
of any size. Every time a MyFloat variable with a parameter that is an unsigned int 
is created,this constructor sets NumberOfDigits = 0,sets Max_Digits = the MaximumLength 
passed in as a parameter, dynamically creates an char array of MaximumLength size that Number 
points to, and fills the Number array with 0s.
Parameters:
In: The size of the Number array that is needed
Out: None
Returns: Nothing
********************************************************************/
MyFloat::MyFloat(unsigned MaximumLength)
{
	NumberOfDigits = 0;
	Max_Digits = MaximumLength;

	Number = new(nothrow) char[Max_Digits + 1];

	if (Number == NULL)
		NumberOfDigits = 0; //memory allocation error

	else
	{
		for (int i = 0; i <= Max_Digits; ++i)
			Number[i] = 0;
	}
}

/*******************MyFloat (copy constructor) ***************************
Action: This function is the copy constructor that allows for the creation of a MyFloat
with the exact same values as another MyFloat. Every time a MyFloat variable with a parameter
that is another MyFloat is created,this constructor sets NumberOfDigits = the NumberOfDigits in
the MyFloat being passed in, sets Max_Digits = the Max_Digits in the MyFloat being passed in, 
dynamically creates an char array of Max_Digits size that Number points to, and fills 
the Number array with with the elements of the Number array of the MyFloat being passed in.
Parameters:
In: The MyFloat to be copied into the new MyFloat being created. This is passed in by 
    constant reference
Out: None
Returns: Nothing
********************************************************************/
MyFloat::MyFloat(const MyFloat &MyFloat2)
{
	NumberOfDigits = MyFloat2.NumberOfDigits;
	Max_Digits = MyFloat2.Max_Digits;

	Number = new(nothrow) char[Max_Digits];

	if (Number == NULL)
		NumberOfDigits = 0; //memory allocation error

	else
	{
		for (int i = 0; i < Max_Digits; ++i)
			Number[i] = MyFloat2.Number[i];
	}
}

/****************************** operator+ ***************************
Action: This function adds two MyFloats together and stores the results in a third
MyFloat. It only stores the decimal part of the number. For example, in any addition where
the result is greater than 1, only the decimal will be stored. Any number on the left side of the 
decimal place will be ignored.
Parameters: The MyFloat on the right side of the + operator. It will be added to the MyFloat on 
the left side of the + operator.
Returns: The result of the addition stored in the MyFloat Result
*********************************************************************/
MyFloat& MyFloat::operator+ (MyFloat &MyFloat2)
{
	int i = 0, Long, Short;
	char CarryBit = 0, Sum;

	Long = Short = NumberOfDigits;

	if (Long < MyFloat2.NumberOfDigits)
		Long = MyFloat2.NumberOfDigits;  //Makes sure Long is equal 
	                                //to the NumberOfDigits of the longest array being added together.
	else
		Short = MyFloat2.NumberOfDigits;

	MyFloat Result(Long);
	Result.NumberOfDigits = Result.Max_Digits;
	Result.Number = new(nothrow) char[Long];

	if (Result.Number == NULL)
		Result.NumberOfDigits = 0;  //memory allocation error

	for (i = 0; i < Short; ++i);      //Tells the program how many elements 
	                                      //of the array to add together.
	for (int x = i; x < Long; ++x)
	{
		if (x < NumberOfDigits)
			Result.Number[x] = Number[x];
		else
			Result.Number[x] = MyFloat2.Number[x];
	}

	for (i; i >= 0; --i)
	{
		Sum = Number[i] + MyFloat2.Number[i] + CarryBit;

		if (Sum > 9)
		{
			CarryBit = Sum / 10;
			Result.Number[i] = Sum % 10;
		}

		else
		{
			Result.Number[i] = Sum;
			CarryBit = 0;
		}
	}
	* this = Result;
	return * this;
}

/************************ operator== ************************************
Action: This function compares two MyFloats to see if they are equal by comparing the elements
of the array Number[] in both of them.
Parameters: The MyFloat on the left side of the == operator. It will be compared to the 
MyFloat on the right side to see if they are equal.
Returns: O if the MyFloats are not equal. Returns 1 if they are equal.
************************************************************************/
char MyFloat::operator== (MyFloat &MyFloat2)
{
	int Long = NumberOfDigits, Short, i = 0;
	Short = Long;

	if (Long > MyFloat2.NumberOfDigits) 
		Long = MyFloat2.NumberOfDigits; //Makes sure Length is set to the length of the 
	                                       //smallest array being compared.
	else
		Short = MyFloat2.NumberOfDigits;

	for ( i; i < Short; ++i)      //Loop to checks up to the length 
	{	                          //of the shortest array being compared. 
		if (Number[i] != MyFloat2.Number[i])  //Loop stops as soon as it finds elements that do not match.
			return 0;
	}

	for ( i; i < Long; ++i) //checks rest of array Number to make sure MyFloats are equal
	{
		if (Long == NumberOfDigits)
		{
			if (Number[i] != 0) //Number contains any nonzero digit
				return 0;
		}

		else
		{
			if (MyFloat2.Number[i] != 0)  //Number contains any nonzero digit
				return 0;
		}	
	}
	return 1;
}

/****************** operator= (String assignment) ***********************
Action: This function allows for the use of the assignment operator with a string on the right
hand side. Stores the value in the null terminating character array on the right hand side 
into the array Number[] in the MyFloat data type. Also determines the number of elements
being stored in Number[], creates a MyFloat with a Number array of the correct size, and
places that value in NumberOfDigits and Max_Digits.This function uses the same process for 
storing data in Number[] as the overloaded extraction operator.
Parameters:
In: The array Source[] filled with the data from the null terminating character array Source[] 
on the right hand side of the assignment operator. This data is passed in by constant reference.
This allows the function to access the data in Source[] but does not allow it to make changes to 
the data.
Out: None
Returns: A MyFloat filled with the data from the array Source[]. This data is returned by dereferencing
the pointer this which points to the instance being referred to in the function definition. This allows
for cascading.
Precondition: Null terminating character array on right hand side of the assignment operator.
****************************************************/
MyFloat& MyFloat::operator= (const char Source[])
{
	int i = 0;
	NumberOfDigits = 0;

	if (strlen(Source) > Max_Digits)
	{
		Max_Digits = strlen(Source);
		delete [] Number;
		Number = new(nothrow) char[Max_Digits];

		if (Number == NULL)
		{
			NumberOfDigits = 0;
			return *this;
		}
	}
	
	while (Source[i] == '0' || isspace(Source[i]))
		++i;

	if (Source[i] == '.')
	{
		++i;

		for (;isdigit(Source[i]) && NumberOfDigits < Max_Digits; ++i, ++NumberOfDigits)
			Number[NumberOfDigits] = Source[i] - '0';  
	

		i = NumberOfDigits; //fills NumberOfDigits data member

		for (i; i < Max_Digits; ++i)  //fills the rest of the array Number[] with 0s
			Number[i] = 0;
	}

	return *this;  //allows for cascading
}

/****************** operator= (MyFloat assignment)***********************
Action: This function allows for the use of the assignment operator with a MyFloat on the right
hand side. It copies all the elements of the MyFloat on the right hand side into a new
MyFloat.
Parameters:
In: The MyFloat on the right hand side to be copied into a new MyFloat
Out: None
Returns: A MyFloat filled with the data from the MyFloat on the right hand side of the operator. 
This data is returned by dereferencing the pointer this which points to the instance 
being referred to in the function definition. This allows for cascading.
Precondition: Null terminating character array on right hand side of the assignment operator.
****************************************************/
MyFloat& MyFloat::operator= (const MyFloat &MyFloat2)
{
	NumberOfDigits = MyFloat2.NumberOfDigits;

	if (MyFloat2.Max_Digits > Max_Digits) //Make sure the array Number being 
		                                 //written to is big enough
	{
		Max_Digits = MyFloat2.Max_Digits;
		delete [] Number;
		Number = new(nothrow) char[Max_Digits];

		if (Number == NULL)
		{
			NumberOfDigits = 0;
			return *this;
		}
	}
	
	for (int i = 0; i < Max_Digits; ++i)
		Number[i] = MyFloat2.Number[i];  

	return *this;  //allows for cascading
}

/******************* operator> ***************************
Action: This function allows for the comparison of two MyFloats. It checks to see if 
the right hand MyFloat is greater than or less than the left hand one by comparing the 
elements in the array Number[]. If all the elements compared are equal, it then determines
which array is longer. This must be the greater one because, in the test driver, the comparator
operator function has already been called so the two arrays can't be equal.
Parameters:
In: The MyFloats on the right and left hand sides of the > operator. The left hand side is passed
in by reference.
Out: None
Returns: 1 if the left hand MyFloat is greater than the right hand one or O if it is less than.
**********************************************************/
char MyFloat::operator> (const MyFloat &Float2)
{
	char i = 0;

	while (i < NumberOfDigits && i < Float2.NumberOfDigits)
	{
		if (Number[i] > Float2.Number[i])
			return 1;
		else if (Number[i] < Float2.Number[i])
			return 0;
		else                                    
			++i;
	}

	if (NumberOfDigits > Float2.NumberOfDigits)
		return 1;

	return 0;
}

/*


----------------------------------------------------------------------

     1)  Test copy constructor          2)  Test assignment operator
     3)  Test >> input function         4)  Test + operator
     5)  Test == operator               6)  Test destructor
     Q)  Quit program

Choice? 1


============ Testing copy constructor  ================

NOTE: This function also calls default constructor and '='operator.


After 'X = 0.0',  Y = 0.12345
Note that Y should be 0.12345



----------------------------------------------------------------------

     1)  Test copy constructor          2)  Test assignment operator
     3)  Test >> input function         4)  Test + operator
     5)  Test == operator               6)  Test destructor
     Q)  Quit program

Choice? 2


------------  Testing '='  for MyFloats   --------------------


After the assignments, X = "0.1234567890", Y = X, and X = 0.0, Y = 0.1234567890



----------------------------------------------------------------------

     1)  Test copy constructor          2)  Test assignment operator
     3)  Test >> input function         4)  Test + operator
     5)  Test == operator               6)  Test destructor
     Q)  Quit program

Choice? 3


>>>>>>>>>>>>>  Testing input operator >>>>>>>>>>>>>>>>>

Enter MyFloat ==> 0.123

After the read,  X = '0.123'


------------------------------------------  Spacebar continues this test



----------------------------------------------------------------------

     1)  Test copy constructor          2)  Test assignment operator
     3)  Test >> input function         4)  Test + operator
     5)  Test == operator               6)  Test destructor
     Q)  Quit program

Choice? 3


>>>>>>>>>>>>>  Testing input operator >>>>>>>>>>>>>>>>>

Enter MyFloat ==> .123

After the read,  X = '0.123'


------------------------------------------  Spacebar continues this test



----------------------------------------------------------------------

     1)  Test copy constructor          2)  Test assignment operator
     3)  Test >> input function         4)  Test + operator
     5)  Test == operator               6)  Test destructor
     Q)  Quit program

Choice? 3


>>>>>>>>>>>>>  Testing input operator >>>>>>>>>>>>>>>>>

Enter MyFloat ==> 0.

After the read,  X = '0.?'


------------------------------------------  Spacebar continues this test



----------------------------------------------------------------------

     1)  Test copy constructor          2)  Test assignment operator
     3)  Test >> input function         4)  Test + operator
     5)  Test == operator               6)  Test destructor
     Q)  Quit program

Choice? 3


>>>>>>>>>>>>>  Testing input operator >>>>>>>>>>>>>>>>>

Enter MyFloat ==> .

After the read,  X = '0.?'


------------------------------------------  Spacebar continues this test



----------------------------------------------------------------------

     1)  Test copy constructor          2)  Test assignment operator
     3)  Test >> input function         4)  Test + operator
     5)  Test == operator               6)  Test destructor
     Q)  Quit program

Choice? 3


>>>>>>>>>>>>>  Testing input operator >>>>>>>>>>>>>>>>>

Enter MyFloat ==>    000000.23445

After the read,  X = '0.23445'


------------------------------------------  Spacebar continues this test



----------------------------------------------------------------------

     1)  Test copy constructor          2)  Test assignment operator
     3)  Test >> input function         4)  Test + operator
     5)  Test == operator               6)  Test destructor
     Q)  Quit program

Choice? 3


>>>>>>>>>>>>>  Testing input operator >>>>>>>>>>>>>>>>>

Enter MyFloat ==> .456h78

After the read,  X = '0.456'


------------------------------------------  Spacebar continues this test


----------------------------------------------------------------------

     1)  Test copy constructor          2)  Test assignment operator
     3)  Test >> input function         4)  Test + operator
     5)  Test == operator               6)  Test destructor
     Q)  Quit program

Choice? 3


>>>>>>>>>>>>>  Testing input operator >>>>>>>>>>>>>>>>>

Enter MyFloat ==> .123456789012345

After the read,  X = '0.1234567890'



----------------------------------------------------------------------

     1)  Test copy constructor          2)  Test assignment operator
     3)  Test >> input function         4)  Test + operator
     5)  Test == operator               6)  Test destructor
     Q)  Quit program

Choice? 5


== == == == ==  Testing "== " for MyFloat  == == == == ==

MyFloat variables have maximum length of 10

Enter A  ==> .12

Enter B  ==> .1200000

 (A == B) is TRUE

------------------------------------------  Spacebar continues this test


----------------------------------------------------------------------

     1)  Test copy constructor          2)  Test assignment operator
     3)  Test >> input function         4)  Test + operator
     5)  Test == operator               6)  Test destructor
     Q)  Quit program

Choice? 5


== == == == ==  Testing "== " for MyFloat  == == == == ==

MyFloat variables have maximum length of 10

Enter A  ==> .123

Enter B  ==> .123

 (A == B) is TRUE

------------------------------------------  Spacebar continues this test


----------------------------------------------------------------------

     1)  Test copy constructor          2)  Test assignment operator
     3)  Test >> input function         4)  Test + operator
     5)  Test == operator               6)  Test destructor
     Q)  Quit program

Choice? 5


== == == == ==  Testing "== " for MyFloat  == == == == ==

MyFloat variables have maximum length of 10

Enter A  ==> .345

Enter B  ==> .356

 (A == B) is FALSE

------------------------------------------  Spacebar continues this test


----------------------------------------------------------------------

     1)  Test copy constructor          2)  Test assignment operator
     3)  Test >> input function         4)  Test + operator
     5)  Test == operator               6)  Test destructor
     Q)  Quit program

Choice? 5


== == == == ==  Testing "== " for MyFloat  == == == == ==

MyFloat variables have maximum length of 10

Enter A  ==> .45

Enter B  ==> .4500001

 (A == B) is FALSE

------------------------------------------  Spacebar continues this test





----------------------------------------------------------------------

     1)  Test copy constructor          2)  Test assignment operator
     3)  Test >> input function         4)  Test + operator
     5)  Test == operator               6)  Test destructor
     Q)  Quit program

Choice? 4


++++++++++++++++  Testing "+"  for MyFloat  ++++++++++++++++
                  (Do not use leading zero)

Enter X  ==>   .123

Enter Y  ==> + .12
             ------
              0.243


------------------------------------------  Spacebar continues this test

Enter X  ==>   .356

Enter Y  ==> + .236
             ------
              0.586


------------------------------------------  Spacebar continues this test

Enter X  ==>   .12345

Enter Y  ==> + .4567
             ------
              0.573


------------------------------------------  Spacebar continues this test

Enter X  ==>   .12

Enter Y  ==> + .7
             -----
              0.87


------------------------------------------  Spacebar continues this test

Enter X  ==>   .12

Enter Y  ==> + .12
             -----
              0.27


------------------------------------------  Spacebar continues this test*/
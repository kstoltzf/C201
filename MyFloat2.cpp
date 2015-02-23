//Kyle Stoltzfus
//C201 5:30 - 7:20
//Homework 6
//MyFloat2.cpp
/*             MyFloat
           ---------------
A C++ class definition that creates a data type MyFloat. This data type allows 
for the use and manipulation of small floats between 0 and 1, and provides 
accuracy to 20 digits in calculations. MyFloat2.cpp improves on the original 
class definition in MyFloat.cpp by adding two new member functions and replacing 
several others with improved versions.

Changes:

<<	: Overloaded "<<" that replaces the Write() function and allows the use of the 
      insertion operator in the code of any program using this class
>>	: Overloaded ">>" that replaces the Read() function and allow the use of the 
      extraction operator in the code of any program using this class

Additions:

=	: Overloaded "=" that allows the use of the assignment operator in the code 
      of any program using this class
>	: Overloaded ">" that allows the use of the greater than comparator operator 
      in the code of any program using this class
*/

#include <iostream>
using namespace std;

class MyFloat
{
	private:
		enum {MAX_DIGITS = 20};
		char Number[MAX_DIGITS];
		char NumberOfDigits;

	public:
		short int MaxDigits();    //Returns the maximum number of digits 
		                          //possible in a MyFloat
		short int Digits();       //Returns the number of digits in a MyFloat
		MyFloat();                //Default constructor
		MyFloat& operator+ (MyFloat &MyFloat2);  //Adds two MyFloats together 
		                                  //and returns the result as a MyFloat
		char operator== (MyFloat &MyFloat2);    //Compares two MyFloats to
		                                        //see if they are equal
		MyFloat& operator= (const char Source[]);      //Stores the value 
		   //on the right hand side of the assignment operator in a MyFloat
		char operator> (MyFloat &Float1);       //Compares two MyFloats 
		                                 //to determine which one is bigger
		friend ostream& operator<< (ostream& Output, const MyFloat &Float1);  
		//Allows the use of the insertion operator
		friend istream& operator>> (istream& Input, MyFloat &Float1);         
		//Allows the use of the extraction operator
};

/******************** operator<< *********************************
Action: This function allow the use of the insertion operator in the code of any 
program implementing the MyFloat class. For example, it is now legal to have code 
like the following: cout << any MyFloat variable. This code will display the 
contents of the arrayNumber[] on the screen. Also allows for cascading.
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
members Number[] and NumberOfDigits. It also allows cascading. This function works
exactly like the Read() function in MyFloat.cpp. In order to simplify any functions
that use the data in Number[], the input is converted from a char to an int before 
it is stored in Number[] so that Number[] holds the actual int value wanted and not
the ASCII value of that int as a char. This is done by subtracting the ASCII value 
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

	while (Ch != '.' && Ch != '\n')  //skips all data before the '.' and stops 
		Input.get(Ch);    //on a '.' (start of MyFloat) or '\n' (end of user input)

	if (Ch == '.')
	{
		Input.get(Ch);

		while (isdigit(Ch) && Float1.NumberOfDigits < Float1.MAX_DIGITS)
		{
			Float1.Number[Float1.NumberOfDigits] = Ch - '0';
			++ Float1.NumberOfDigits;
			Input.get(Ch);
		}
	}
		
	for (char i = Float1.NumberOfDigits; i < Float1.MAX_DIGITS; ++i) 
			Float1.Number[i] = 0;  //fill rest of array with 0s

	Input.putback(Ch);  //needed for test program to run correctly

	return Input;  //allows cascading
}

/*******************MaxDigits**************************************
Action: This function returns the maximum number of digits in a MyFloat.
Parameters: None
Returns: The enumerated data type MAX_DIGITS that is declared in the 
private data of the class.
******************************************************************/
short int MyFloat::MaxDigits()
{
	return MAX_DIGITS;
}

/************************Digits**********************************
Action: This function returns the number of digits in a MyFloat.
Parameters: None
Returns: The NumberOfDigits in a MyFloat as determined by the read function.
*****************************************************************/
short int MyFloat::Digits()
{
	return NumberOfDigits;  //Typecasts the char variable NumberOfDigits
	                        //to an int for display in standard output
}

/*******************MyFloat (constructor) ***************************
Action: This function is the default constructor. Every time a MyFloat 
variable is created,this constructor sets NumberOfDigits = 0 and fills 
the array Number[] with 0s.
Parameters: None
Returns: Nothing
********************************************************************/
MyFloat::MyFloat()
{
	NumberOfDigits = 0;
	
	for (char i = 0; i < MAX_DIGITS; ++i)  //Fills the entire array
		Number[i] = 0;                     //Number[] with zeroes
		               
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
	MyFloat Result;
	char CarryBit = 0, i, Sum;

	Result.NumberOfDigits = NumberOfDigits;  

	if (Result.NumberOfDigits < MyFloat2.NumberOfDigits)
		Result.NumberOfDigits = MyFloat2.NumberOfDigits;  //Makes sure Result.NumberOfDigits is equal 
	                                //to the NumberOfDigits of the longest array being added together.
	for (i = 0; i < Result.NumberOfDigits - 1; ++i);      //Tells the program how many elements 
	                                                      //of the array to add together.
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

	return Result;
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
	char Length = NumberOfDigits;

	if (Length < MyFloat2.NumberOfDigits) 
		Length = MyFloat2.NumberOfDigits;  //Makes sure Length is set to the length of the 
	                                       //longest array being compared.
	for (char i = 0; i < Length; ++i)      //Loop only needs to check up to the length 
	{	                                   //of the longest array being compared. 
	                                       //After that, both arrays will contain only 0s.
		if (Number[i] != MyFloat2.Number[i])  //Loop stops as soon as it finds elements that do not match.
			return 0;
	}

	return 1;
}

/****************** operator= ***********************
Action: This function allows for the use of the assignment operator. Stores the value in the 
null terminating character array on the right hand side into the array Number[] in the MyFloat 
data type. Also determines the number of elements being stored in Number[] and places that value
in NumberOfDigits. Then fills the rest of Number[] with 0s. This function uses the same process 
for storing data in Number[] as the overloaded extraction operator.
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
	char i = 0, Length = strlen(Source);  //strlen determines the length of the array Source[]
	NumberOfDigits = 0;

	while (Source[i] != '.' && i < Length) //skips all characters in front of the '.'
		++i;

	if (Source[i] == '.')
	{
		++i;

		for (;isdigit(Source[i]) && NumberOfDigits < MAX_DIGITS; ++i, ++NumberOfDigits)
			Number[NumberOfDigits] = Source[i] - '0';  
	

		i = NumberOfDigits; //fills NumberOfDigits data member

		for (i; i < MAX_DIGITS; ++i)  //fills the rest of the array Number[] with 0s
			Number[i] = 0;
	}

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
char MyFloat::operator> (MyFloat &Float2)
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

/*Testing Member Functions of MyFloat Class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test >> operator
   2)  Test =  operator
   3)  Test MaxDigits and Digits
   4)  Test == and > operators
   5)  Test + operator
   6)  Test + execution speed
   Q)  Quit program

Choice? 1




>>>>>>>>  Testing Read function  >>>>>>>>>>>>

Enter a MyFloat ==> 0321454

Input error!
After read,   X = '0.?'


--------------------------------------------------  Spacebar continues test:

Enter a MyFloat ==> 0.

Input error!
After read,   X = '0.?'


--------------------------------------------------  Spacebar continues test:

Enter a MyFloat ==> .1235

After read,   X = '0.1235'


--------------------------------------------------  Spacebar continues test:

Enter a MyFloat ==> 0.324fhfghd

After read,   X = '0.324'


--------------------------------------------------  Spacebar continues test:

Enter a MyFloat ==> 2345ghjjfghfd.3214

After read,   X = '0.3214'


--------------------------------------------------  Spacebar continues test:

Enter a MyFloat ==> 0.012345678901234567890123

After read,   X = '0.01234567890123456789'


--------------------------------------------------  Spacebar continues test:


Testing Member Functions of MyFloat Class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test >> operator
   2)  Test =  operator
   3)  Test MaxDigits and Digits
   4)  Test == and > operators
   5)  Test + operator
   6)  Test + execution speed
   Q)  Quit program

Choice? 2




------------  Testing "=" for MyFloat --------------------

Enter string holding float: 0124

Format error!
After assignment,     'X = 0.?'


--------------------------------------------------  Spacebar continues test:

Enter string holding float: 0.

Format error!
After assignment,     'X = 0.?'


--------------------------------------------------  Spacebar continues test:

Enter string holding float: .3258

After assignment,     'X = 0.3258'


--------------------------------------------------  Spacebar continues test:

Enter string holding float: .644jhhj/.,

After assignment,     'X = 0.644'


--------------------------------------------------  Spacebar continues test:

Enter string holding float: 131213hjhf/,[].568

After assignment,     'X = 0.568'


--------------------------------------------------  Spacebar continues test:

Enter string holding float: .012345678901234567890312

After assignment,     'X = 0.01234567890123456789'


--------------------------------------------------  Spacebar continues test:


Testing Member Functions of MyFloat Class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test >> operator
   2)  Test =  operator
   3)  Test MaxDigits and Digits
   4)  Test == and > operators
   5)  Test + operator
   6)  Test + execution speed
   Q)  Quit program

Choice? 4





============  Testing "==" and ">" for MyFloat  ================

Enter X  ==> .123456789

Enter Y  ==> .123456789


0.123456789 == 0.123456789

--------------------------------------------------  Spacebar continues test:

Enter X  ==> .32000000000000

Enter Y  ==> .32


0.32000000000000 == 0.32

--------------------------------------------------  Spacebar continues test:

Enter X  ==> .3698

Enter Y  ==> .3598


0.3698 > 0.3598

--------------------------------------------------  Spacebar continues test:

Enter X  ==> .368

Enter Y  ==> .367


0.368 > 0.367

--------------------------------------------------  Spacebar continues test:

Enter X  ==> .369

Enter Y  ==> .3691


0.3691 > 0.369

--------------------------------------------------  Spacebar continues test:

Enter X  ==> .3987

Enter Y  ==> .456


0.456 > 0.3987

--------------------------------------------------  Spacebar continues test:

Enter X  ==> .365

Enter Y  ==> .366


0.366 > 0.365

--------------------------------------------------  Spacebar continues test:

Enter X  ==> .258

Enter Y  ==> .2587


0.2587 > 0.258

--------------------------------------------------  Spacebar continues test:


Testing Member Functions of MyFloat Class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test >> operator
   2)  Test =  operator
   3)  Test MaxDigits and Digits
   4)  Test == and > operators
   5)  Test + operator
   6)  Test + execution speed
   Q)  Quit program

Choice? 5





++++++++++++  Testing "+"  for MyFloat  ++++++++++++++++
                  (Do not use leading zero)

Enter X  ==> .325

Enter Y  ==> .123


    X + Y = 0.448



--------------------------------------------------  Spacebar continues test:

Enter X  ==> .254

Enter Y  ==> .379


    X + Y = 0.633



--------------------------------------------------  Spacebar continues test:

Enter X  ==> .589

Enter Y  ==> .985


    X + Y = 0.574



--------------------------------------------------  Spacebar continues test:

Enter X  ==> .1234567890123456789

Enter Y  ==> .1558445745587427874


    X + Y = 0.2793013635710884663



--------------------------------------------------  Spacebar continues test:


Testing Member Functions of MyFloat Class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test >> operator
   2)  Test =  operator
   3)  Test MaxDigits and Digits
   4)  Test == and > operators
   5)  Test + operator
   6)  Test + execution speed
   Q)  Quit program

Choice? 6




Performing 10000000 float additions...  Time:   0.08

Performing 10000000 MyFloat additions...  Time:   7.27

Addition of floats is: 90.92 times faster than addition of MyFloats.


--------------------------------------------------  Spacebar continues test:

Performing 10000000 float additions...  Time:   0.07

Performing 10000000 MyFloat additions...  Time:   7.28

Addition of floats is: 105.46 times faster than addition of MyFloats.


--------------------------------------------------  Spacebar continues test:


Testing Member Functions of MyFloat Class
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test >> operator
   2)  Test =  operator
   3)  Test MaxDigits and Digits
   4)  Test == and > operators
   5)  Test + operator
   6)  Test + execution speed
   Q)  Quit program

Choice? q



Press any key to continue . . .
*/


//Kyle Stoltzfus
//C201 5:30 - 7:30
//10/22/2012
//Homework 5
//MyFloat.cpp
//This program is an implementation file for a class called MyFloat.

#include <iostream>
using namespace std;

class MyFloat
{
	private:
		enum {MAX_DIGITS = 20};
		char Number[MAX_DIGITS];
		char NumberOfDigits;

	public:
		void Write();       //Writes a MyFloat to standard output
		short int MaxDigits();    //Returns the maximum number of digits possible in a MyFloat
		short int Digits();       //Returns the number of digits in a MyFloat
		void Read();        //Reads a MyFloat from standard input
		MyFloat();          //Default constructor
		MyFloat operator+ (MyFloat MyFloat2);  //Adds two MyFloats together and returns the result as a MyFloat
		char operator== (MyFloat MyFloat2);     //Compares two MyFloats to see if they are equal
};

/***************Write**************************
Action: This function writes a MyFloat to standard output. If there was an error
in the input (NumberOfDigits == 0), 0.? will be displayed in the output.
Parameters: None
Returns: Nothing
**********************************************/
void MyFloat::Write()
{
	if (NumberOfDigits == 0)  //There was an error in input.
		cout << "0.?";

	else                    
	{
		cout << "0.";

		for (char i = 0; i < NumberOfDigits; ++i)
			cout << short int(Number[i]);           //Needs to be typecast as an int or it will display the 
		                                            //characters with the ASCII values 0 - 9 that are in the array Number[]
	}
}

/*******************MaxDigits**************************************
Action: This function returns the maximum number of digits in a MyFloat.
Parameters: None
Returns: The enumerated data type MAX_DIGITS that is declared in the private data of the class.
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
	return NumberOfDigits;  //Typecasts the char variable NumberOfDigits to an int for display in standard output
}

/*******************MyFloat (constructor) ***************************
Action: This function is the default constructor. Every time a MyFloat variable is created,
this constructor sets NumberOfDigits = 0 and fills the array Number[] with 0s.
Parameters: None
Returns: Nothing
********************************************************************/
MyFloat::MyFloat()
{
	NumberOfDigits = 0;
	
	for (char i = 0; i < MAX_DIGITS; ++i)  //Fills the entire array Number[] with zeroes
		Number[i] = 0;                 
}

/*******************************Read*****************************
Action: This function reads a MyFloat from standard input. It converts the input
from a char to an int before storing it in the array Number[]. This is done by 
converting the char to an int and then subtracting 48. For example, the int 2 has an
ASCII value of 50 as a char. Typecasting the char 2 as an int will produce an int of 50.
Subtracting 48 from 50 will produce the value 2 that is then stored in the array Number[].
Parameters: None
Returns: Nothing
*****************************************************************/
void MyFloat::Read()
{
	char ch;

	cin.get(ch);

	while ((ch == '0' || isspace(ch)) && ch != '\n')  //Skips leading 0s and whitespaces and makes sure
		cin.get(ch);                                  //the last character in the input buffer is not a newline

	if (ch == '.')
	{
		cin.get(ch);

		while (isdigit(ch) && NumberOfDigits < MAX_DIGITS)
		{
			Number[NumberOfDigits] = short int(ch) - 48;
			++ NumberOfDigits;
			cin.get(ch);
		}
	}
	
	cin.putback(ch);  //Needed for test program to function correctly
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
MyFloat MyFloat::operator+ (MyFloat MyFloat2)
{
	MyFloat Result;
	char CarryBit = 0, i, Sum;

	Result.NumberOfDigits = NumberOfDigits;  

	if (Result.NumberOfDigits < MyFloat2.NumberOfDigits)
		Result.NumberOfDigits = MyFloat2.NumberOfDigits;  //Makes sure Result.NumberOfDigits is equal to the NumberOfDigits
	                                                      //of the longest array being added together.
	for (i = 0; i < Result.NumberOfDigits - 1; ++i);      //Tells the program how many elements of the array to add together.

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
char MyFloat::operator== (MyFloat MyFloat2)
{
	char Length = NumberOfDigits;

	if (Length < MyFloat2.NumberOfDigits) 
		Length = MyFloat2.NumberOfDigits;  //Makes sure Length is set to the length of the longest array being compared

	for (char i = 0; i < Length; ++i)      //Loop only needs to check up to the length of the longest array being compared. 
	{                                      //After that, both arrays will contain only 0s.
		if (Number[i] != MyFloat2.Number[i])  //Loop stops as soon as it finds elements that do not match.
			return 0;
	}

	return 1;
}

/*
Testing Member Functions of MyFloat Class
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test Read function
   2)  Test + operator
   3)  Test MaxDigits and Digits
   4)  Test ==  operator
   Q)  Quit program

Choice? 1




>>>>>>>>  Testing Read function  >>>>>>>>>>>>

Enter a MyFloat ==> 05239

Input error!
After read,   X = '0.?'


---------------------------  Press Spacebar then Enter key to continue:


Testing Member Functions of MyFloat Class
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test Read function
   2)  Test + operator
   3)  Test MaxDigits and Digits
   4)  Test ==  operator
   Q)  Quit program

Choice? 1




>>>>>>>>  Testing Read function  >>>>>>>>>>>>

Enter a MyFloat ==> 0.

Input error!
After read,   X = '0.?'


---------------------------  Press Spacebar then Enter key to continue:


Testing Member Functions of MyFloat Class
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test Read function
   2)  Test + operator
   3)  Test MaxDigits and Digits
   4)  Test ==  operator
   Q)  Quit program

Choice? 1




>>>>>>>>  Testing Read function  >>>>>>>>>>>>

Enter a MyFloat ==> 000

Input error!
After read,   X = '0.?'


---------------------------  Press Spacebar then Enter key to continue:


Testing Member Functions of MyFloat Class
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test Read function
   2)  Test + operator
   3)  Test MaxDigits and Digits
   4)  Test ==  operator
   Q)  Quit program

Choice? 1




>>>>>>>>  Testing Read function  >>>>>>>>>>>>

Enter a MyFloat ==> .346

After read,   X = '0.346'


---------------------------  Press Spacebar then Enter key to continue:

Testing Member Functions of MyFloat Class
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test Read function
   2)  Test + operator
   3)  Test MaxDigits and Digits
   4)  Test ==  operator
   Q)  Quit program

Choice? 1




>>>>>>>>  Testing Read function  >>>>>>>>>>>>

Enter a MyFloat ==> 0.356a

After read,   X = '0.356'


---------------------------  Press Spacebar then Enter key to continue:

Testing Member Functions of MyFloat Class
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test Read function
   2)  Test + operator
   3)  Test MaxDigits and Digits
   4)  Test ==  operator
   Q)  Quit program

Choice? 1




>>>>>>>>  Testing Read function  >>>>>>>>>>>>

Enter a MyFloat ==> .346

After read,   X = '0.346'


---------------------------  Press Spacebar then Enter key to continue:

Testing Member Functions of MyFloat Class
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test Read function
   2)  Test + operator
   3)  Test MaxDigits and Digits
   4)  Test ==  operator
   Q)  Quit program

Choice? 3




============ Testing Digits and MaxDigits  ==============

X.MaxDigits() = 20


Enter MyFloat ==> 0.3456

Digits(0.3456) = 4


---------------------------  Press Spacebar then Enter key to continue:


Testing Member Functions of MyFloat Class
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test Read function
   2)  Test + operator
   3)  Test MaxDigits and Digits
   4)  Test ==  operator
   Q)  Quit program

Choice? 3




============ Testing Digits and MaxDigits  ==============

X.MaxDigits() = 20


Enter MyFloat ==> 0.45!y

Digits(0.45) = 2


---------------------------  Press Spacebar then Enter key to continue:

Testing Member Functions of MyFloat Class
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test Read function
   2)  Test + operator
   3)  Test MaxDigits and Digits
   4)  Test ==  operator
   Q)  Quit program

Choice? 4





============  Testing "=="  for MyFloat  ================

Enter X  ==> 0.23

Enter Y  ==> 0.23


0.23 is equal to 0.23

---------------------------  Press Spacebar then Enter key to continue:


Testing Member Functions of MyFloat Class
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test Read function
   2)  Test + operator
   3)  Test MaxDigits and Digits
   4)  Test ==  operator
   Q)  Quit program

Choice? 4





============  Testing "=="  for MyFloat  ================

Enter X  ==> 0.340

Enter Y  ==> 0.34


0.340 is equal to 0.34

---------------------------  Press Spacebar then Enter key to continue:




Testing Member Functions of MyFloat Class
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test Read function
   2)  Test + operator
   3)  Test MaxDigits and Digits
   4)  Test ==  operator
   Q)  Quit program

Choice? 4





============  Testing "=="  for MyFloat  ================

Enter X  ==> 0.345

Enter Y  ==> 0.34


0.345 is NOT equal to 0.34

---------------------------  Press Spacebar then Enter key to continue:


Testing Member Functions of MyFloat Class
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test Read function
   2)  Test + operator
   3)  Test MaxDigits and Digits
   4)  Test ==  operator
   Q)  Quit program

Choice? 2




------------  Testing "+" for MyFloat --------------------

Enter a MyFloat X ==> 0.34

Enter another MyFloat Y ==> 0.34

  X    0.34
+ Y    0.34
-----------
  Z    0.68

---------------------------  Press Spacebar then Enter key to continue:

Testing Member Functions of MyFloat Class
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test Read function
   2)  Test + operator
   3)  Test MaxDigits and Digits
   4)  Test ==  operator
   Q)  Quit program

Choice? 2




------------  Testing "+" for MyFloat --------------------

Enter a MyFloat X ==> 0.35

Enter another MyFloat Y ==> 0.36

  X    0.35
+ Y    0.36
-----------
  Z    0.71

---------------------------  Press Spacebar then Enter key to continue:


Testing Member Functions of MyFloat Class
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test Read function
   2)  Test + operator
   3)  Test MaxDigits and Digits
   4)  Test ==  operator
   Q)  Quit program

Choice? 2




------------  Testing "+" for MyFloat --------------------

Enter a MyFloat X ==> 0.56

Enter another MyFloat Y ==> .92

  X    0.56
+ Y    0.92
-----------
  Z    0.48

---------------------------  Press Spacebar then Enter key to continue:


Testing Member Functions of MyFloat Class
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   1)  Test Read function
   2)  Test + operator
   3)  Test MaxDigits and Digits
   4)  Test ==  operator
   Q)  Quit program

Choice? 2




------------  Testing "+" for MyFloat --------------------

Enter a MyFloat X ==> 0.345adfg

Enter another MyFloat Y ==> 0.456a

  X    0.345
+ Y    0.456
------------
  Z    0.801
*/
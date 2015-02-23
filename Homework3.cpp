//Kyle Stoltzfus
//C201 5:30 - 7:20
//9/23/2012
//Homework 3
//Homework3.cpp
//This program explains and proves the birthday paradox.

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
using namespace std;

void DisplayMenu();
char MenuChoice();
void ExplainBirthdayParadox();
void VerifyBirthdayParadox();
void DisplayBirthdaySet();
void GenerateBirthdaySet(int []);
void SortBirthdaySet(int []);
void ConvertDayOfYear(int, int&, int&);
int DaysInMonth(int);

const int NUMBER_OF_SETS = 1000;
const int SAMPLE_SIZE = 23;

void main()
{
	char Choice;

	srand(time(NULL));

	do 
	{
		DisplayMenu();
		Choice = MenuChoice();
		
		switch (Choice)
		{
			case '1': ExplainBirthdayParadox();break;   //without the break statement all cases after the true case will execute
			case '2': VerifyBirthdayParadox();break;
			case '3': DisplayBirthdaySet();
		}
	}
	while (Choice != 'E' && Choice != 'e');
}

/************************DisplayMenu*************************************
Action: This function displays displays a menu with options for the user to choose from
Parameters:
In: Nothing
Out: Nothing
Returns: Nothing
*************************************************************************/
void DisplayMenu()
{
	cout << "1)  Explain birthday paradox" << endl;
	cout << "2)  Check birthday paradox by generating 1000 sets of birthdays" << endl;
	cout << "3)  Display one set of 23 birthdays" << endl;
	cout << "E)  Exit" << endl << endl;
}

/*********************************GetMenuChoice****************************
Action: This function reads the user's selection from the menu
Parameters:
In: Nothing
Out: Nothing
Returns: The user's choice from the menu as a character
**************************************************************************/
char MenuChoice()
{
	char Choice;
	
	cin >> Choice;
	cout << endl;
	
	return Choice;
}

/*******************ExplainBirthdayParadox*******************************
Action: This function diplays an explanation of the birthday paradox
Parameters:
In: Nothing
Out: Nothing
Returns: Nothing
************************************************************************/
void ExplainBirthdayParadox()
{
	cout << "If 23 persons are chosen at random, then the chances are more than 50%" << endl
		<< "that at least two will have the same birthday!" << endl << endl;
}

/*********************VerifyBirthdayParadox******************************
Action: This function tests the birthday paradox by generating 1000 random sets of 23
birthdays and checking for matches. If there are more than 1 pair of matching birthdays
per set, only 1 pair is counted. 
Parameters:
In: Nothing
Out: Nothing
Returns: Nothing
************************************************************************/
void VerifyBirthdayParadox()
{
	int k, NumberOfMatches = 0, Birthdays[SAMPLE_SIZE];

	for (int i = 1; i <= NUMBER_OF_SETS; ++i)
	{
		GenerateBirthdaySet(Birthdays);
		SortBirthdaySet(Birthdays);

		for (k = 0; Birthdays[k] != Birthdays[k + 1] && k < SAMPLE_SIZE; ++k);  //checks the array for matches and breaks out immediately if a match is found

		if (k < (SAMPLE_SIZE - 1) && Birthdays[k] == Birthdays[k + 1])  //k < (SAMPLE_SIZE - 1) makes sure that the previous for loop didn't find a match by checking the last element of the array against the value in the next memory location
			++ NumberOfMatches;
	}

	cout << "Generating 1000 sets of 23 birthdays and checking for matches ..." << endl << endl;
	cout << "Results : " << NumberOfMatches << " out of " << NUMBER_OF_SETS << " ("
		<< setiosflags(ios::fixed | ios::showpoint) << setprecision(1) << float(NumberOfMatches) / 10 
		<< "%) of the sets contained matching birthdays" << endl;

	for (int n = 0; n <= 75; ++ n)
		cout << "=";

	cout << endl << endl;
}

/************************DisplayBirthdaySet****************************
Action: This function displays a random set of 23 birthdays in a formatted output
with month names and the day of the month. It also shows any matches by displaying a 2
in front of the month name.
Parameters:
In: Nothing
Out: Nothing
Returns: Nothing
***********************************************************************/
void DisplayBirthdaySet()
{
	int Counter, OutputCounter = 0, DayOfYear, MonthNumber, DayOfMonth, Birthdays[SAMPLE_SIZE];
	char *Months[13] = {" ", "January", "February", "March", "April", "May", "June", "July",
		"August", "September", "October", "November", "December"};

	GenerateBirthdaySet(Birthdays);
	SortBirthdaySet(Birthdays);

	cout << "Here are the results of generating a set of 23 birthdays" << endl;

	for (int n = 0; n <= 75; ++ n)
		cout << "=";
	
	cout << endl;

	for (int i = 0; i < SAMPLE_SIZE; ++ i)
	{
		Counter = 1;   //Counter needs to be reset whenever a new date is checked. Otherwise, matches will carry over from previous dates.

		DayOfYear = Birthdays[i];
		
		ConvertDayOfYear(DayOfYear, MonthNumber, DayOfMonth);

		while (Birthdays[i] == Birthdays[i + 1])
		{
			++ Counter;
			++ i;            //Ensures matching dates are only displayed once in the output.
		}

		if (Counter > 1)
			cout << " (" << Counter << ")" << " ";
		else
			cout << "     ";

		cout << left << setw(9) << Months[MonthNumber] << right << setw(5) << DayOfMonth;
		
		++ OutputCounter;

		if (OutputCounter % 3 == 0)
			cout << endl;
	}

	cout << endl << endl;
}

/**************************GenerateBirthdaySet**********************************
Action: This function fills an array with 23 random birthdays between 1 and 365.
Birthdays are in days only. For example, February 1 is 32.
Parameters:
In: An empty integer array
Out: The same integer array filled with random numbers between 1 and 365 in random order
Returns: Nothing
********************************************************************************/
void GenerateBirthdaySet(int Birthdays[SAMPLE_SIZE])
{
	for (int i = 0; i < SAMPLE_SIZE; ++i)
		Birthdays[i] = 1 + rand() % 365;
}

/************************  Swap  *****************************************
Provided by class instructor: Matt Holloway
  DESCRIPTION  Interchanges the contents of A and B.

  PARAMETERS   IN-OUT  A and B, the variables to swap

  NOTE         This function is declared to be inline so that the overhead
               of a function call is avoided.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
inline void Swap (int &A, int &B)
{
  int Temp= A;
  A = B;
  B = Temp;
}

/*************************  SelectionSort *********************************
Provided by class instructor: Matt Holloway
DESCRIPTION  Sorts the members of the array List[1..Last]. (The array
             element in position 0 is ignored.) This version of the
             selection sort works by finding the smallest element of the
             entire array and placing it in its correct position (1).
             Next the smallest element in List[2]..List[Last] is found
             and placed in position 2. After step N, the elements
             List[1]..List[N] are in their correct places.

PARAMETERS
  List       IN-OUT, an array with subscripts from 0..Last of int

  Last       IN, the subscript of the last array member to be sorted

CALLS        Swap, an inline function to swap array elements.

NOTE:        To sort List[0..Last] change for loop to:

             for ( Start = 0; Start < Last; ++Start )

Precondition: Last does not go outside scope of array
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void SortBirthdaySet (int Birthdays[])
{
  int i, Start, SubSmall;

  for ( Start = 0; Start < SAMPLE_SIZE; ++Start )   // Sort items 1..Last
    {
    SubSmall = Start;                        //  subscript of smallest elt.

    for ( i = Start + 1; i < SAMPLE_SIZE; i++ )    //  Find subscript of smallest
      if ( Birthdays[i] < Birthdays[SubSmall] )        //   elt. in tail end of array
        SubSmall= i;

    Swap(Birthdays[SubSmall],  Birthdays[Start]);      // Place in correct position
    }
}

/**********************ConvertDayOfYear**************************************
Action: This function converts a day number (32) into a month and day (2  1)
Parameters: 
In: The day of the year from the DisplayBirthdaySet function
Out: The month number and the day of the month 
Returns: Nothing
*****************************************************************************/
void ConvertDayOfYear(int DayOfYear, int& MonthNumber, int& DayOfMonth)
{
	int MonthLength;
	MonthNumber = 1;

	MonthLength = DaysInMonth(MonthNumber);

	while (DayOfYear > MonthLength)
	{
		DayOfYear -= MonthLength;
		++ MonthNumber;
		MonthLength = DaysInMonth(MonthNumber);
	}

	DayOfMonth = DayOfYear;
}

/**********************DaysInMonth*****************************
Action: This function determines the number of days in a particular month
Parameters:
In: The month number (1 - 12)
Out: Nothing
Returns: The number of days in the month
- This is for a non-leap year. February has 28 days.
***************************************************************/
int DaysInMonth(int MonthNumber)
{
	switch (MonthNumber)
	{
		case 2: return 28; break;  //February
		case 4:                    //April
		case 6:                    //June
		case 9:                    //September
		case 11: return 30; break; //November
		default: return 31;        //All other months
	}
}


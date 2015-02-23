//Kyle Stoltzfus
//5:30 - 7:20
//9/17/2012
//Homework 2
//Homework2.cpp
//This program censors the input entered by the user and replaces the word hell
//with the word heck. It then displays the original input and the censored input. 
//It continually asks for input until a null string is entered.

#include <iostream>
#include <ctype.h>
using namespace std;

void GetSentence (char []);
void CopyString (char [], char []);
void MakeUpperCase (char []);
void InsertBlankStartEnd (char []);
void ReplacePunctWithBlanks (char []);
void SearchAndReplaceHell (char []);
void DeleteBlankStartEnd (char []);
void OriginalCaseAndPunct (char [], char []);
void DisplayResult (char [], char []);

const int MAX_LENGTH = 100;

void main ()
{
	char Str[MAX_LENGTH] = "";
	char StrCopy[MAX_LENGTH] = "";

	GetSentence (Str);

	while (Str[0] != 0)
	{
		CopyString (StrCopy, Str);
		MakeUpperCase (StrCopy);
		InsertBlankStartEnd (StrCopy);
		ReplacePunctWithBlanks (StrCopy);
		SearchAndReplaceHell (StrCopy);
		DeleteBlankStartEnd (StrCopy);
		OriginalCaseAndPunct (Str, StrCopy);
		DisplayResult (Str, StrCopy);
		GetSentence (Str);
	}

	cout << "Goodbye....." << endl << endl;
}

/*******************GetSentence********************************
Action: This function gets input from the user and stores it in
a character array.
Parameters:
In: An empty character array called Str[]
Out: The same character array Str[] but it has been filled by user input
Returns: Nothing
**************************************************************/
void GetSentence (char Str[MAX_LENGTH])
{
	cout << "Enter Sentence ==> ";
	cin.getline(Str, MAX_LENGTH);
}

/**********************CopyString*****************************
Action: This function takes the original character array and copies
it to a new one so that changes can be made without overwriting the 
original input.
Parameters:
In: The character array Str[] filled by GetSentence and an empty 
    character array called StrCopy[]
Out: The character array StrCopy[] which is now an exact copy 
     of the original input in Str[]
Returns: Nothing
*************************************************************/
void CopyString (char StrCopy[MAX_LENGTH], char Str[MAX_LENGTH])
{
	for (int i = 0; Str[i] >= 0; ++i)
		StrCopy[i] = Str[i];
}

/***************************MakeUpperCase********************
Action: This function converts all alphabetic characters in the character
array StrCopy[] to uppercase.
Parameters:
In: The character array StrCopy[]
Out: The same character array StrCopy[] with all the alphabetic characters
     changed to uppercase
Returns: Nothing
*************************************************************/
void MakeUpperCase (char StrCopy[MAX_LENGTH])
{
	for (int i = 0; StrCopy[i]; ++i)
		StrCopy[i] = toupper(StrCopy[i]);
}

/*****************InsertBlankStartEnd************************
Action: This function inserts a blank at the beginning of the character
array StrCopy[] and at the end, just before the null terminator.
Parameters: 
In: The character array StrCopy[]
Out: The character array StrCopy[] with a space at StrCopy[0] and
     just before the null terminator at the end of the array.
Returns: Nothing
************************************************************/
void InsertBlankStartEnd (char StrCopy[MAX_LENGTH])
{
	int i;

	for (i = 0; StrCopy[i]; ++i);

	StrCopy[i + 2] = StrCopy[i];
	StrCopy[i + 1] = ' ';

	for (--i; i >= 0; --i)
		StrCopy[i + 1] = StrCopy[i];

	StrCopy[0] = ' ';
}

/**********************ReplacePunctWithBlanks****************
Action: This function replaces all punctuation in the character array
StrCopy[] with spaces.
Parameters:
In: The character array StrCopy[]
Out: The character array StrCopy[] with all punctuation replaced by spaces
Returns: Nothing
*************************************************************/
void ReplacePunctWithBlanks (char StrCopy[MAX_LENGTH])
{
	for (int i = 0; StrCopy[i]; ++i)
	{
		if (ispunct(StrCopy[i]))
			StrCopy[i] = ' ';
	}
}

/*****************SearchAndReplaceHell**************************
Action: This function searches the array StrCopy[] and replaces the word 
hell with the word heck.
Special Cases:
- The program will censor hell with puctuation at the beginning or end of the word. For example, 
  hell's will be changed to heck's and !hell will be changed to !heck.
- The program will not censor hell with any other changes. For example, he!l, hell2, h3ll, 4hell,
  and he!ll will not be censored.
Parameters:
In: The character array StrCopy[]
Out: The character array StrCopy[] with all instances of the word hell 
     replaced with the word heck
Returns: Nothing
****************************************************************/
void SearchAndReplaceHell (char StrCopy[MAX_LENGTH])
{
	for (int i = 0; StrCopy[i]; ++i)
	{
		if (StrCopy[i] == ' ' && StrCopy[i + 1] == 'H' && StrCopy[i + 2] == 'E' 
			&& StrCopy[i + 3] == 'L' && StrCopy[i + 4] == 'L' && StrCopy[i + 5] == ' ')
		{
			StrCopy[i + 3] = 'c';
			StrCopy[i + 4] = 'k';
		}
	}
}

/**********************DeleteBlankStartEnd*********************
Action: This function deletes the extra spaces previously inserted by
InsertBlankStartEnd at StrCopy[0] and just before the null terminator
in the character array StrCopy[].
Parameters:
In: The character array StrCopy[]
Out: The character array StrCopy[] with the spaces at StrCopy[0] and just 
     before the null terminator at the end of the array deleted.
Returns: Nothing 
***************************************************************/
void DeleteBlankStartEnd (char StrCopy[MAX_LENGTH])
{
	int i;

	for (i = 0; StrCopy[i + 1]; ++i)
		StrCopy[i] = StrCopy[i + 1];

	StrCopy[i - 1] = 0;
}

/*******************OriginalCaseAndPunct************************************
Action: This function compares the original input entered by the user in the character
array Str[] with the censored input in the character array StrCopy[]. It makes sure all
alphabetic characters are the same case and inserts the punctuation in the correct places.
Parameters:
In: The original input entered by the user in the character array Str[] and the 
    censored input in the character array StrCopy[]
Out: The censored input in the character array StrCopy[] with the same case and punctuation
     as the original input in the character array Str[]
Returns: Nothing
***************************************************************************/
void OriginalCaseAndPunct (char Str[MAX_LENGTH], char StrCopy[MAX_LENGTH])
{
	for (int i = 0; Str[i]; ++i)
	{
		if (islower(Str[i]))
			StrCopy[i] = tolower(StrCopy[i]);

		else if (ispunct(Str[i]))
			StrCopy[i] = Str[i];
	}
}

/**********************DisplayResult*************************************
Action: This function displays the original input and the censored input in a 
formatted output.
Parameters:
In: The original input entered by the user in the character array Str[] and the 
    censored input in the character array StrCopy[]
Out: Nothing
Returns: Nothing
*************************************************************************/
void DisplayResult (char Str[MAX_LENGTH], char StrCopy[MAX_LENGTH])
{
	cout << endl << "Original : \"" << Str << "\"" << endl;
	cout << "Censored : \"" << StrCopy << "\"" << endl;
	
	for (int i = 0; i <= 75; ++i)
		cout << "-";

	cout << endl << endl;
}

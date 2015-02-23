//Kyle Stoltzfus
//C201 5:30 - 7:20
//9/7/2012
//Homework 1
//Homework1.cpp
//This program reads text from a file or as input from the keyboard
//and calculates how often words of a specific length occur. Finally,
//it displays the results of the calculations.

#include <iostream>
#include <ctype.h>
#include <iomanip>
using namespace std;

const int SIZE = 16;

int WordLength ();
float AverageWordLength (int []);
void DisplayResults (int [], float);

void main ()
{
	int Characters, WordSize [SIZE] = {0};
	float Average = 0;

	cout << "Enter some text. If using the keyboard be sure to" << endl
		<< "place a ^Z (Ctrl-Z) after the final character. " << endl;

	Characters = WordLength ();

	while (Characters)
	{
		++ WordSize [Characters];
		Characters = WordLength ();
	}

	Average = AverageWordLength (WordSize);

	DisplayResults (WordSize, Average);
}

/*********************WordLength**************************
Action: This function takes text from the input buffer or a text
file, reads one character at a time, and determines the number of characters 
in the word. Any word longer than 15 characters will be counted as a 15
character word.
Special Cases:
- Punctuation is never included in the character count of a word except for the
hyphen and apostrophe in special cases. As a result, any word with punctuation
in the middle that is not one of these special cases will be counted as two words.
For example, th!s would be counted as two words, one with two characters and one 
with one character.
- An apostrophe that is immediately followed by an alphanumeric character is 
included in the character count of a word.
- An apostrophe at the end of a word that is followed by punctuation or a whitespace
is not included in the character count of a word.
- Hyphens that are part of compound words connected by a hyphen are included in 
the character count of a word, and these compound words are counted as one word.
- Hyphens that are used to break words at the end of a line are not included in
the character count of a word, but these words are still counted as one word.
- Quotation marks and parentheses are never included in the character count of a word.
- Whitespaces are never included in the character count of a word. Whitespaces
are the space, newline, formfeed, return, tab, and vertical tab characters.
Parameters:
In: Nothing
Out: Nothing
Returns: The number of characters in the word.
*********************************************************/
int WordLength ()
{
	int NumberOfCharacters = 0, EndOfWord = 0;
	char ch;

	ch = cin.get();

	while (! cin.eof() && ! EndOfWord)
	{
		while (isspace(ch) || ispunct(ch))   //clears leading whitespaces and punctuation
			cin.get(ch);
		
		if (isalnum(ch))
			++ NumberOfCharacters;
			
		ch = cin.get();

		if (ch == '-' && cin.peek() == '\n')
		{
			ch = cin.get();
			ch = cin.get();  //ignores hyphen and newline characters
		}
	
		if (ch == '-')
			{
				++ NumberOfCharacters;
				ch = cin.get();
			}

		if (ch == 39 && isalnum(cin.peek()))  // ASCII code for ' (apostrophe) is 39
		{
			++ NumberOfCharacters;
			ch = cin.get();
		}
		
		if (isspace(ch) || ispunct(ch) || cin.eof())
			EndOfWord = 1;
	}
	
	if (NumberOfCharacters <= 15)    //makes sure the bounds of the array are not exceeded
		return NumberOfCharacters;
	
	else 
		return 15;
}


/**************AverageWordLength*****************
Action: This function determines the average word length in the 
text provided by the user.
Parameters: 
In: The array WordSize which contains the number of words of a specific 
length. For example, WordSize [2] = 5 means that the text contains 5 words
that are 2 characters in length.
Out: Nothing
Returns: The average word length of the sample text.
*************************************************/

float AverageWordLength (int WordSize [SIZE])
{
	float TotalLengthOfAllWords = 0, NumberOfWords = 0, Average;

	for (int i = 1; i < SIZE; ++ i)
	{
		NumberOfWords += WordSize [i];
		TotalLengthOfAllWords += (WordSize [i] * i);
	}

	if (NumberOfWords != 0)       //makes sure the program does not try to divide by 0 
	{
		Average = TotalLengthOfAllWords / NumberOfWords;
		return Average;
	}

	else
		return 0;
}

/****************DisplayResults***************************
Action: This function diplays the results from the previous two functions
in a formatted table.
Parameters:
In: The array WordSize which contains the number of words of a specific
length. The result of the AverageWordLenth function containing the average 
word length of the sample text.
Out: Nothing
Returns: Nothing
*********************************************************/

void DisplayResults (int WordSize [SIZE], float Average)
{
	cout << endl << left << setw(21) << "Word Length" << "Frequency" << endl;
	cout << setw(20) << "------------" << "----------" << endl;

	for (int i = 1; i < SIZE; ++ i)
		cout << setw(5) << " " << setw (2) << i << setw(17) << " " << WordSize [i] << endl;

	cout << endl << endl << "Average Word Length: " << Average << endl << endl;
}

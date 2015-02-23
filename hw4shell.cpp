/*******************************************************************
Author  :  Kyle Stoltzfus and Matt Holloway
Date    :  10/8/2012
Homework:  Homework 4
Compiler:  Microsoft Visual Studio 2010
Source  :  hw4shell.cpp
Action  :  Program will read in text and keeps track of the number of
           characters, words and lines from an external file. File name
           is the second argument in command line.  Main program also
           gives the user the ability to use command line input to program.
           This will tell program what to display, i.e. display the
           number of words only, or lines or all of them.
           example at command line if this file is called "hw4.cpp":

                  hw4  filename  /options

           possible options are
                    l  : liness
                    w  : words
                    c  :characters

   NOTE : This program will only run with command line input from external
          file given on the command line.  Cannot use keyboard input with
          this program.
*********************************************************************/
#include <iostream>
#include <ctype.h>
#include <string>
#include <fstream>
using namespace std;

struct CmdLineRecord
{
   enum { MAX_NAME_LENGTH = 32 };    // Max allowable filename chars
   int SyntaxError;                  // True if user syntax is incorrect
   int WantsLineCount;               // set to true if user wants line count
   int WantsWordCount;               // set to true if user wants word count
   int WantsCharCount;               // set to true if user wants char count
};

struct CountsRecord
{
   unsigned LineCount;          // number of lines
   unsigned WordCount;          // number of words
   unsigned CharCount;          // number of characters
};

void DetermineWhatUserWants(CmdLineRecord & User, int arg, char * arv[]);
int CountLineWordChar(CountsRecord & Data, char File[]);
void ReportResults(CmdLineRecord User, const CountsRecord & Data);


int main(int argc, char * argv[])
{
   CmdLineRecord User;
   CountsRecord Data;
   int FileOpened = 1;

   DetermineWhatUserWants(User, argc, argv);
   if (!User.SyntaxError)
      FileOpened = CountLineWordChar(Data, argv[1]);

   if (FileOpened)
      ReportResults(User, Data);
   else
     cerr << "Cannot open file " << argv[1];

   return 0;
}

/**************  DetermineWhatUserWants  ****************************
Action  :  Function will determine what the user wants to have displayed
           for the count, based on command line input, i.e. does user
           want to display how many lines or words or characters or
           combination of them, or if an input error occurred. Second
           argument in command line must be the file name the third argument
           is the option of display.

           Command line options are inputed after the "/" char and are:
                c : character count
                w : word count
                l : line count

           If no options are inputed then the default of display all count
           totals is done, otherwise the option is done.  One option or two
           is permitted after the "/", illegal character option will result
           in a syntax error.

Parameters:
  Reference  :
    U        : User variable of struct type given above
  Value
    arg      : number of command line arguments
    *arv[]   : array of pointers each pointing to different argument
Returns    : nothing
Preconditions : None
=======================================================================*/
void DetermineWhatUserWants(CmdLineRecord & U, int arg, char * arv[])
{

  U.SyntaxError = 0;
  U.WantsLineCount = 0;    //initialize all wants to zero to start
  U.WantsCharCount = 0;
  U.WantsWordCount = 0;

  if (arg < 2)
	  U.SyntaxError = 1;  //not enough arguments
  
  else if (arg > 3)
	  U.SyntaxError = 2;  //too many arguments

  else if (arg == 2)
  {
	  U.WantsLineCount = 1;
	  U.WantsCharCount = 1;
	  U.WantsWordCount = 1;
  }

  else  //arg == 3
  {
	  if (arv[2][0] != '/')
		  U.SyntaxError = 3;  // first element of third argument must be '/'

	  else if (arv[2][1])
	  {
		  for (int i = 1; arv[2][i]; ++i)
		  {
			  if (i > 3)
				  U.SyntaxError = 4;  //only three options are allowed in third argument
			  
			  else if (arv[2][i] == 'l' || arv[2][i] == 'L')
				  U.WantsLineCount = 1;

			  else if (arv[2][i] == 'c' || arv[2][i] == 'C')
				  U.WantsCharCount = 1;

			  else if (arv[2][i] == 'w' || arv[2][i] == 'W')
				  U.WantsWordCount = 1;

			  else
				  U.SyntaxError = 5;  //an option of the third argument is invalid
		  }
	  }

	  else
		  U.SyntaxError = 6;  //an option must be entered after the '/'
   }
}

/*********************  CountLineWordChar  *****************************
Action  :  Function will count the number of characters, words and lines
           in given input stream of text ended by control Z, ^Z, EOF

Parameters:
  Reference :
    Data    : variable of type struct given above
  Value
    File[]  : second command line argument that has the file to read from

Returns   : 1 if file opened, 0 if can not open file or not found

NOTE   :  Characters are everything, including newline and form feed.
          Words are delimited by whitespace characters and EOF.
          Does not take into consideration hypentation, words are composed
          numbers and letters, punctuation also included in words.

Precondition : none
=======================================================================*/
int CountLineWordChar(CountsRecord & Data, char File[])
{
   char ch;                  // current character in stream
   char NextCh;              // Next character in stream
   ifstream FileIn;          // declare FileIn to be input file

   Data.CharCount = 0;
   Data.WordCount = 0;
   Data.LineCount = 0;

   FileIn.open (File);

   if (FileIn.fail())
	   return 0;

   FileIn.get(ch);

   while (!FileIn.eof())
   {
	   FileIn.get(NextCh);

	   ++ Data.CharCount;

	   if (ch == '\n')
		   ++ Data.LineCount;

	   if (!isspace(ch) && isspace(NextCh) || !isspace(ch) && FileIn.eof())  //words are any set of characters separated by whitespaces
		   ++ Data.WordCount;                                                //second condition makes sure last word is counted

	   ch = NextCh;
   }

   if (Data.CharCount != 0)
	++ Data.LineCount;  //counts the last line of the file

   FileIn.close();

   return 1;
}

/**********************  ReportResults  ********************************
Action  :  Function will display the number of words, lines or characters
           or all of them depending on what the user entered on the command
           line input.
Parameters :
  Value    : 2 value parameters, User - what to display
                                 Data - holds the number to display
Returns    : nothing
======================================================================*/
void ReportResults(CmdLineRecord User, const CountsRecord & Data)
{
	if (User.SyntaxError > 0)
	{
		switch (User.SyntaxError)
		{
			case 1: cout << "Syntax Error: Not enough arguments. At least two arguments are required." << endl; break;
			case 2: cout << "Syntax Error: Too many arguments. Only three arguments are allowed." << endl; break;
			case 3: cout << "Syntax Error: The first element of the third argument must be a '/'." << endl; break;
			case 4: cout << "Syntax Error: Only three options are allowed in the third argument." << endl; break;
			case 5: cout << "Syntax Error: An option in the third argument is invalid. Valid options are l, c, w, L, C, W." << endl;break;
			case 6: cout << "Syntax Error: The '/' must be followed by at least one option." << endl;
		}
	}

	else 
	{
		if (User.WantsCharCount == 1)
			cout << "Number of Characters: " << Data.CharCount << endl;

		if (User.WantsLineCount == 1)
			cout << "Number of Lines: " << Data.LineCount << endl;

		if (User.WantsWordCount == 1) 
			cout << "Number of Words: " << Data.WordCount << endl;
	}
}


/*
Microsoft Windows [Version 6.1.7601]
Copyright (c) 2009 Microsoft Corporation.  All rights reserved.

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw4
Syntax Error: Not enough arguments. At least two arguments are required.

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw4 words
.1
Number of Characters: 12
Number of Lines: 1
Number of Words: 3

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw4 words
.1 /
Syntax Error: The '/' must be followed by at least one option.

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw4 words
.1 l
Syntax Error: The first element of the third argument must be a '/'.

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw4 words
.1 /lwcc
Syntax Error: Only three options are allowed in the third argument.

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw4 words
.1 /lx
Syntax Error: An option in the third argument is invalid. Valid options are l, c
, w, L, C, W.

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw4 words
.1 /lwc gld
Syntax Error: Too many arguments. Only three arguments are allowed.

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw4 words
.1 /l
Number of Lines: 1

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw4 words
.1 /lw
Number of Lines: 1
Number of Words: 3

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw4 words
.2
Number of Characters: 100
Number of Lines: 5
Number of Words: 16

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw4  word
s.3
Number of Characters: 0
Number of Lines: 0
Number of Words: 0

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw4 words
.4
Number of Characters: 355
Number of Lines: 6
Number of Words: 64

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw4 words
.5
Number of Characters: 23
Number of Lines: 3
Number of Words: 3

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw4 words
.5 /lwc
Number of Characters: 23
Number of Lines: 3
Number of Words: 3
*/
/**********************************************************************

 PROGRAMMER : Kyle Stoltzfus
 CLASS		: C201 5:30 - 7:20
 DATE       : 11/12/2012
 HOMEWORK	: Homework 7
 COMPILER   :  Visual C++ .NET
 SOURCE FILE:  Assign7.cpp

 ACTION:     Reads words from stdin and displays them in 3 columns.
             A word is defined in the overloaded >> operator in the
			 String class as any sequence of characters that are delimited
			 by white spaces. Reading from stdin input need to manual enter end of 
             file marker, ctrl-Z then enter.

 NOTES :     The program does not handle correctly words longer than
             MAX_LENGTH, a constant defined in the String class definition. 
			 If such words are encountered, they are truncated.

             Only as many as MAX_WORD_COUNT words can be stored in the
             array holding the words.

=====================================================================*/

#include <iostream>
#include <iomanip>
#include <ctype.h>
#include "string2.cpp"
using namespace std;

void WriteWords (String  Word[],
                 int     Count[],
                 int     TotalWordCount,
                 int     DistinctWordCount);

void StoreWord (String  NewWord,
                String  Word[],
                int     Count[],
                int    &TotalWordCount,
                int    &DistinctWordCount,
                int     MaxWordCount);

/***************************  main  ***********************************/

void main()
{
  const  int MAX_WORD_COUNT  = 130;

  String  NewWord,
          Word[MAX_WORD_COUNT + 1] = {"", ""};       // ALWAYS allow 1 extra slot!

  int     Count[MAX_WORD_COUNT + 1] ={0}, // Initialize array to zeros
          DistinctWordCount = 0,
          TotalWordCount = 0;

  cin >> NewWord;  //  Get the first word
 
  while ( NewWord.Length() != 0 )            //  While NewWord is not null string
    {
    StoreWord (NewWord, Word, Count, TotalWordCount,
               DistinctWordCount, MAX_WORD_COUNT);

    cin >> NewWord;             //  Get the next word
    }

  WriteWords(Word, Count, TotalWordCount, DistinctWordCount);

}

/***************************  StoreWord   ********************************

DESCRIPTION  Adds a variable of String class called NewWord (holding up to MAX_WORD_LENGTH
             characters) to the end of the array Word.

PARAMETERS   NewWord            The variable of String class to be added
             Word               An array of variables of String class
             DistinctWordCount  The number of different words in the array
             TotalWordCount     The total number of word in the file
             MaxWordCount       The max number of words that can be stored
                                in the array Word. If DistinctWordCount ==
                                MaxWordCount, the function is exited.

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void StoreWord (String  NewWord,
                String  Word[],
                int     Count[],
                int    &TotalWordCount,
                int    &DistinctWordCount,
                int     MaxWordCount)
{
  int i, k = 0;

  while ( Word[k] < NewWord && k < DistinctWordCount )
    ++k;

  // Assert:  k is NewWord's correct position in the ordered array Word

  if ( NewWord == Word[k] )   // NewWord is already there
    {
    ++Count[k];
    ++TotalWordCount;
    }

  else if ( DistinctWordCount < MaxWordCount ) // Room for a new word
    {
    ++DistinctWordCount;  // If this line reached, found new word
    ++TotalWordCount;

    for ( i = DistinctWordCount-1;  i > k;  --i ) // Make room for
      {                                             //  NewWord
      Word[i] = Word[i-1];
      Count[i] = Count[i-1];
      }
    Word[k] = NewWord; // Store NewWord in array
    Count[k] = 1;
    }
}

/***************************  WriteWords   ********************************

DESCRIPTION  Writes the variables of String class in the array Word to standard output.
             The words are left justified. After WORDS_PER_ROW words have
             been written a new line is started.

PARAMETERS   Word       An array of variables of String class
             WordCount  The number of words in the array

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void WriteWords (String  Word[],
                 int     Count[],
                 int     TotalWordCount,
                 int     DistinctWordCount)
{
  const char *Header1   = "    Word          Count | ",
             *Header2   = "                        | ",
             *Separator = "   | ";

  const int WORD_FW       = 17,
        COUNT_FW      = 4,
        WORDS_PER_ROW = 3;

  int C;

  cout << "\n\n";

  if ( TotalWordCount == 0 )
    return;

  for ( C = 1; C <= WORDS_PER_ROW;  ++C )
    cout << Header1;
  cout << endl;

  for ( C = 1; C <= WORDS_PER_ROW; ++C )
    cout << Header2;
  cout << endl;

  int N = 0;

  while ( N < DistinctWordCount )
  {
    for ( C = 1; C <= WORDS_PER_ROW && N < DistinctWordCount; ++C )
    {
      cout << setiosflags(ios::left)  << setw(WORD_FW) << Word[N];
      cout << setiosflags(ios::right) << setw(COUNT_FW)<< Count[N];
      cout << Separator;
      cout << resetiosflags(ios::right);
      ++N;
     }
    cout << endl;
   }

  cout << "\nTotal    Word Count : " << TotalWordCount    << endl;
  cout << "\nDistinct Word Count : " << DistinctWordCount << endl;
}

/*Microsoft Windows [Version 6.1.7601]
Copyright (c) 2009 Microsoft Corporation.  All rights reserved.

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw7 < wor
ds.1


    Word          Count |     Word          Count |     Word          Count |
                        |                         |                         |
This                1   | fun!                1   | is                  1   |

Total    Word Count : 3

Distinct Word Count : 3

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw7 < wor
ds.2


    Word          Count |     Word          Count |     Word          Count |
                        |                         |                         |
(219)               1   | -                   1   | 10000000000000005   1   |
123456789123456     1   | 237                 1   | 4496.               1   |
My                  1   | Two                 1   | are                 1   |
as                  1   | fol-                1   | is                  1   |
large               1   | lows,               1   | number              1   |
numbers             1   |

Total    Word Count : 16

Distinct Word Count : 16

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw7 < wor
ds.3



C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw7 < wor
ds.4


    Word          Count |     Word          Count |     Word          Count |
                        |                         |                         |
All                 1   | As                  1   | Dick                1   |
Dick,               1   | Did                 1   | Jane                1   |
Jane,               1   | Spot                1   | Spot's              1   |
Spot?               1   | a                   5   | account             1   |
after.              1   | ago,                1   | altered             1   |
and                 1   | away                1   | brokerage           1   |
but                 1   | computer            1   | end.                1   |
engineer            1   | ever                2   | executive           1   |
expect,             1   | few                 1   | firm.               1   |
for                 2   | happened            1   | happily             1   |
happy               1   | he                  1   | his                 1   |
is                  2   | large               1   | lived               1   |
major               1   | might               1   | never               1   |
of                  1   | passed              1   | personality.        1   |
pleasant            1   | senior              1   | success             1   |
the                 1   | they                1   | to                  2   |
top                 1   | vendor.             1   | was                 1   |
what                1   | wonder              1   | years               1   |
you                 2   |

Total    Word Count : 64

Distinct Word Count : 55

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>hw7 < wor
ds.5


    Word          Count |     Word          Count |     Word          Count |
                        |                         |                         |
!!wishy-washy!!     1   | hy-                 1   | pen                 1   |

Total    Word Count : 3

Distinct Word Count : 3

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>*/
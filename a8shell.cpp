/*************************************************************************

   AUTHOR  :                   (with John Russo and modified some
                                     by Matt Holloway)

   SOURCE  :
              with the help from shell program a8shell.cpp

   DATE    :

   COMPILER: Visual C++ .NET

   ACTION  : The program tests routines designed to perform various
             operations on singly linked lists. The lists have a
             dummy head node that holds the "Happy Face" character. 
             The tail of the lists points to NULL.

*************************************************************************/
#include <iostream>
#include <ctype.h>
#include <new>
#include <process.h>        //  Needed for call to exit
using namespace std;

struct Node
{
  enum  { DUMMY_VALUE = 1 };  //  Value () stored in dummy head node.
  char  Ch;                   //  Holds the char data.
  Node *Link;                 //  Points to another struct of type Node.
};

typedef Node* NodePtr;

void AbortProgram (void);

void AddNode (char NewChar,  NodePtr List);

void BuildList (NodePtr List);

void ZapList (NodePtr P);

void DeleteNode (char CharToDelete, NodePtr List, int &CharFound);

void StartList (NodePtr &List);

void ShowList (NodePtr List);

void DisplayMenuAndGetMenuChoice (char &MenuChoice);

void TestAddNode (NodePtr List);

void TestBuildList (NodePtr List);

void TestDeleteNode (NodePtr List);

void TestZapList (NodePtr List);
/*****************************  main   ********************************/

int main(void)
{
  NodePtr List = NULL;

  char MenuChoice;

  system("cls");
  cout << "This program allows you to test the routines needed \n"
          "for homework 8. \n\n";

  StartList(List);
  if (List == NULL)                        //  Unexpected error.
    AbortProgram ();

  do
  {
    DisplayMenuAndGetMenuChoice(MenuChoice);

    switch( MenuChoice )
    {
      case 'Q':  break;                // Exit program

      case 'B':  TestBuildList(List);
                 break;

      case 'A':  TestAddNode(List);
                 break;

      case 'D':  TestDeleteNode(List);
                 break;

      case 'Z':  TestZapList(List);
                 break;

      default :  cout << "\nError: '" << MenuChoice
                      << "' is not an option \n\n";
    }
   }
  while ( MenuChoice != 'Q' );

  return 0;
}

/*********************   DisplayMenuAndGetMenuChoice *********************
   Displays a menu of options and reads the user's choice into the
   parameter MenuChoice. Unbuffered input is used, so the user does
   not have to enter a newline character after typing a menu choice.
   The MenuChoice is upcased.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void DisplayMenuAndGetMenuChoice (char &MenuChoice)
{
  char* Option[] = {"B(uildList", "A(ddNode", "D(eleteNode",
                    " Z(apList", "Q(uit", "" };

  char DottedLine[] ="\n- - - - - - - - - - - - - - - "
                     "- - - - - - - - - - - - - - - -\n ";
  int K = 0;

  cout << DottedLine;

  while ( Option[K][0] != 0 )  // while we haven't gotten to ""
  {
    cout << Option[K];         // Display menu option
    cout << "  ";              // Add some white space.
    ++K;
  }

  cout << "=> ";
  MenuChoice = toupper(cin.get());
  cin.ignore(10,'\n');

  cout <<  DottedLine;
}

/************************    TestAddNode  ********************************
   Facilitates the testing of the function AddNode, a function which
   adds a node to the tail end of a linked list. If the enter key is
   pressed in response to the prompt, it is assumed that the user
   wants to exit and this function is aborted.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestAddNode (NodePtr List)
{
  char NewChar;

  cout << "\n\n----------------   Testing AddNode   -------------------\n\n";

  cout << "Character to be added? ";
  NewChar = cin.get();
  cin.ignore();

  if (NewChar == '\n')  // User pressed just enter key.
  {
    cout << "Aborting AddNode...";
    return;
  }

  cout << NewChar;
  cout << " --  Adding \'" << NewChar  << "\'";

  AddNode (NewChar, List);

  cout << "\n\nThe new list: ";
  ShowList(List);
}

/*************************    TestBuildList     **************************
   Facilitates the testing of the function BuildList, which is supposed
   to build an ordered linked list of characters.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestBuildList (NodePtr List)
{
  cout << "\n\n=================  Testing BuildList  ===================";
  cout << "\n\nType the characters for the list -  "
           "when finished, press enter key\n\n ->";

  BuildList(List);

  cout << "\n\nAfter BuildList, List = ";
  ShowList(List);
}

/***********************    TestDeleteNode   *****************************
   Facilitates the testing of DeleteNode, a function which is supposed
   to delete characters from a linked list.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestDeleteNode (NodePtr List)
{
  int  CharFound;
  char CharToBeDeleted;

  cout << "\n\n*****************   Testing DeleteNode   *******************";

  cout << "\n\nCharacter to be deleted? ";
  CharToBeDeleted = cin.get();
  cin.ignore();

  DeleteNode (CharToBeDeleted, List, CharFound);

  if ( CharFound )
    cout << "\n\n'" << CharToBeDeleted << "' has been deleted,";
  else
    cout << "\n\n'" << CharToBeDeleted << "' was not in the list,";

  cout << "\n\nList = ";
  ShowList(List);
}

/***********************    TestZapList  *********************************
   Facilitates the testing of ZapList, a function that is supposed to
   return all storage allocated for a linked list to the heap (except the
   storage occupied by the dummy head node.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void TestZapList (NodePtr List)
{
  cout << "\n\n^^^^^^^^^^^^^^^^^   Calling ZapList  ^^^^^^^^^^^^^^^^^^^^^^^";

  ZapList(List);

  cout << "\n\nList = ";
  ShowList(List);
}

/****************************  AbortProgram   ****************************
   Displays an error message and returns a non-zero error code to
   the operating system.

   Requires exit function prototyped in process.h.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void AbortProgram (void)
{
  cout << "\n\n\a A error has occurred while using the new operator. \n"
          "Returning to the operating system\n";
  cout << "Press ENTER key to continue: ";
  cin.get();
  exit(1);
}

/************************    StartList  *********************************
  DESCRIPTION   Creates an empty list, i.e. a singly linked list that
                contains only a dummy head node.

  PARAMETER

    OUT, List   A pointer to the head node of the list. If the
                dynamic memory allocation is unsuccessful, List will
                hold NULL on exit.

  PRECONDITION  List points to NULL. If List points to an actual node,
                calling this routine will create inaccessable memory.
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void StartList (NodePtr &List)
{
  List = new(nothrow) Node;
  if (List == NULL)
    return;                        // Memory allocation error.

  List->Ch   = List->DUMMY_VALUE;  // Fill in dummy head node fields
  List->Link = NULL;               // Initialize end of list.
}

/*************************   ShowList  ***********************************
  DESCRIPTION  Displays the character field of all of the nodes in List, a
               singly linked list with a dummy head node. The list is
               enclosed in quotes.

               The constant MAX_CHARS_PER_LINE controls the maximum
               number of characters displayed before a newline char
               is displayed.

  PARAMETER

    IN, List   A pointer to a singly linked list with a dummy head node.

  NOTE         To facilitate debugging this routine displays "NULL"
               if called with List == NULL.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void ShowList (NodePtr List)
{
  const int MAX_CHARS_PER_LINE = 50;

  int CharCount = 0;

  if ( List == NULL )
  {
    cout << " NULL LIST\n\n";
    return;
  }

  cout << "\"";                 //  Display quote for ease of testing.
  while ( List->Link != NULL )
  {
    List = List->Link;
    cout << List->Ch;
    if ( List-> Ch != '\n' )   // Increment CharCount unless newline
      ++CharCount;             //   char is encountered in List
    else
      CharCount = 0;
    if ( CharCount % MAX_CHARS_PER_LINE == 0 )
      cout << "\n     ";
  }

  cout << "\"\n\n";
}

/*****************************   ZapList  ********************************
  DESCRIPTION  Frees all the storage space currently occupied by the
               linked list pointed to by List. Does NOT delete the delete
               the dummy head node.

  PARAMETER

    OUT, List  A pointer to a singly linked list with a dummy head node.
               After this call, List will contain only the dummy head node.

  PRECONDITION List must point to a linked list that has a dummy head node
               and a tail node that points at NULL.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void ZapList (NodePtr List)
{
  NodePtr Temp;

  while (List -> Link != NULL)  //keeps looping until Link in the dummy 
  {                             //head node points to NULL     
	  
	  Temp = List -> Link;      //Temp points to Node to be deleted
	  List -> Link = Temp -> Link;  //List -> Link points to the Node after the one being deleted
	  delete Temp;                  //Node is deleted
  }
}


/****************************   AddNode  *********************************
  DESCRIPTION  Adds a node containing NewChar to the end of List.

  PARAMETERS

    IN, NewChar The character to be added to the end of the list.

    IN, List    A pointer to a singly linked list with a dummy head node.
                The value of List (address of dummy head node) is not
                changed by this routine, so List is passed by value.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void AddNode (char NewChar, NodePtr List)
{
   NodePtr NewNode = List;  //make NewNode point to List

   while (NewNode -> Link != NULL)     //find end of linked list
	   NewNode = NewNode -> Link;     

   NewNode -> Link = new (nothrow) Node;  //create a new Node at the end of the list

   if (NewNode -> Link == NULL)  //make sure Node was created
	   return;

   NewNode = NewNode -> Link;  //make NewNode point to the Node just created
   NewNode -> Ch = NewChar;    //fill Ch part of NewNode
   NewNode -> Link = NULL;     //make sure the list ends with NULL
}

/****************************    DeleteNode   ****************************
  DESCRIPTION  Deletes the first node of List that contains the char
               CharToDelete. The storage occupied by the deleted
               node is returned to the heap.

  PARAMETERS

    IN, CharToDelete  The character to be deleted.

    IN, List    A pointer to a singly linked list with a dummy head node.
                The value of List is not changed by this routine but the
                linked list itself is changed.

    OUT, CharFound Set to 1 if the CharToDelete is found and deleted and
         0 otherwise.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void DeleteNode (char CharToDelete, NodePtr List, int &CharFound)
{
  NodePtr NodeToBeDeleted;

  if (List -> Link == NULL)  //makes sure List is not empty
	  CharFound = 0;

  else
  {
	while (List -> Link -> Ch != CharToDelete && List -> Link -> Link != NULL)
		List = List -> Link;  //search through list until the CharToDelete is found or
                            //the end of the List is reached
	 if (List -> Link -> Ch == CharToDelete) //CharToDelete is in List
	{
		CharFound = 1;
		NodeToBeDeleted = List -> Link;  //NodeToBeDeleted points to Node containing CharToDelete
		List -> Link = NodeToBeDeleted -> Link;  //Node before NodeToBeDeleted now points to
	                                           //the Node after NodeToBeDeleted
		delete NodeToBeDeleted;  //Node containing CharToDelete is deleted
	}

	else  //CharToDelete is not in List
		  CharFound = 0;
  }
}

/****************************   BuildList    *****************************
  DESCRIPTION   Builds a singly linked list with a dummy head node. The
                characters in the list are in the same order in which the
                user enters them, i.e. new characters are added to the tail
                end of the list.

                Input terminates when the enter key is pressed.

  PARAMETERS

    IN, List    A pointer to a singly linked list with a dummy head node.
                It is imperative that List be initialized before calling
                this routine.

  NOTE          Before building the new list, ZapList is called. This
                ensures that a memory leak does not develop.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void BuildList (NodePtr List)
{
  ZapList(List); //makes sure List is empty

  char NewChar;

  cin.get(NewChar);

  while (NewChar != '\n')
  {
	  List -> Link = new (nothrow) Node;  //create a new Node

	  if (List -> Link == NULL)  //make sure Node was created
		  return;

	  List = List -> Link;  //List points to the new Node
	  List -> Ch = NewChar;  //fill Ch part of new Node
	  List -> Link = NULL;  //make sure the List ends with NULL
	  cin.get(NewChar);
  }
}

/*This program allows you to test the routines needed
for homework 8.


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => b

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


=================  Testing BuildList  ===================

Type the characters for the list -  when finished, press enter key

 ->abc123


After BuildList, List = "abc123"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => b

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


=================  Testing BuildList  ===================

Type the characters for the list -  when finished, press enter key

 ->f


After BuildList, List = "f"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => b

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


=================  Testing BuildList  ===================

Type the characters for the list -  when finished, press enter key

 ->


After BuildList, List = ""


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => a

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


----------------   Testing AddNode   -------------------

Character to be added? n
n --  Adding 'n'

The new list: "n"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => a

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


----------------   Testing AddNode   -------------------

Character to be added? j
j --  Adding 'j'

The new list: "nj"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => a

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


----------------   Testing AddNode   -------------------

Character to be added? y
y --  Adding 'y'

The new list: "njy"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => d

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


*****************   Testing DeleteNode   *******************

Character to be deleted? y


'y' has been deleted,

List = "nj"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => d

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


*****************   Testing DeleteNode   *******************

Character to be deleted? r


'r' was not in the list,

List = "nj"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => d

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


*****************   Testing DeleteNode   *******************

Character to be deleted? n


'n' has been deleted,

List = "j"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => d

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


*****************   Testing DeleteNode   *******************

Character to be deleted? j


'j' has been deleted,

List = ""


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => d

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


*****************   Testing DeleteNode   *******************

Character to be deleted? w


'w' was not in the list,

List = ""


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => b

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


=================  Testing BuildList  ===================

Type the characters for the list -  when finished, press enter key

 ->abcc1234


After BuildList, List = "abcc1234"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => d

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


*****************   Testing DeleteNode   *******************

Character to be deleted? 1


'1' has been deleted,

List = "abcc234"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => d

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


*****************   Testing DeleteNode   *******************

Character to be deleted? c


'c' has been deleted,

List = "abc234"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => z

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


^^^^^^^^^^^^^^^^^   Calling ZapList  ^^^^^^^^^^^^^^^^^^^^^^^

List = ""


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => z

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


^^^^^^^^^^^^^^^^^   Calling ZapList  ^^^^^^^^^^^^^^^^^^^^^^^

List = ""


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => b

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


=================  Testing BuildList  ===================

Type the characters for the list -  when finished, press enter key

 ->1


After BuildList, List = "1"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => z

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


^^^^^^^^^^^^^^^^^   Calling ZapList  ^^^^^^^^^^^^^^^^^^^^^^^

List = ""


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  Q(uit  => */
/*************************************************************************

   AUTHOR  : Kyle Stoltzfus (with John Russo and modified some
								by Matt Holloway)
   CLASS   : 5:30 - 7:20

   HOMEWORK: Homework #8
   
   SOURCE  : hw8.cpp
              with the help from shell program a8shell.cpp

   DATE    : 11/19/2012

   COMPILER: Visual C++ .NET

   ACTION  : The program tests routines designed to perform various
             operations on singly linked lists. The lists have a
             dummy head node that holds the "Happy Face" character. 
             The tail of the lists points to NULL.

*************************************************************************/

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
/*************************************************************************

   AUTHOR  : Kyle Stoltzfus and John Russo and some by Matt Holloway

   CLASS   : 5:30 - 7:20

   HOMEWORK: Homework #9

   SOURCE  :  hw9.cpp
              with the help from shell program a9shell.cpp

   DATE    : 11/28/2012

   COMPILER: Microsoft Visual C++ .NET

   ACTION  : The program tests routines designed to perform various
             operations on singly linked lists. The lists have a
             dummy head node that holds the  character. The tail of
             the lists points to NULL.

             This is an extended program of homework #8
             The menu choices also all reading in a list from an
             external file and sorting a list.

*************************************************************************/

/****************************   ReadList    *****************************

  DESCRIPTION   Builds a singly linked list with a dummy head node. The
                characters in the list are read in from an external file
                in the same order in which they are found in file.

                Input to list terminates when the End of File is encountered

  PARAMETERS

    IN, List    A pointer to a singly linked list with a dummy head node.
                It is imperative that List be initialized before calling
                this routine.

    IN, FileName  A pointer to a string that has the name of the file to
                  open, if error in opening then return a 1;

  RETURNS      1 if file opening error, 0 if read from file successful

  NOTE          Before building the new list, ZapList is called. This
                ensures that a memory leak does not develop.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
int ReadList (NodePtr List,char FileName[])
{
	char ch;
	ifstream indata;              //declare file variable to read from
	
	ZapList(List);                     //make sure list is empty

	indata.open(FileName);  //open file to read from

	if (indata.fail())  //make sure file opened
		return 1;

	indata.get(ch);  //get first character from file

	while (indata.good() && !indata.eof())  //loops until error in reading data or 
										    //end of file is found
	{
		List -> Link = new (nothrow) Node;  //create a new Node at the end of List

		if (List-> Link == NULL)  //makes sure new Node was created
			AbortProgram();

		List = List -> Link; //point List at the new Node
		List -> Ch = ch;     //fill Ch value of Node with char from file
		List -> Link = NULL; //make sure List ends with NULL
		indata.get(ch);      //get next char from file
	}

	indata.close();  //close data file

	return 0; 
}

/**************************  SortList ************************************

Description  Arranges the singly linked list pointed to by List in
             natural order.  It is assumed that the list has a dummy
             head node.

             The algorithm used is a linked variation of the selection
             sort and works like this:
             Start with EndSorted aimed at first node of list

             repeat
               Find smallest char between EndSorted and end of list
               Swap smallest element with char in EndSorted
               Change EndSorted to next node
             until we get to end of list

             None of the pointers in linked list are changed

Parameters
  IN, List  A pointer to a singly linked list with a dummy head node
-----------------------------------------------------------------------*/
void SortList(NodePtr List)
{
	NodePtr SmallNode;        //points to smallest char
	NodePtr SearchNode;       //used to search each node in list
	NodePtr EndSorted;       //points to list to sort
	char TempCh;

	if (List -> Link != NULL) //List is not empty
		EndSorted = List -> Link; //make EndSorted point to the beginning of List
	else  //List is empty
		EndSorted = List; //EndSorted points to dummy head Node and the following loop 
	                      //will never execute
	while (EndSorted -> Link != NULL) //make sure EndSorted is not at the end of List
	{
		SmallNode = EndSorted;  //give SmallNode a starting value
		SearchNode = EndSorted -> Link; //make SearchNode point to the Node after EndSorted

		while (SearchNode != NULL) //make sure SearchNode is not at the end of List
		{
			if (SearchNode -> Ch < SmallNode -> Ch) //check the Ch value of the two Nodes
				SmallNode = SearchNode; //if SearchNode -> Ch is smaller then SmallNode -> Ch
			                            //make SmallNode point to SearchNode
			SearchNode = SearchNode -> Link; //advance SearchNode to the next Node
		}

		TempCh = EndSorted -> Ch; //place the Ch value in EndSorted in TempCh
		EndSorted -> Ch = SmallNode -> Ch; //swap SmallNode -> Ch with EndSorted -> Ch
		//This places the smallest unsorted value in List at the beginning
		SmallNode -> Ch = TempCh;
		EndSorted = EndSorted -> Link; //advance EndSorted to the next Node
	}
}

/*This program allows you to test the routines needed
for homework #9.


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => b


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


=================  Testing BuildList  ===================

Type the characters for the list -  when finished, press enter key

 ->fdjklgd4586


After BuildList, List = "fdjklgd4586"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => s


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


^^^^^^^^^^^^^^^^   Calling SortList  ^^^^^^^^^^^^^^^^^^^^^^^

List = "4568ddfgjkl"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => z


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


^^^^^^^^^^^^^^^^^   Calling ZapList  ^^^^^^^^^^^^^^^^^^^^^^^

List = ""


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => s


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


^^^^^^^^^^^^^^^^   Calling SortList  ^^^^^^^^^^^^^^^^^^^^^^^

List = ""


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => b


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


=================  Testing BuildList  ===================

Type the characters for the list -  when finished, press enter key

 ->178439


After BuildList, List = "178439"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => s


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


^^^^^^^^^^^^^^^^   Calling SortList  ^^^^^^^^^^^^^^^^^^^^^^^

List = "134789"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => b


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


=================  Testing BuildList  ===================

Type the characters for the list -  when finished, press enter key

 ->9456721


After BuildList, List = "9456721"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => s


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


^^^^^^^^^^^^^^^^   Calling SortList  ^^^^^^^^^^^^^^^^^^^^^^^

List = "1245679"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => b


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


=================  Testing BuildList  ===================

Type the characters for the list -  when finished, press enter key

 ->1573521389359


After BuildList, List = "1573521389359"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => s


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


^^^^^^^^^^^^^^^^   Calling SortList  ^^^^^^^^^^^^^^^^^^^^^^^

List = "1123335557899"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => b


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


=================  Testing BuildList  ===================

Type the characters for the list -  when finished, press enter key

 ->9546921451


After BuildList, List = "9546921451"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => s


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


^^^^^^^^^^^^^^^^   Calling SortList  ^^^^^^^^^^^^^^^^^^^^^^^

List = "1124455699"


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  =>

 This program allows you to test the routines needed
for homework #9.


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => r


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


----------------  Testing ReadList  -------------------

Please enter the file to read from? words.1


The list created from the file -- words.1 --

"This is fun!"



- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => r


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


----------------  Testing ReadList  -------------------

Please enter the file to read from? words.2


The list created from the file -- words.2 --

"My number is as fol-

lows, (219) 237 - 4496.

Two large numbers are

123456789123456

10000000000000005"



- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => r


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


----------------  Testing ReadList  -------------------

Please enter the file to read from? words.3


The list created from the file -- words.3 --

""



- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => r


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


----------------  Testing ReadList  -------------------

Please enter the file to read from? words.4


The list created from the file -- words.4 --

"Did you ever wonder what happened to Dick, Jane, a
nd Spot?  As you

might expect, they lived happily ever after.  Jane
 is a top account

executive for a large brokerage firm.  Dick is a s
enior engineer for

a major computer vendor.  Spot passed away a few y
ears ago, but he

was happy to the end.  All of his success never al
tered Spot's

pleasant personality."



- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => r


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


----------------  Testing ReadList  -------------------

Please enter the file to read from? words.5


The list created from the file -- words.5 --

"hy-

pen

!!wishy-washy!!"



- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 B(uildList  A(ddNode  D(eleteNode   Z(apList  R(eadList  S(ortList  Q(uit  => q


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

C:\Users\Kyle\Documents\Visual Studio 2010\C201 Finished and Test Data>*/

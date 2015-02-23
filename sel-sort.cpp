/************************  Swap  *****************************************

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
void SelectionSort (int List[], int  Last)
{
  int i, Start, SubSmall;

  for ( Start = 1; Start < Last; ++Start )   // Sort items 1..Last
    {
    SubSmall = Start;                        //  subscript of smallest elt.

    for ( i = Start + 1; i <= Last; i++ )    //  Find subscript of smallest
      if ( List[i] < List[SubSmall] )        //   elt. in tail end of array
        SubSmall= i;

    Swap(List[SubSmall],  List[Start]);      // Place in correct position
    }
}
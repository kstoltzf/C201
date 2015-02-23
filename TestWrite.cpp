#include <iostream>
#include "MyFloat.cpp"
using namespace std;

void AssignValue (MyFloat &X)
{
	X.Number[0] = '1';
	X.Number[1] = '2';
	X.Number[2] = '3';
	X.NumberOfDigits = 0;
}

void main()
{
	MyFloat X;

	AssignValue(X);

	cout << "X = ";
	X.Write();
	cout << endl << "Press Enter key to continue";
	cin.ignore();
}
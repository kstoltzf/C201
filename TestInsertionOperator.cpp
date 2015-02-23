#include <iostream>
#include "MyFloat2.cpp"
using namespace std;

void AssignValue (MyFloat &X)
{
	X.Number[0] = '1';
	X.Number[1] = '2';
	X.Number[2] = '3';
	X.Number[3] = 0;
	X.NumberOfDigits = 3;
}

void main()
{
	MyFloat X;

	AssignValue(X);

	cout << "X =" << X;
	cout << endl << "Press Enter key to continue";
	cin.ignore();
}
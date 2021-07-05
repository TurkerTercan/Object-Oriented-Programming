//*************			TURKER		TERCAN		171044032		HW4		CSE241	OOP				 *************//

//This is my test functions for gtuset and gtuvector classes

#include "gtuset.h"
#include "gtuvector.h"
#include "gtuset.cpp"
#include "gtuvector.cpp"
#include <iostream>

using namespace std;
using namespace TurkerTercanHW6;

//I defined these two global functions for testing find_if and for_each functions to use.
bool equaltoA(const int& temp)
{
	if( temp == 'A' )
		return true;
	return false;
}

void square( int& temp)
{
	temp *= temp;
}

int main()
{
	GTUSet<int> testset_int;
	cout << "Testing for set class.. It will throw an exception because trying to insert same elements" << endl;
	try
	{
		testset_int.insert(1);		//Inserting elements for set
		testset_int.insert(2);
		testset_int.insert(3);
		testset_int.insert(4);
		testset_int.insert(5);
		testset_int.insert(6);
		testset_int.insert(2);		//It will throw an exception
		testset_int.insert(7);
	}
	catch(const exception& e)
	{
		cout << e.what() << endl;	//Catch the exception
	}
	
	for(auto p = testset_int.cbegin(); p != testset_int.cend(); p++)	//Print testset_int
		cout << *p << " ";
	cout << endl;

	cout << "Testing for vector class.." << endl;
	GTUVector<char> testvector;
	
	testvector.insert('T');		//Inserting elements for GTUVector class
	testvector.insert('U');
	testvector.insert('R');
	testvector.insert('K');
	testvector.insert('E');
	testvector.insert('R');
	testvector.insert(' ');
	testvector.insert('T');
	testvector.insert('E');
	testvector.insert('R');
	testvector.insert('C');
	testvector.insert('A');
	testvector.insert('N');
	testvector.insert(' ');
	testvector.insert('H');
	testvector.insert('W');
	testvector.insert('6');
	
	
	for(auto p = testvector.cbegin(); p != testvector.cend(); p++)		//Printing vector class
		cout << *p;
	cout << endl;

	cout << "Testing [] operator for GTUVector (testvector[3])" << endl;
	cout << testvector[3] << endl;

	cout << "Testing find function for set(it will return the iterator that it points int 4)" << endl;
	auto testfind = find(testset_int.begin(), testset_int.end(), 4);	//Find the element
	cout << *testfind << endl;
	
	cout << "Testing find_if for vector(it will return the char value that is equals to 'A')" << endl;
	auto testfind_if = find_if(testvector.begin(), testvector.end(), equaltoA);		//Find the element which is true by given function
	cout << *testfind_if << endl;
	
	cout << "Testind for_each function for set(it will square all values)" << endl;
	for_each(testset_int.begin(), testset_int.end(), square);			//Apply the given function to all elements in that container
	
	cout << "After for_each" << endl;
	for(auto p = testset_int.cbegin(); p != testset_int.cend(); p++)
		cout << *p << " ";
	cout << endl;
	
	cout << "Deleting third position in vector" << endl;
	GTUIterator<char> test_delete = testvector.begin() + 2;		//Go to the iterator to third element in container
	testvector.erase(test_delete);								//Erase the element
	
	for(auto p = testvector.cbegin(); p != testvector.cend(); p++)
		cout << *p ;
	cout << endl;

	cout << "Clearing all data in set" << endl;
	testset_int.clear();		//Clear all data
	if(testset_int.empty())		//Check is empty
		cout << "testset_int is empty" << endl;
	else
		cout << "testset_int is not empty" << endl;
		
	return 0;
}

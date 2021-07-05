//*************			TURKER		TERCAN		171044032		HW4		CSE241	OOP				 *************//


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BoardVector.h"
#include "BoardArray2D.h"
#include "BoardArray1D.h"

using namespace TurkerTercanHW5;
using namespace std;

int main(){
	AbstractBoard *temp;
	vector<AbstractBoard*> boards;
	bool boardVec = false, board1D = false, board2D = false;
	ifstream infile;
	ofstream outfile;
	string fileName;
	int size = -1, width = -1;
	bool check = false;
	bool goBack = true;
	int choice;
	char ch;
	while( !check )
	{
		cout << "Welcome to the board game" << endl;
		while(size < 0)
		{
			cout << "Enter your board's size: ";
			cin >> size;
			if(size < 0)
				cout << "Size can not be non positive integer" << endl;
		}
		while(width < 0)
		{
			cout << "Enter your board's width: ";
			cin >> width;
			if(width < 0)
				cout << "Width can not be non positive integer" << endl;
		}
		cout << "1- Create BoardVector" << endl 
		<< "2- Create BoardArray2D" << endl 
		<< "3- Create BoardArray1D" << endl;
		cin >> choice;
		switch(choice)
		{
			case 1: temp = new BoardVector(size, width); goBack = false; boards.push_back(temp); boardVec = true;
			break;
			case 2: temp = new BoardArray2D(size, width); goBack = false; boards.push_back(temp); board2D = true;
			break;
			case 3: temp = new BoardArray1D(size, width); goBack = false; boards.push_back(temp); board1D = true;
			break;
			default: cout << "Wrong Choice! Try Again" << endl;
		}
		while(!goBack)
		{
			cout << endl <<"Your Board:" << endl;
			if(temp->isSolved())
				cout << "You have solved the board" << endl;
			temp->print();
			cout << "Choices:" << endl;
			cout 	<< "L: LeftMove\t"  
					<< "R: RightMove\t"  
					<< "U: UpMove\t"  
					<< "D: DownMove" << endl
					<< "S: Shufle\t" 
					<< "E: Read from file\t" << endl
					<< "V: Check if your moves valid or not\t"
					<< "W: Write to a file\t" << endl
					<< "P: Print report\t" << endl
					<< "C: Go back and choice board again" << endl
					<< "Q: Close the program" << endl;
			cin >> ch;
			switch(ch)
			{
				case 'L': 	if(boardVec){ temp = new BoardVector(*temp);}
							else if(board2D){ temp = new BoardArray2D(*temp);}
							else if(board1D){ temp = new BoardArray1D(*temp);}
							temp->move(ch);
							boards.push_back(temp);
				
				break;
				case 'R': 	if(boardVec){ temp = new BoardVector(*temp);}
							else if(board2D){ temp = new BoardArray2D(*temp);}
							else if(board1D){ temp = new BoardArray1D(*temp);}
							temp->move(ch);
							boards.push_back(temp);
				break;
				case 'U': 	if(boardVec){ temp = new BoardVector(*temp);}
							else if(board2D){ temp = new BoardArray2D(*temp);}
							else if(board1D){ temp = new BoardArray1D(*temp);}
							temp->move(ch);
							boards.push_back(temp);
				break;
				case 'D': 	if(boardVec){ temp = new BoardVector(*temp);}
							else if(board2D){ temp = new BoardArray2D(*temp);}
							else if(board1D){ temp = new BoardArray1D(*temp);}
							temp->move(ch);
							boards.push_back(temp);
				break;
				case 'S': temp->randomMoves(); boards.clear(); boards.push_back(temp);
				break;
				case 'V': if(validMoves(boards))
					cout << "Your moves are valid" << endl;
					else
						cout << "Your moves are not valid " << endl;
				break;
				case 'E': cout << "Enter your file name: ";
				cin >> fileName;
				infile.open(fileName);
				if(!infile.fail()){
					temp->readFromFile(infile);
					infile.close();
					boards.clear(); 
					boards.push_back(temp);
				}
				else
					cout << "Error: file could not be opened" << endl;
				break;
				case 'W': cout << "Enter your file name: "; 
				cin >> fileName;
				outfile.open(fileName);
				if(!outfile.fail()){
					temp->writeToFile(outfile);
					outfile.close();
				}
				else
					cout << "Error: file could not be opened" << endl;
				break;
				case 'P': temp->printReport();
				break;
				case 'C': goBack = true;
				break;
				case 'Q': goBack = true; check = true;
				break;
				default: cout << "Wrong Choice! Try Again" << endl;
			}
		}
		size = -1;
		width =-1;
		cout << boards.size();
		delete temp;
		boards.clear();
	}
	
	return 0;
}
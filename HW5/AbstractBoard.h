//*************			TURKER		TERCAN		171044032		HW4		CSE241	OOP				 *************//

//Declarations for AbstractBoard
#ifndef ABSTRACTBOARD_H
#define ABSTRACTBOARD_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

namespace TurkerTercanHW5{
	
	class AbstractBoard{
	public:
		AbstractBoard(); 			//default constructor
		AbstractBoard(int, int); 	//constructor
		virtual ~AbstractBoard();	//virtual destructor
		AbstractBoard(const AbstractBoard&); 	//copy constructor
		void print() const;						//print for every abstract objects
		void writeToFile(ostream&) const;			//save current board abstract objectss
		virtual void readFromFile(istream&) = 0;	//virtual read from txt
		virtual int* getBoard() const = 0;			//get board
		void reset();								//to get final solution
		virtual void move(char) = 0;				//move functions
		virtual int operator ()(int, int) const = 0;//operator() to get  
		virtual void randomMoves() = 0;				//to get shuffle board
		virtual int getTile(int, int) const = 0;	//get board[i][j]
		virtual void setTile(int, int, int) = 0;	//set board[i][i]
		void printReport() const;	//print member variables
		void setSize(int, int);		
		bool isSolved() const;		
		int numberOfBoards() const;
		char lastMove() const;
		int numberOfMoves() const;
		int getSize() const;
		int getWidth() const;
		int getLocationX() const;
		int getLocationY() const;
		void setLocationX(int);
		void setLocationY(int);
		void setSize(int);
		void setWidth(int);
		void setLastMove(char);
		void setNumberOfMoves(int);
		void setSolved(bool);
		friend bool operator == (const AbstractBoard&, const AbstractBoard& );
		
		
	private:
		int size;
		int width;
		int moves;
		int locationX;
		int locationY;
		static int num;
		bool solved;
		char last;
	};
	
	bool validMoves(vector<AbstractBoard*>);
	
	
}
#endif //ABSTRACTBOARD_H
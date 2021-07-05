//*************			TURKER		TERCAN		171044032		HW4		CSE241	OOP				 *************//

//Implementation for AbstractBoard
#include "AbstractBoard.h"

using namespace std;
namespace TurkerTercanHW5{
	
	AbstractBoard::AbstractBoard( ){ num++; }
	AbstractBoard::~AbstractBoard(){ }
	AbstractBoard::AbstractBoard(const AbstractBoard& object) : size(getSize()), width(getWidth()), moves(object.numberOfMoves()),
	locationX(object.getLocationX()), locationY(object.getLocationY()), solved(object.isSolved()), last(object.lastMove())
	{
		
	}
	
	AbstractBoard::AbstractBoard(int newSize, int newWidth) : moves(0), solved(false), last('S')
	{ 
		if(newSize > 0)
			size = newSize;
		else{
			cout << "Size can not be negative integer" << endl;
			size = 0;
		}
		if(newWidth > 0)
			width = newWidth;
		else{
			cout << "Width can not be negative integer" << endl;
			width = 0;
		}
		num++; 
	}
	
	int AbstractBoard::num = 0;
	
	void AbstractBoard::setSize(int newSize, int newWidth){
		if(newSize > 0)
			size = newSize;
		else{
			cout << "Size can not be negative integer" << endl;
			size = -1;
		}
		
		if(newWidth > 0)
			width = newWidth;
		else{
			cout << "Width can not be negative integer" << endl;
			width = -1;
		}
	}
	
	bool AbstractBoard::isSolved() const{
		return solved;
	}
	
	int AbstractBoard::numberOfBoards() const{
		return num;
	}
	
	char AbstractBoard::lastMove() const{
		return last;
	}
	
	int AbstractBoard::getSize() const{
		return size;
	}
	
	int AbstractBoard::getWidth() const{
		return width;
	}
	
	int AbstractBoard::getLocationX() const{
		return locationX;
	}
	
	int AbstractBoard::getLocationY() const{
		return locationY;
	}
	
	void AbstractBoard::setLocationX(int x){
		locationX = x;
	}
	
	void AbstractBoard::setLocationY(int y){
		locationY = y;
	}
	
	bool operator ==(const AbstractBoard& n1, const AbstractBoard& n2 ){
		if(n1.getSize() != n2.getSize() || n1.getWidth() != n2.getWidth())
			return false;
		else{
			int* temp1 = n1.getBoard();
			int* temp2 = n2.getBoard();
			
			for(int i = 0; i < n1.getSize() * n2.getWidth(); i++){
				if(temp1[i] != temp2[i])
					return 0;
			}
		}
		return 1;
	}
	void AbstractBoard::setSize(int newSize){
		size = newSize;
	}
	
	void AbstractBoard::setWidth(int newWidth){
		width = newWidth;
	}
	
	void AbstractBoard::setLastMove(char newLast){
		last = newLast;
	}
	
	void AbstractBoard::setNumberOfMoves(int newMoves){
		moves = newMoves;
	}
	
	int AbstractBoard::numberOfMoves() const{
		return moves;
	}
	
	void AbstractBoard::setSolved(bool newSolved){
		solved = newSolved;
	}
	
	void AbstractBoard::printReport() const{
		cout << numberOfBoards() << " number of boards created" << endl
		<< "You played "<< numberOfMoves() << " times in this board" << endl;
		if(isSolved())
			cout << "You have been solved the puzzle" << endl;
		else
			cout << "Puzzle is not solved" << endl;
		
	}
	
	//In classes i implemented my boards the way that i can check their validity with blank space's position
	bool validMoves(vector<AbstractBoard*> boards)
	{
		int x, y;
		int compareX, compareY;
		int size = boards.size();
		if( size == 1)
		{
			return 1;
		}
		for( int i = 0; i < size - 1; i++)
		{
			x = boards[i]->getLocationX();
			y = boards[i]->getLocationY();
			
			compareX = boards[i+1]->getLocationX();
			compareY = boards[i+1]->getLocationY();
			
			if( abs(x - compareX) != 1 && abs(y - compareY) != 1 )
				if( x != compareX || y != compareY)
					return 0;
		}
		return 1;
	}
	void AbstractBoard::writeToFile(ostream& outFile) const{
		for(int i = 0; i < getSize(); i++){
			for(int j = 0; j < getWidth(); j++){
				if( getTile(i,j) < 10 && getTile(i,j) != -1 && j != -1)
					outFile << "0" << getTile(i,j) << " ";
				else if( getTile(i,j) < 10 && getTile(i,j) != -1 && j == 1)
					outFile << "0" << getTile(i,j);
				else if( getTile(i,j) == -1 && j != getWidth() - 1)
					outFile << "bb ";
				else if( getTile(i,j) == -1 && j == getWidth() - 1)
					outFile << "bb";
				else if( j != getWidth() - 1 )
					outFile << getTile(i,j) << " ";
				else if( j == getWidth() - 1 )
					outFile << getTile(i,j);
			}
			if( i != getSize() - 1 )
				outFile << endl;
		}
		cout << "Saving process succesfully ended!\n\n";
	}
	
	void AbstractBoard::print() const{
		for(int i = 0; i < getSize(); i++){
			for(int j = 0; j < getWidth(); j++){
				if( getTile(i,j) < 10 && getTile(i,j) != -1)
					cout << "0" << getTile(i,j) << " ";
				else if( getTile(i,j) == -1)
					cout << "bb" << " ";
				else if( getTile(i,j) >= 10 && getTile(i,j) != -1)
					cout << getTile(i,j) << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	
	void AbstractBoard::reset()
	{
		int count = 1;
		for(int i = 0; i < getSize(); i++)
		{
			for(int j = 0; j < getWidth(); j++)
			{
				setTile(count++, i, j);
				if( i == getSize() - 1 && j == getWidth() - 1 )
					setTile(-1, i, j);
			}
		}
		setSolved(true);
	}
}
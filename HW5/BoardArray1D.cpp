//*************			TURKER		TERCAN		171044032		HW4		CSE241	OOP				 *************//

//Implementation for AbstractBoard
#include "BoardArray1D.h"
#include <iostream>
#include <fstream>

using namespace std;
namespace TurkerTercanHW5
{
	BoardArray1D::BoardArray1D() : AbstractBoard(){ }
	BoardArray1D::BoardArray1D(int newSize, int newWidth) : AbstractBoard(newSize, newWidth)
	{
		int count = 1;
		board = new int[newSize * newWidth];
		for(int i = 0; i < newSize * newWidth; i++)
		{
			board[i] = count++;
			if( i == (newSize * newWidth) - 1)
				board[i] = -1;
		}
		setLocationX(newSize - 1);
		setLocationY(newWidth - 1);
		randomMoves();
	}
	
	BoardArray1D::BoardArray1D(const AbstractBoard& object) : AbstractBoard(object)
	{
		setSize(object.getSize(), object.getWidth());		
		setLastMove(object.lastMove());
		setNumberOfMoves(object.numberOfMoves());
		setSolved(object.isSolved());
		setLocationX(object.getLocationX());
		setLocationY(object.getLocationY());
		board = new int[getSize() * getWidth()];
		int count = 0;
		for(int i = 0; i < getSize(); i++)
		{
			for(int j = 0; j < getWidth(); j++)
			{
				board[count++] = object(i,j);
			}
		}
	}
	
	BoardArray1D& BoardArray1D::operator =(const AbstractBoard& other)
	{
		free(board);
		setSize(other.getSize(), other.getWidth());		
		setLastMove(other.lastMove());
		setNumberOfMoves(other.numberOfMoves());
		setSolved(other.isSolved());
		setLocationX(other.getLocationX());
		setLocationY(other.getLocationY());
		board = new int[getSize() * getWidth()];
		int count = 0;
		for(int i = 0; i < getSize(); i++)
		{
			for(int j = 0; j < getWidth(); j++)
			{
				board[count++] = other(i,j);
			}
		}
		return *this;
	}
	
	BoardArray1D::~BoardArray1D()
	{
		free(board);
	}
	
	void BoardArray1D::readFromFile(istream& infile)
	{
		free(board);
		setSize(0);
		setWidth(0);
		int temp;
		int i = 0;
		int y = 0;
		const int lineCapacity = 30; //there can be 30 char values in the file
		char line[lineCapacity];
		
		while(!infile.eof())
		{
			infile.getline(line, lineCapacity);
			setSize(getSize() + 1);
		}
		for(int i = 0; i < lineCapacity; i++)
		{
			if(line[i] == '\n' || line[i] == '\0')
			{
				setWidth( getWidth() + 1);
				break;
			}
			else
				setWidth( getWidth() + 1);
		}
		setWidth( getWidth() / 3);
		infile.clear();
		infile.seekg(0, ios::beg);
		
		board = new int[getSize() * getWidth()];
		while(!infile.eof())
		{
			infile.getline(line, lineCapacity);
			for(int j = 0; j < lineCapacity; j+=3)
			{
				temp = (((int)line[j] - 48) * 10) + (int)line[j+1] - 48;
				if(temp == 550)//int value of bb
				{	
					temp = -1;
					setLocationX(i);
					setLocationY(y);
				}
				board[i * getWidth() + y++] = temp;
			}
			y = 0;
			i++;
		}
	}
	
	void BoardArray1D::move(char choice)
	{
		switch(choice){
			case 'L': moveLeft();
			break;
			case 'R': moveRight();
			break;
			case 'U': moveUp();
			break;
			case 'D': moveDown();
			break;
			default: cout << "Wrong decision" << endl;
		}
	}
	
	void BoardArray1D::swapBlank(int x, int y)
	{
		board[ getLocationX() * getWidth() + getLocationY()] = board[ x * getWidth() + y];
		board[ x * getWidth() + y] = -1;
		setLocationX(x);
		setLocationY(y);
	}
	
	void BoardArray1D::moveLeft()
	{
		if(getLocationY() != 0 && board[(getLocationX() * getWidth()) + getLocationY() - 1] != 0){
			swapBlank(getLocationX(), getLocationY() - 1);
			setNumberOfMoves(numberOfMoves() + 1);
			setLastMove('L');
			setSolved(check());
		}
		else if( getLocationY() == 0 )
			cout << "Unavailable to move: Left side is empty" << endl;
		else if( board[(getLocationX() * getWidth()) + getLocationY() - 1] == 0 )
			cout << "Unavailable to move: Left side is a wall" << endl;
	}
	
	void BoardArray1D::moveRight()
	{
		if(getLocationY() != getWidth() - 1 && board[(getLocationX() * getWidth()) + getLocationY() + 1] != 0){
			swapBlank(getLocationX(), getLocationY() + 1);
			setNumberOfMoves(numberOfMoves() + 1);
			setLastMove('R');
			setSolved(check());
		}
		else if( getLocationY() == getWidth() - 1 )
			cout << "Unavailable to move: Right side is empty" << endl;
		else if( board[(getLocationX() * getWidth()) + getLocationY() + 1] == 0 )
			cout << "Unavailable to move: Right side is a wall" << endl;
	}
	
	void BoardArray1D::moveUp()
	{
		if(getLocationX() != 0 && board[((getLocationX() - 1) * getWidth()) + getLocationY() ] != 0){
			swapBlank(getLocationX() - 1, getLocationY());
			setNumberOfMoves(numberOfMoves() + 1);
			setLastMove('U');
			setSolved(check());
		}
		else if( getLocationX() == 0 )
			cout << "Unavailable to move: Up side is empty" << endl;
		else if( board[((getLocationX() - 1) * getWidth()) + getLocationY() ] == 0 )
			cout << "Unavailable to move: Up side is a wall" << endl;
	}
	
	void BoardArray1D::moveDown()
	{
		if(getLocationX() != getSize() - 1 && board[((getLocationX() + 1) * getWidth()) + getLocationY() ] != 0){
			swapBlank(getLocationX() + 1, getLocationY());
			setLastMove('D');
			setNumberOfMoves(numberOfMoves() + 1);
			setSolved(check());
		}
		else if( getLocationX() == getSize() - 1 )
			cout << "Unavailable to move: Down side is empty" << endl;
		else if( board[((getLocationX() + 1) * getWidth()) + getLocationY() ] == 0 )
			cout << "Unavailable to move: Down side is a wall" << endl;
	}
	
	int* BoardArray1D::getBoard() const
	{
		return board;
	}
	
	int BoardArray1D::operator ()(int x, int y) const
	{
		return board[ x * getWidth() + y];
	}
	
	int BoardArray1D::getTile(int x, int y) const
	{
		return board[ x * getWidth() + y];
	}
	
	void BoardArray1D::setTile(int tile, int x, int y)
	{
		board[x * getWidth() + y] = tile;
	}
	
	void BoardArray1D::randomMoves()
	{
		srand(time(NULL));
		int n;
		for(int i = 0; i < getSize() * getWidth(); i++){
			n = rand() % 4;
			if( n == 0 && lastMove() != 'D' && getLocationX() != 0)
				move('U');
			else if( n == 1 && lastMove() != 'R' && getLocationY() != 0)
				move('L');
			else if( n == 2 && lastMove() != 'L' && getLocationY() != getWidth() -1)
				move('R');
			else if( n == 3 && lastMove() != 'U' && getLocationX() != getSize() - 1)
				move('D');
		}
	}
	
	bool BoardArray1D::check() const
	{
		int count = 1;
		for(int i = 0; i < getSize() * getWidth(); i++)
		{
			if( i == getSize() * getWidth()- 1  && board[i] == -1)
				return 1;
			if( board[i] != count++)
				return 0;
		}
		return 1;
	}
}
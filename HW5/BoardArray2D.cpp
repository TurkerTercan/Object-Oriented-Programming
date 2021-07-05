//*************			TURKER		TERCAN		171044032		HW4		CSE241	OOP				 *************//

//Implementation for BoardArray2D
#include "BoardArray2D.h"
#include <iostream>
#include <fstream>

using namespace std;
namespace TurkerTercanHW5{
	BoardArray2D::BoardArray2D() : AbstractBoard() { }
	BoardArray2D::BoardArray2D(int newSize, int newWidth) : AbstractBoard(newSize, newWidth)
	{
		int count = 1;
		board = new int*[newSize];
		for(int i = 0; i < newSize; i++){
			board[i] = new int[newWidth];
			for(int j = 0; j < newWidth; j++){
				board[i][j] = count++;
				if(i == newSize -1 && j == newWidth -1)
					board[i][j] = -1;
			}
		}
		setLocationX(newSize - 1);
		setLocationY(newWidth - 1);
		randomMoves();
	}
	
	BoardArray2D::BoardArray2D(const AbstractBoard& object) : AbstractBoard(object)
	{
		setSize(object.getSize(), object.getWidth());		
		setLastMove(object.lastMove());
		setNumberOfMoves(object.numberOfMoves());
		setSolved(object.isSolved());
		setLocationX(object.getLocationX());
		setLocationY(object.getLocationY());
		board = new int*[getSize()];
		for(int i = 0; i < getSize(); i++)
		{
			board[i] = new int[getWidth()];
			for(int j = 0; j < getWidth(); j++)
			{
				board[i][j] = object(i,j);
			}
		}
	}
	
	BoardArray2D& BoardArray2D::operator =(const AbstractBoard& other)
	{
		free(board);
		setSize(other.getSize(), other.getWidth());		
		setLastMove(other.lastMove());
		setNumberOfMoves(other.numberOfMoves());
		setSolved(other.isSolved());
		setLocationX(other.getLocationX());
		setLocationY(other.getLocationY());
		board = new int*[getSize()];
		for(int i = 0; i < getSize(); i++)
		{
			board[i] = new int[getWidth()];
			for(int j = 0; j < getWidth(); j++)
			{
				board[i][j] = other(i,j);
			}
		}
		return *this;
	}
	
	BoardArray2D::~BoardArray2D()
	{
		free(board);
	}
	
	void BoardArray2D::readFromFile(istream& infile)
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
		
		board = new int*[getSize()];
		while(!infile.eof())
		{
			infile.getline(line, lineCapacity);
			board[i] = new int[getWidth()];
			for(int j = 0; j < lineCapacity; j+=3)
			{
				temp = (((int)line[j] - 48) * 10) + (int)line[j+1] - 48;
				cout << temp << endl;
				if(temp == 550)//int value of bb
				{	
					temp = -1;
					setLocationX(i);
					setLocationY(y);
				}
				board[i][y++] = temp;
			}
			y = 0;
			i++;
		}
	}
	
	void BoardArray2D::randomMoves()
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
	
	void BoardArray2D::move(char choice)
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
	void BoardArray2D::swapBlank(int x, int y)
	{
		board[getLocationX()][getLocationY()] = board[x][y];
		board[x][y] = -1;
		setLocationX(x);
		setLocationY(y);
	}
	
	void BoardArray2D::moveLeft()
	{
		if(getLocationY() != 0 && board[getLocationX()][getLocationY() - 1] != 0){
			swapBlank(getLocationX(), getLocationY() - 1);
			setNumberOfMoves(numberOfMoves() + 1);
			setLastMove('L');
			setSolved(check());
		}
		else if( getLocationY() == 0 )
			cout << "Unavailable to move: Left side is empty" << endl;
		else if( board[getLocationX()][getLocationY() - 1] == 0 )
			cout << "Unavailable to move: Left side is a wall" << endl;
	}
	
	void BoardArray2D::moveRight()
	{
		if(getLocationY() != getWidth() - 1 && board[getLocationX()][getLocationY() + 1] != 0){
			swapBlank(getLocationX(), getLocationY() + 1);
			setNumberOfMoves(numberOfMoves() + 1);
			setLastMove('R');
			setSolved(check());
		}
		else if( getLocationY() == getWidth() - 1 )
			cout << "Unavailable to move: Right side is empty" << endl;
		else if( board[getLocationX()][getLocationY() + 1] == 0 )
			cout << "Unavailable to move: Right side is a wall" << endl;
	}
	
	void BoardArray2D::moveUp()
	{
		if(getLocationX() != 0 && board[getLocationX() - 1][getLocationY()] != 0){
			swapBlank(getLocationX() - 1, getLocationY());
			setNumberOfMoves(numberOfMoves() + 1);
			setLastMove('U');
			setSolved(check());
		}
		else if( getLocationX() == 0 )
			cout << "Unavailable to move: Up side is empty" << endl;
		else if( board[getLocationX() - 1][getLocationY()] == 0 )
			cout << "Unavailable to move: Up side is a wall" << endl;
	}
	
	void BoardArray2D::moveDown()
	{
		if(getLocationX() != getSize() - 1 && board[getLocationX() + 1][getLocationY()] != 0){
			swapBlank(getLocationX() + 1, getLocationY());
			setLastMove('D');
			setNumberOfMoves(numberOfMoves() + 1);
			setSolved(check());
		}
		else if( getLocationX() == getSize() - 1 )
			cout << "Unavailable to move: Down side is empty" << endl;
		else if( board[getLocationX() + 1][getLocationY()] == 0 )
			cout << "Unavailable to move: Down side is a wall" << endl;
	}
	
	int BoardArray2D::operator ()(int x, int y) const
	{
		return board[x][y];
	}
	
	int BoardArray2D::getTile(int x, int y) const
	{
		return board[x][y];
	}
	
	void BoardArray2D::setTile(int tile, int x, int y)
	{
		board[x][y] = tile;
	}
	
	
	bool BoardArray2D::check() const
	{
		int count = 1;
		for(int i = 0; i < getSize(); i++){
			for(int j = 0; j < getWidth(); j++){
				if( i == getSize() - 1 && j == getWidth() - 1 && board[i][j] == -1)
					return 1;
				if( board[i][j] != count++)
					return 0;
			}
		}
		return 1;
	}
	
	int* BoardArray2D::getBoard() const
	{
		int *temp = new int[getSize() * getWidth()];
		int count = 0;
		for(int i = 0; i < getSize(); i++)
		{
			for(int j = 0; j< getWidth(); j++)
			temp[count++] = board[i][j];
		}
		return temp;
	}
}
//*************			TURKER		TERCAN		171044032		HW4		CSE241	OOP				 *************//

//Implementation for BoardVector
#include "BoardVector.h"

#include <vector>

using namespace std;
namespace TurkerTercanHW5{
	BoardVector::BoardVector() : AbstractBoard(){ }
	BoardVector::BoardVector(int size, int width) : AbstractBoard(size, width){ initializeVectorBoard();}
	BoardVector::~BoardVector() {
		board.clear();
	}
	BoardVector::BoardVector(const AbstractBoard& object) 
	{
		setSize(object.getSize(), object.getWidth());		
		setLastMove(object.lastMove());
		setNumberOfMoves(object.numberOfMoves());
		setSolved(object.isSolved());
		setLocationX(object.getLocationX());
		setLocationY(object.getLocationY());
		for(int i = 0; i < getSize(); i++){
			vector<int> temp;
			for(int j = 0; j < getWidth(); j++){
				temp.push_back(object(i,j));
			}
			board.push_back(temp);
		}
	}
	
	BoardVector& BoardVector::operator=(const AbstractBoard& other){
		board.clear();
		setSize(other.getSize(), other.getWidth());		
		setLastMove(other.lastMove());
		setNumberOfMoves(other.numberOfMoves());
		setSolved(other.isSolved());
		setLocationX(other.getLocationX());
		setLocationY(other.getLocationY());
		
		for(int i = 0; i < getSize(); i++){
			vector<int> temp;
			for(int j = 0; j < getWidth(); j++){
				temp.push_back(other(i,j));
			}
			board.push_back(temp);
		}
		return *this;
	}
	
	void BoardVector::initializeVectorBoard(){
		int count = 1;
		for(int i = 0; i < getSize(); i++){
			vector<int> temp;
			for(int j = 0; j < getWidth(); j++){
				if( i == getSize() - 1 && j == getWidth() - 1){
					temp.push_back(-1);
					setLocationX(i);
					setLocationY(j);
				}
				else{
					temp.push_back(count);
					count++;
				}
			}
			board.push_back(temp);
		}
		randomMoves();
	}
	void BoardVector::randomMoves(){
		srand(time(NULL));
		int n;
		for(int i = 0; i < getSize() * getWidth(); i++){
			n = rand() % 4;
			if( n == 0 && getLocationX() != 0 && lastMove() != 'D')
				move('U');
			else if( n == 1 && lastMove() != 'R' && getLocationY() != 0)
				move('L');
			else if( n == 2 && lastMove() != 'L' && getLocationY() != getWidth() -1)
				move('R');
			else if( n == 3 && lastMove() != 'U' && getLocationX() != getSize() - 1)
				move('D');
		}
	}
	
	void BoardVector::move(char choice){
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
	void BoardVector::swapBlank(int x, int y){
		board[getLocationX()][getLocationY()] = board[x][y];
		board[x][y] = -1;
		setLocationX(x);
		setLocationY(y);
	}
	
	void BoardVector::moveLeft(){
		if(getLocationY() != 0 && board[getLocationX()][getLocationY() - 1] != 0){
			swapBlank(getLocationX(), getLocationY() - 1);
			setLastMove('L');
			setNumberOfMoves(numberOfMoves() + 1);
			setSolved(check());
		}
		else if( getLocationY() == 0 )
			cout << "Unavailable to move: Left side is empty" << endl;
		else if( board[getLocationX()][getLocationY() - 1] == 0 )
			cout << "Unavailable to move: Left side is a wall" << endl;
	}
	
	void BoardVector::moveRight(){
		if(getLocationY() != getWidth() - 1 && board[getLocationX()][getLocationY() + 1] != 0){
			swapBlank(getLocationX(), getLocationY() + 1);
			setLastMove('R');
			setNumberOfMoves(numberOfMoves() + 1);
			setSolved(check());
		}
		else if( getLocationY() == getWidth() - 1 )
			cout << "Unavailable to move: Right side is empty" << endl;
		else if( board[getLocationX()][getLocationY() + 1] == 0 )
			cout << "Unavailable to move: Right side is a wall" << endl;
	}
	
	void BoardVector::moveUp(){
		if(getLocationX() != 0 && board[getLocationX() - 1][getLocationY()] != 0){
			swapBlank(getLocationX() - 1, getLocationY());
			setLastMove('U');
			setNumberOfMoves(numberOfMoves() + 1);
			setSolved(check());
		}
		else if( getLocationX() == 0 )
			cout << "Unavailable to move: Up side is empty" << endl;
		else if( board[getLocationX() - 1][getLocationY()] == 0 )
			cout << "Unavailable to move: Up side is a wall" << endl;
	}
	
	void BoardVector::moveDown(){
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
	
	int BoardVector::operator ()(int x, int y) const{
		return board[x][y];
	}
	
	int BoardVector::getTile(int x, int y) const{
		return board[x][y];
	}
	
	void BoardVector::setTile(int tile, int x, int y)
	{
		board[x][y] = tile;
	}

	void BoardVector::readFromFile(istream& infile){
		board.clear();
		setSize(0);
		setWidth(0);
		int temp;
		const int lineCapacity = 30; //there can be 30 char values in the file
		char line[lineCapacity];
		
		while(!infile.eof()){
			infile.getline(line, lineCapacity);
			vector<int> row;
			for(int i = 0; i < lineCapacity; i+=3){
				temp = (((int)line[i] - 48) * 10) + (int)line[i+1] - 48;
				if(temp == 550)//int value of bb
					temp = -1;
				row.push_back(temp);
			}
			board.push_back(row);
			setSize(getSize( ) + 1);
		}
		
		for(int i = 0; i < lineCapacity; i++){
			if(line[i] == '\n' || line[i] == '\0'){
				setWidth(getWidth( ) + 1);
				break;
			}
			else
				setWidth(getWidth( ) + 1);
		}
		setWidth(getWidth( ) / 3);
	} 
		
	int * BoardVector::getBoard() const{
		int * temp = new int[getSize() * getWidth()];
		int count = 0;
		for(int i = 0; i < getSize(); i++){
			for(int j = 0; j< getWidth(); j++)
			temp[count++] = board[i][j];
		}
		return temp;
	}
	
	bool BoardVector::check() const{
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
}
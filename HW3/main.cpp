//*************			TURKER		TERCAN		171044032		HW3		CSE241	OOP				 *************//
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Board{
public:
	void print() const;	//Prints board
	void readFromFile(ifstream&);	//It loads a shapefile to current board.
//Shapefile must not contain unnecessary whitespaces and newlines
	void writeToFile(ofstream&);	//It saves current board to a output shape file
	void reset();	//It takes board to final solution and calls resetSolved
	void setSize(int, int);	//It used for changing size and width
	void move(char);	//moves the blank cell 
	bool isSolved() const;	//returns if it is solved
	int getSize() const;		//returns size
	int getWidth() const;		//returns width
	void locateBB(int&, int&);	//Finds blank space 
	void increaseMoves();	//increase move count
	int getMoves() const;	//returns movecount
	void resetMoves();	//resets movecount
	void resetSolved();	//changes solved value to false
	int whereIsBest(int, int);		//it checks which possible move is best for us
	bool isThereAWall(int, int) const;	//Checks if there is wall for random moves
private:
	void moveLeft(int, int);	//These four functions provides us to move blank space
	void moveRight(int, int);
	void moveUp(int, int);
	void moveDown(int, int);
	void truePosition(int, int&, int&);	//Locates that piece's where it needs to be
	int manhattanDistance();	//Calculates the how many moves needs to be done for each wrong tiles
	int trueValue(int, int) const;	//it returns what value should be in that tile
	void check();	//Checks if the puzzle has been solved or not
	int tiles[9][9] = {-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,
	-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2};
	bool solved = false;
	int size, width;
	int moves = 0;
};

class NPuzzle{
public:
	void print() const;		//Prints the current board
	void printReport()const;//Prints the board solved or not and how many moves have been done
	void readFromFile();//Takes a string and opens it for board::readFromFile()
	bool readFromFile(string);	//Converts optional command line to string and opens it
	void writeToFile();	//Takes a string and opens it for board::writeToFile()
	void shuffle();	//Resets the board and moves randomly size * width times
	void reset();	//It takes puzzle to final solution
	void setSize();	//It takes to int and checks if they are valid or not
	void move(int);	//This two functions calls board::move()
	void move(char);
	void moveRandom(int&);	//When the algorithm stucks, this functions helps it for making random moves.
	void moveIntelligent();	//An algorithm that it makes one intellegent move for us
	void solvePuzzle();	//New algorithm is that tries to solve the puzzle directly.
	void choices(int) const;	//It shows the usuable choices
	bool check() const; //It returns board.solved
private:
	Board board;
};

int main(int argc, char** argv){
	NPuzzle problem;
	char choice;
	bool flag = false;
	srand(time(NULL));
	if(argc == 2)
		flag = problem.readFromFile(argv[1]);
	else if(!flag){
		problem.setSize();
		problem.shuffle();
	}
	
	cout << "\nYour initial board is ->\n";
	problem.print();
	while(1){
		if(!problem.check()){
			problem.choices(0);
			cin >> choice;
			switch(choice){
				case 'V': problem.solvePuzzle();
				break;
				case 'T': problem.printReport(); 
				break;
				case 'E': problem.writeToFile(); 
				break;
				case 'O': problem.readFromFile(); problem.print();
				break;
				case 'L': problem.move('L'); problem.print();
				break;
				case 'R': problem.move('R'); problem.print();
				break;
				case 'U': problem.move('U'); problem.print();
				break;
				case 'D': problem.move('D'); problem.print();
				break;
				case 'I': problem.moveIntelligent(); problem.print();
				break;
				case 'S': problem.shuffle(); problem.print();
				break;
				case 'Q': return 0;
				default: cout << "Invalid choice!\n\n"; problem.choices(0);
			}
		}
		else{
			problem.choices(1);
			cin >> choice;
			switch(choice){
				case 'T': problem.printReport(); 
				break;
				case 'E': problem.writeToFile(); 
				break;
				case 'O': problem.readFromFile(); problem.print();
				break;
				case 'S': problem.shuffle(); problem.print();
				break;
				case 'Q': return 0;
				default: cout << "Invalid choice!\n\n"; problem.choices(1);
			}
		}
	}
	return 0;
}

//Prints tile values
void Board::print() const{
	for(int i = 0; i < size; i++){
		for(int j = 0; j < width; j++){
			if(tiles[i][j] < 10 && tiles[i][j] != -1)
				cout << "0" << tiles[i][j] << " ";
			else if(tiles[i][j] == -1)
				cout << "bb ";
			else
				cout << tiles[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
//It reads from file
void Board::readFromFile(ifstream& inFile){
	size = 0;	//resizing the values
	width = 0;
	int temp;
	const int lineCapacity = 30;
	char line[lineCapacity];
	
	while(!inFile.eof()){
		inFile.getline(line, lineCapacity);
		for(int i = 0; i < lineCapacity; i = i + 3){
			temp = (((int)line[i] - 48) * 10) + (int)line[i+1] - 48;
			if(temp == 550) //the integer value of bb
				temp = -1;
			tiles[size][i / 3] = temp;
		}
		size++;
	}
	for(int i = 0; i < lineCapacity; i++){
		if(line[i] == '\n' || line[i] == '\0'){
			width++;
			break;
		}
		else
			width++;
	}
	width = width / 3;
	inFile.close();
}
//Write current board to a shapefile
void Board::writeToFile(ofstream& outFile){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < width; j++){
			if( tiles[i][j] < 10 && tiles[i][j] != -1 && j != -1)
				outFile << "0" << tiles[i][j] << " ";
			else if( tiles[i][j] < 10 && tiles[i][j] != -1 && j == 1)
				outFile << "0" << tiles[i][j];
			else if( tiles[i][j] == -1 && j != width - 1)
				outFile << "bb ";
			else if( tiles[i][j] == -1 && j == width - 1)
				outFile << "bb";
			else if( j != width - 1 )
				outFile << tiles[i][j] << " ";
			else if( j == width - 1 )
				outFile << tiles[i][j];
		}
		if( i != size - 1 )
			outFile << endl;
	}
	cout << "Saving process succesfully ended!\n\n";
	outFile.close();
}
//to turn board.solve value to false and takes the puzzle to final solution
void Board::reset(){
	int count = 1;
	resetSolved();
	for(int i = 0; i < size; i++){
		for(int j = 0; j < width; j++){
			if( tiles[i][j] != 0 ){
				tiles[i][j] = count;
				count++;
			}
		}
	}
	tiles[size-1][width-1] = -1;	//Blank space tile
}
//It changes size and width values
void Board::setSize(int newSize, int newWidth){
	size = newSize;
	width = newWidth;
	reset();
}
//Checks the choices are valid and move bb by choice
void Board::move(char choice){
	int x, y;
	locateBB(x, y);
	if(choice == 'U'){
		if( x == 0 )
			cout << "Error: There is no place above\n";
		else if( tiles[x-1][y] == 0 )
			cout << "Error: There is a wall on the top\n";
		else{
			moveUp(x, y);
			increaseMoves();
		}
	}
	else if(choice == 'L'){
		if( y == 0 )
			cout << "Error: There is no room on the left\n";
		else if( tiles[x][y-1] == 0)
			cout << "Error: There is a wall on the left\n";
		else{
			moveLeft(x, y);
			increaseMoves();
		}
	}
	else if(choice == 'R'){
		if( y == width - 1)
			cout << "Error: There is no room on the right\n";
		else if( tiles[x][y+1] == 0)
			cout << "Error: There is a wall on the right\n";
		else{
			moveRight(x, y);
			increaseMoves();
		}
	}
	else if(choice == 'D'){
		if( x == size - 1)
			cout << "Error: There is no place below\n";
		else if( tiles[x+1][y] == 0)
			cout << "Error: There is a wall below\n";
		else{
			moveDown(x, y);
			increaseMoves();
		}
	}
	else
		cout << "Invalid choice\n";
}

//Locates bb and returns it position
void Board::locateBB(int& x, int& y){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < width; j++){
			if(tiles[i][j] == -1){
				x = i;
				y = j;
				return;
			}
		}
	}
}
//Moves the blank space and checks if the board solved or not
void Board::moveUp(int x, int y){
	tiles[x][y] = tiles[x-1][y];
	tiles[x-1][y] = -1;
	check();
}

void Board::moveLeft(int x, int y){
	tiles[x][y] = tiles[x][y-1];
	tiles[x][y-1] = -1;
	check();
}

void Board::moveRight(int x, int y){
	tiles[x][y] = tiles[x][y+1];
	tiles[x][y+1] = -1;
	check();
}

void Board::moveDown(int x, int y){
	tiles[x][y] = tiles[x+1][y];
	tiles[x+1][y] = -1;
	check();
}

inline bool Board::isSolved() const{
	return solved;
}

inline int Board::getSize() const{
	return size;
}

inline int Board::getWidth() const{
	return width;
}

inline int Board::getMoves() const{
	return moves;
}

inline void Board::increaseMoves(){
	moves++;
}

inline void Board::resetMoves(){
	moves = 0;
}

inline void Board::resetSolved(){
	solved = false;
}

//To chooce best choice function needs to calculate every possible move and find the minimum one
int Board::whereIsBest(int x, int y){
	int piece[4] = {1000,1000,1000,1000};
	
	if( x != 0 && tiles[x-1][y] != 0){
		moveUp(x, y);
		piece[0] = manhattanDistance();
		moveDown(x-1, y);
	}
	if( y != 0 && tiles[x][y-1] != 0){
		moveLeft(x, y);
		piece[1] = manhattanDistance();
		moveRight(x, y-1);
	}
	if( y != getWidth() - 1 && tiles[x][y+1] != 0){
		moveRight(x, y);
		piece[2] = manhattanDistance();
		moveLeft(x, y+1);
	}
	if( x != getSize() - 1 && tiles[x+1][y] != 0){
		moveDown(x, y);
		piece[3] = manhattanDistance();
		moveUp(x+1, y);
	}
	
	int min = 1000, result = -1;
	for(int i = 0; i < 4; i++){
		if(piece[i] < min){
			min = piece[i];
			result = i;
		}
	}
	return result;
}
//it calculates how many moves needs to be done for every wrong tile 
int Board::manhattanDistance(){
	int distance = 0, count = 1;
	int wrongPiece, x, y;
	
	for(int i = 0; i < getSize(); i++){
		for(int j = 0; j < getWidth(); j++){
			if(tiles[i][j] != 0){
				if(tiles[i][j] != count && tiles[i][j] != -1 && (i != getSize() || j != getWidth())){
					wrongPiece = tiles[i][j];
					truePosition(wrongPiece, x, y);
					distance += abs(x - i) + abs(y - j);
				}
				count++;
			}
		}
	}
	return distance;
}
//To locate that variable's true position
void Board::truePosition(int wrongPiece, int& x, int& y){
	int count = 1;
	
	for(int i = 0; i < getSize(); i++){
		for(int j = 0; j < getWidth(); j++){
			if(tiles[i][j] == wrongPiece){
				x = i - 1;
				y = j - 1;
				return;
			}
			if(tiles[i][j] != 0){
				count++;
			}
		}
	}
}
//to get the true value of that tile
int Board::trueValue(int x, int y) const{
	int count = 1;
	for(int i = 0; i < getSize(); i++){
		for(int j = 0; j < getWidth(); j++){
			if(i == x && j == y){
				return count;
			}
			if( tiles[i][j] != 0){
				count++;
			}
		}
	}
}
//Checks the board is finished
void Board::check(){
	int count = 1;
	int numberOfCorrects = 0;
	for(int i = 0; i < getSize(); i++){
		for(int j = 0; j < getWidth(); j++){
			if(tiles[i][j] == 0)
				numberOfCorrects++;
			else{
				if(tiles[i][j] == count){
					numberOfCorrects++;
				}
				count++;
			}
		}
	}
	if(numberOfCorrects == (getSize() * getWidth()) - 1 && tiles[getSize() - 1][getWidth() - 1] == -1){
		solved = true;
	}
}

void NPuzzle::print() const{
	board.print();
}

void NPuzzle::printReport() const{
	if(board.isSolved())
		cout << "Problem is solved. Moves: " << board.getMoves() << endl;
	else
		cout << "Problem has not solved yet. Moves: " << board.getMoves() << endl;
}

void NPuzzle::readFromFile(){
	string fileName;
	ifstream inFile;
	do{
		cout << "Enter your shapefile name: \n" << "(If you want to go back to main menu, type M)\n";
		cin >> fileName;
		if(fileName == "M")
			return;
		inFile.open(fileName);
		if(inFile.fail())
			cout << "Failed to open the shapefile. Try again!\n";
	}while(inFile.fail());
	board.readFromFile(inFile);
}

bool NPuzzle::readFromFile(string fileName){
	ifstream inFile;
	inFile.open(fileName);
	if(!inFile.fail()){
		board.readFromFile(inFile);
		return true;
	}
	else
		return false;
}

void NPuzzle::writeToFile(){
	ofstream outFile;
	string fileName;
	cout << "Type a name to save your current board: ";
	cin >> fileName;
	outFile.open(fileName);
	board.writeToFile(outFile);
}

void NPuzzle::shuffle(){
	int x = board.getSize();
	int y = board.getWidth();
	int dir = -1;
	int count = 0;
	reset();
	while( count < (x * y)){
		moveRandom(dir);
		count++;
	}
	board.resetMoves();
}

void NPuzzle::reset(){
	board.reset();
}
//to make sure newSize and newWidth are valid for us
void NPuzzle::setSize(){
	int newSize, newWidth;
	cout << "Enter the size of the puzzle: ";
	cin >> newSize;
	cout << "Enter the width of the puzzle: ";
	cin >> newWidth;
	while( newSize <= 0 || newSize >= 10 || newWidth <= 0 || newWidth >= 10){
		if( newSize <= 0 || newSize >= 10 ){
			cout << "Size must be between 0 and 10. Try Again! ";
			cin >> newSize;
		}
		if( newWidth <= 0 || newWidth >= 10){
			cout << "Width must be between 0 and 10. Try Again! ";
			cin >> newWidth;
		}
	}
	board.setSize(newSize, newWidth);
}

void NPuzzle::move(int direction){
	switch(direction){
		case 0: board.move('U');
		break;
		case 1: board.move('L');
		break;
		case 2: board.move('R');
		break;
		case 3: board.move('D');
		break;
		default: cout << "Invalid NPuzzle::move choice\n";
	}
}

void NPuzzle::move(char choice){
	if( choice == 'U' || choice == 'L' || choice == 'R' || choice == 'D')
		board.move(choice);
	else
		cout << "Invalid NPuzzle::move choice\n";
}

inline bool Board::isThereAWall(int x, int y) const{
	return (tiles[x][y] == 0);
}
//Makes a random move
void NPuzzle::moveRandom(int& lastMove){
	//I used last move for just i wanted to be sure about it will not go backwards.
	int randomN, x, y;
	bool flag = false;
	board.locateBB(x ,y);
	while(!flag){
		randomN = rand() % 4;
		if( x != 0 && randomN == 0 && lastMove != 3 && !board.isThereAWall(x-1, y)){
			move(randomN);
			flag = true;
			lastMove = 0;
		}
		if( y != 0 && randomN == 1 && lastMove != 2 && !board.isThereAWall(x, y-1)){
			move(randomN);
			flag = true;
			lastMove = 1;
		}
		if( y != board.getWidth() - 1 && randomN == 2 && lastMove != 1 && !board.isThereAWall(x, y+1)){
			move(randomN);
			flag = true;
			lastMove = 2;
		}
		if( x != board.getSize() - 1 && randomN == 3 && lastMove != 0 && !board.isThereAWall(x+1, y)){
			move(randomN);
			flag = true;
			lastMove = 3;
		}
	}
}
//One intelegent move
void NPuzzle::moveIntelligent(){
	int x, y;
	int whereToGo;
	board.locateBB(x, y);
	whereToGo = board.whereIsBest(x, y);
	//If there is a match for cell to move
	switch(whereToGo){
		case 0: cout << "AI chosed moveUp.\n"; move(whereToGo); 
		break;
		case 1: cout << "AI chosed moveLeft.\n"; move(whereToGo); 
		break;
		case 2: cout << "AI chosed moveRight.\n"; move(whereToGo); 
		break;
		case 3: cout << "AI chosed moveDown.\n"; move(whereToGo); 
		break;
		default: cout << "Unable to calculate.\n";
	}
}
//Solves the puzzle
void NPuzzle::solvePuzzle(){
	int x, y, i = 0;
	int whereToGo = -1, lastMove = -1;
	while(!check()){
		board.locateBB(x, y);
		whereToGo = board.whereIsBest(x, y);
		if((whereToGo == 0 && lastMove == 3) || (whereToGo == 1 && lastMove == 2) || (whereToGo == 2 && lastMove == 1) || 
		(whereToGo == 3 && lastMove == 0)){ //If the algorithm stucks and wants to return back, it'll makes random moves size times
			while( i != board.getSize()){
				moveRandom(lastMove);
				i++;
				switch(lastMove){
					case 0: cout << "RandomMove chosed moveUP \n";
					break;
					case 1: cout << "RandomMove chosed moveLEFT \n";
					break;
					case 2: cout << "RandomMove chosed moveRIGHT \n";
					break;
					case 3: cout << "RandomMove chosed moveDOWN \n";
					break;
				}
				print();
			}
			i = 0;
		}
		else{
			switch(whereToGo){
				case 0: cout << "AI chosed moveUP \n";
				break;
				case 1: cout << "AI chosed moveLEFT \n";
				break;
				case 2: cout << "AI chosed moveRIGHT \n";
				break;
				case 3: cout << "AI chosed moveDOWN \n";
				break;
				default: cout << "Unable to calculate \n";
			}
			move(whereToGo);
			lastMove = whereToGo;
			print();
			board.increaseMoves();
		}
	}
}

void NPuzzle::choices(int n) const{
	if(n == 0){
		cout << "\nNew Actions:\n" << "V: Solve puzzle with new algorithm\n" << "T: Print the reports\n"
			 << "E: Save current puzzle\n" << "O: Load a shapefile\n" << endl
			 << "Moves:\nL: Moves blank cell to left\n" << "R: Moves black cell to right\n" << "U: Moves blank cell to up \n"
			 << "D: Moves blank cell to down\n\n" << "I: Makes an intelegent move for you\n"
			 << "S: Shuffle the board\n" << "Q: Quits the game" << endl
			 << "What is your choice?  ";
	}
	if(n == 1){
		cout << "\nThe puzzle have been solved. Congratulations!!" << endl
			 << "T: Print the report\nE: Save current puzzle\nO: Load a shapefile\n\n"
			 << "S: Reset and shuffle the game\nQ: Quits the game\n\nWhat is your choice?  ";
	}
}

bool NPuzzle::check() const{
	return board.isSolved();
}

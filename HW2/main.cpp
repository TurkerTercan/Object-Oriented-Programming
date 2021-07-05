//*************			TURKER		TERCAN		171044032		HW2		CSE241	OOP				 *************//
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void SolveBoard(int [9][9], const int, const int, int&);
//New algorithm is that tries to solve the puzzle directly.
void RandomMovements(int [9][9], int, int, int&, int&);
//When the algorithm stucks, this functions helps it for making random moves.
void LoadCurrent(int [9][9], int&, int&);
//It loads a shapefile to current board.
//Shapefile must not contain unnecessary whitespaces and newlines
int LoadCurrent(int [9][9], int&, int&, const char*);
//Optional command line
void SaveCurrent(const int [9][9], const int, const int);
//It saves current board to a output shape file
void ShowChoices();
//It shows the usuable choices
void TruePosition(const int [9][9], const int, const int, const int, int&, int&);
//locate the piece's where it should be
int TrueValue(const int [9][9], const int, const int, const int, const int);
//find the value of that tile
void ShowResult(const bool, const int);
//Shows the result

//These five functions provide us to move the cell.
void UpMove(int [9][9], int, int); 
void RightMove(int [9][9], int, int);
void DownMove(int [9][9], int, int);
void LeftMove(int [9][9], int, int);
void FindBlankSpace(int [9][9], int, int, int&, int&);	//it finds the empty cell on the puzzle

void IntelligentMove(int [9][9], int, int);	//get solved the puzzle by ai
int IsCorrectBoard(const int [9][9], const int, const int);	//it return how many matched pieces are there on the puzzle
void BoardInit(int [9][9], const int, const int);	//to initilalize it
void ShowPuzzle(const int [9][9], const int, const int); //to show the path
void Shuffle(int [9][9], int, int);	//it shows the solution and than shuffles it
int WhereIsBest(int [9][9], int, int, int, int);
int ManhattanDistance(int [9][9], int, int); 

int main(int argc, char** argv){
	int size, width;
	int board[9][9];
	int moves = 0; 
	int control;
	bool isSolved = false;
	//if there is an arg, then load it.
	if(argv[1]){
		control = LoadCurrent(board, size, width, argv[1]);
	}
	
	else{
		cout << "Please enter the puzzle's size: ";
		cin >> size;
		cout << "Please enter the puzzle's width: ";
		cin >> width;
		BoardInit(board, size, width);
	}
	
	cout << "\nYour initial board is ->\n" << endl;
	ShowPuzzle(board, size, width);
	ShowChoices();
	
	char choices;
	while( 1 ){
		cin >> choices;
		switch(choices){
			case 'L': LeftMove(board, size, width); moves++; ShowPuzzle(board, size, width);
			break;
			case 'U': UpMove(board, size, width); moves++; ShowPuzzle(board, size, width);
			break;
			case 'R': RightMove(board, size, width); moves++; ShowPuzzle(board, size, width);
			break;
			case 'D': DownMove(board, size, width); moves++; ShowPuzzle(board, size, width);
			break;
			case 'I': IntelligentMove(board, size , width); moves++; ShowPuzzle(board, size, width);
			break;
			case 'S': Shuffle(board, size, width); moves = 0; ShowPuzzle(board, size, width);
			break;
			case 'Q': return 0;
			break;
			//New Cases
			case 'V': SolveBoard(board, size, width, moves);
			break;
			case 'T': ShowResult(isSolved, moves);
			break;
			case 'E': SaveCurrent(board, size, width);
			break;
			case 'Y': LoadCurrent(board, size, width); ShowPuzzle(board, size, width);
			break;
			
			default: cout << "Invalid choice!\n\n"; ShowChoices();
		}
		if( IsCorrectBoard(board,size,width) == (size * width) - 1 ){
			cout << "CONGRATULATIONS!! YOU HAVE SOLVED THE PUZZLE. Moves: " << moves << endl;
			isSolved = true; 
		}
	}
	return 0;
}
//to get result
void ShowResult(const bool isSolved, const int moves){
	if( isSolved ){
		cout << "Problem is solved.  ";
	}
	else{
		cout << "Problem has not solved yet.  ";
	}
	
	cout << "Moves: " << moves << endl;
}
//to solve the puzzle with new intellegent algorithm(it not works properly)
void SolveBoard(int board[9][9], const int size, const int width, int& moves){
	int x, y;
    int whereToGo = -1;
	int lastMove = -1;
	while(IsCorrectBoard(board,size,width) != (size * width) - 1){
		FindBlankSpace(board, size, width, x,y);
		whereToGo = WhereIsBest(board, size, width, x, y); //it returns where should it go
		if( (whereToGo == 0 && lastMove == 3) || (whereToGo == 1 && lastMove == 2) || (whereToGo == 2 && lastMove == 1) || 
		(whereToGo == 3 && lastMove == 0) ){	//i used this because i wanted to be sure that it will not be able to move backwards.
			RandomMovements(board, size, width, moves, lastMove); //if it wants to move backwards, make random moves
		}
		else{
			//If there is a match for cell to move
			switch(whereToGo){
				case 0: UpMove(board, size, width); cout << "AI chosed up move.\n\n";
				break;
				case 1: LeftMove(board, size, width); cout << "AI chosed left move.\n\n";
				break;
				case 2: RightMove(board, size, width); cout << "AI chosed right move.\n\n";
				break;
				case 3: DownMove(board, size, width); cout << "AI chosed down move.\n\n";
				break;
				default: cout << "Unable to calculate\n";
			}
			lastMove = whereToGo;
			moves++;
			ShowPuzzle(board, size, width);
		}
	}
}

void RandomMovements(int board[9][9], int size, int width, int& moves, int& lastMove){
	int choice, x, y;
	srand(time(NULL));
	int count = 1;
	while(count > 0){
		choice = rand() % 4;
		FindBlankSpace(board, size, width, x, y);
		if(choice == 0 && (board[x-1][y] != 0 && x != 0) && lastMove != 3){ //to make sure that there is no wall and no backward moves
			UpMove(board, size, width);
			cout << "Random up move\n\n";
			ShowPuzzle(board, size, width);
			lastMove = choice;
		}
		if(choice == 1 && (board[x][y-1] != 0 && y != 0 && lastMove != 2)){
			LeftMove(board, size, width);
			cout << "Random left move\n\n";
			ShowPuzzle(board, size, width);
			lastMove = choice;
		}
		if(choice == 2 && (board[x][y+1] != 0 && y != width -1) && lastMove != 1){
			RightMove(board, size, width);
			cout << "Random right move\n\n";
			ShowPuzzle(board, size, width);
			lastMove = choice;
		}
		if(choice == 3 && (board[x+1][y] != 0 && x != size - 1) && lastMove != 0){
			DownMove(board, size, width);
			cout << "Random down move\n\n";
			ShowPuzzle(board, size, width);
			lastMove = choice;
		}
		else{
			count++;
			moves--;
		}
		moves++;
		count--;
		
	}
}
//Available choices
void ShowChoices(){
	cout << "New Actions:\n" << "V: Solve puzzle with new algorithm\n" << "T: Print the reports\n"
		 << "E: Save current puzzle\n" << "Y: Load a shapefile\n" << endl
		 << "Moves:\nL: Moves blank cell to left\n" << "R: Moves black cell to right\n" << "U: Moves blank cell to up \n"
		 << "D: Moves blank cell to down\n\n" << "I: Makes an intelegent move for you\n"
		 << "S: Shuffle the board\n" << "Q: Quits the game" << endl
		 << "What is your choice?  ";
}
//Load shapefile
void LoadCurrent(int board[9][9], int& size, int& width){
	string fileName;
	ifstream inFile;
	const int lineCapacity = 30;
	char line[lineCapacity];
	do{
		cout << "Enter the name of the loadable shape file :" << endl;
		cin >> fileName;
		inFile.open(fileName);
		if(inFile.fail()){
			cout << "Name of the file is wrong. Please Try Again!" << endl;
		}
	}while(inFile.fail());
	//if it fails, try again.
	//Reset the board for reloading..
	size = 0;
	width = 0;
	int temp;
	while(!inFile.eof()){
		inFile.getline(line, lineCapacity);
		
		for(int i = 0; i < lineCapacity; i = i + 3){
			//transfering chars to ints
			temp = (((int)line[i] - 48) * 10) + (int)line[i+1] - 48;
			if(temp == 550){
				temp = -1;
			}
			board[size][i / 3] = temp;
		}
		size++;
	}
	for(int i = 0; i < lineCapacity; i++){
		if(line[i] == '\n' || line[i] == '\0'){
			width++;
			break;
		}
		else{
			width++;
		}
	}
	width = width / 3;
	inFile.close();
}
//Optional Loading
int LoadCurrent( int board[9][9], int& size, int& width, const char* argv){
	string fileName = argv;
	ifstream inFile;
	const int lineCapacity = 30;
	char line[lineCapacity];
	
	inFile.open(fileName);
	
	if( inFile.fail()){
		cout << "failed\n";
		return 0;
	}
	
	//Reset the board for reloading..
	size = 0;
	width = 0;
	int temp;
	while(!inFile.eof()){
		inFile.getline(line, lineCapacity);
		
		for(int i = 0; i < lineCapacity; i = i + 3){
			temp = (((int)line[i] - 48) * 10) + (int)line[i+1] - 48;
			if(temp == 550){
				temp = -1;
			}
			board[size][i / 3] = temp;
		}
		size++;
	}
	for(int i = 0; i < lineCapacity; i++){
		if(line[i] == '\n' || line[i] == '\0'){
			width++;
			break;
		}
		else{
			width++;
		}
	}
	width = width / 3;
	inFile.close();
	return 1;
}
//Save current board
void SaveCurrent(const int puzzle[9][9], const int size, const int width){
	ofstream outFile;
	string saveFileName;
	cout << "Enter the name of the file to be saved: ";
	cin >> saveFileName;
	outFile.open(saveFileName);
	
	for(int i = 0; i < size; i++){
		for(int j = 0; j < width; j++){
			if(puzzle[i][j] < 10 && puzzle[i][j] != -1 && j != width - 1){
				outFile << "0" << puzzle[i][j] << " ";
			}
			else if(puzzle[i][j] < 10 && puzzle[i][j] != -1 && j == width - 1){
				outFile << "0" << puzzle[i][j];
			}
			else if(puzzle[i][j] == -1 && j != width - 1){
				outFile << "bb ";
			}
			else if(puzzle[i][j] == -1 && j == width - 1){
				outFile << "bb";
			}
			else if( j == width - 1){
				outFile << puzzle[i][j];
			}
			else{
				outFile << puzzle[i][j] << " ";
			}
		}
		if( i != size - 1){
			outFile << "\n";
		}
	}
	cout << "SUCCESFULLY SAVED!\n\n";
	outFile.close();
}

//Shows puzzle
void ShowPuzzle(const int puzzle[9][9], const int size, const int width){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < width; j++){
			if(puzzle[i][j] < 10 && puzzle[i][j] != -1){
				cout << "0" << puzzle[i][j] << " ";
			}
			else if(puzzle[i][j] == -1){
				cout << "bb ";
			}
			else{
				cout << puzzle[i][j] << " ";
			}
		}
		cout << "\n";
	}
	cout << endl;
}
//If there is no arg, it will generate a board according to its size and width.
void BoardInit(int puzzle[9][9], const int size, const int width){
	int x = 1;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < width; j++){
			if( i == size -1 && j == width - 1){
				puzzle[i][j] = -1;
			}
			else{
				puzzle[i][j] = x;
				x++;
			}
		}
	}
	Shuffle(puzzle, size, width);
}
//it transfer blank space to one direction to the top.
void UpMove(int board[9][9], int size, int width){
	int x, y;
	FindBlankSpace(board, size, width, x, y);
	if( x == 0){
		cout << "Error: There is no blank space at the top\n" << endl;
		return; 
	}
	else if( board[x-1][y] == 0){
		cout << "Error: You can't move that direction because there is a wall over there\n" << endl;
		return;
	}
	board[x][y] = board[x-1][y];
	board[x-1][y] = -1;
}
//it transfer blank space to one direction to the down.
void DownMove(int board[9][9], int size, int width){
	int x, y;
	FindBlankSpace(board, size, width, x, y);
	if( x == size -1){
		cout << "Error: There is no blank space at the bottom\n" << endl;
		return; 
	}
	else if( board[x+1][y] == 0){
		cout << "Error: You can't move that direction because there is a wall over there\n" << endl;
		return;
	}
	board[x][y] = board[x+1][y];
	board[x+1][y] = -1;
}
//it transfer blank space to one direction to the left
void LeftMove(int board[9][9], int size, int width){
	int x, y;
	FindBlankSpace(board, size, width, x, y);
	if( y == 0){
		cout << "Error: There is no blank space on the left\n" << endl;
		return; 
	}
	else if( board[x][y-1] == 0){
		cout << "Error: You can't move that direction because there is a wall over there\n" << endl;
		return;
	}
	board[x][y] = board[x][y-1];
	board[x][y-1] = -1;
}
//it transfer blank space to one direction to the right.
void RightMove(int board[9][9], int size, int width){
	int x, y;
	FindBlankSpace(board, size, width, x, y);
	if( y == width - 1){
		cout << "Error: There is no blank space on the right\n" << endl;
		return; 
	}
	else if( board[x][y+1] == 0){
		cout << "Error: You can't move that direction because there is a wall over there\n" << endl;
		return;
	}
	board[x][y] = board[x][y+1];
	board[x][y+1] = -1;
}
//it locates the blank space on the place because i needed to its coordinates.
void FindBlankSpace(int board[9][9], int size, int width, int& x, int& y){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < width; j++){
			if( board[i][j] == -1){
				x = i;
				y = j;
				return;
			}
		}
	}
}
//to check board is finished 
int IsCorrectBoard(const int board[9][9], const int size, const int width){
	int count = 1;
	int numberOfCorrects = 0;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < width; j++){
			if( board[i][j] == 0){
				numberOfCorrects++;
			}
			else{
				if(board[i][j] == count){
					numberOfCorrects++;
				}
				
				count++;
			}
		}
	}
	return numberOfCorrects;
}

//it runs like restart the game, it shows the final solution and resets the game.
void Shuffle(int board[9][9], const int size, const int width){
	int count = 1;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < width; j++){
			if(board[i][j] != 0){
				board[i][j] = count;
				count++;
			}
		}
	}
	//BlankSpace
	board[size-1][width-1] = -1;
	
	int moves = 0;
	int randomDirection;
	int x, y;
	srand(time(NULL));
	while(moves != size * width){
		FindBlankSpace(board,size,width,x,y);
		randomDirection = rand() % 4;
		if(randomDirection == 0 && x != 0 && board[x-1][y] != 0){
			UpMove(board, size, width);
		}
		else if(randomDirection == 1 && y != width -1 && board[x][y+1] != 0){
			RightMove(board, size, width);
		}
		else if(randomDirection == 2 && x != size -1 && board[x+1][y] != 0){
			DownMove(board, size, width);
		}
		else if(randomDirection == 3 && y != 0 && board[x][y-1] != 0){
			LeftMove(board, size, width);
		}
		else{
			moves--;
		}
		moves++;
	}
}
//hw1 algorithm
void IntelligentMove(int board[9][9], int size, int width){
	int x, y;
    int whereToGo;
    FindBlankSpace(board, size, width, x,y);
	
	whereToGo = WhereIsBest(board, size, width, x, y);
    //If there is a match for cell to move
    switch(whereToGo){
        case 0: UpMove(board, size, width); cout << "AI chosed upmove.\n";
        break;
        case 1: LeftMove(board, size, width); cout << "AI chosed leftmove.\n";
        break;
        case 2: RightMove(board, size, width); cout << "AI chosed rightmove.\n";
        break;
        case 3: DownMove(board, size, width); cout << "AI chosed downmove.\n";
        break;
        default: cout << "Unable to calculate\n";
    }
}
//it makes every possible move and calculates their manhattan distances. after that, it returns minimum possible choice
int WhereIsBest(int board[9][9], int size, int width, int x, int y){
	int piece[4] = {1000,1000,1000,1000};
	
	if( x != 0 && board[x-1][y] != 0){
		UpMove(board, size, width);
		piece[0] = ManhattanDistance(board, size, width);
		DownMove(board, size, width);
	}
	if( y != 0 && board[x][y-1] != 0){
		LeftMove(board, size, width);
		piece[1] = ManhattanDistance(board, size, width);
		RightMove(board, size, width);
	}
	if( y != width -1 && board[x][y+1] != 0){
		RightMove(board, size, width);
		piece[2] = ManhattanDistance(board, size, width);
		LeftMove(board, size, width);
	}
	if( x != size -1 && board[x+1][y] != 0){
		DownMove(board, size, width);
		piece[3] = ManhattanDistance(board, size, width);
		UpMove(board, size, width);
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
//to locate where the wrongPiece should be
void TruePosition(const int board[9][9], const int size, const int width, const int wrongPiece, int& x, int& y){
	int count = 1;
	int i, j;
	for( i = 0; i < size; i++){
		for( j = 0; j < width; j++){
			if( board[i][j] == wrongPiece){
				x = i - 1;
				y = j - 1;
				return;
			}
			if( board[i][j] != 0 ){
				count++;
			}
		}
	}
	
}
//to find what value should be on the tile board[x][y]
int TrueValue(const int board[9][9], const int size, const int width, const int x, const int y){
	int count = 1;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < width; j++){
			if(board[i][j] != 0){
				count++;
			}
			if( i == x && j == y){
				return count;
			}
		}
	}
}
//It returns the total distance of all wrong tiles to their true coordinates.
int ManhattanDistance(int board[9][9], int size, int width){
	int distance = 0, count = 1;
	int wrongPiece, lineerConflicts = 0;
	int x,y;
	
	//to get the real coordinates of the tile and how many spaces needed to go to there from current position
	for(int i = 0; i < size; i++){
		for(int j = 0; j < width; j++){
			if(board[i][j] != 0){
				if( board[i][j] != count && board[i][j] != -1 && (i != size -1 || j != width -1)){
					wrongPiece = board[i][j];
					TruePosition(board, size, width, wrongPiece, x, y);
					distance += abs(x - i) + abs(y - j);
				}
				count++;
			}
		}
	}
	//Lineer Conflict is may be unnecessary but i want to use it any case. It logic works like this:
	// RandomPuzzle:
	//	1	3	2			In this example, to get the solution 3 needs to be in the location where is in the 2 value and also 2 needs to be
	//	4		5		in the location where is in the 3 value. It makes harder to get the solution so i tried to avoid them.
	//	6	7	8
	for(int i = 0; i < size; i++){
		for(int j = 0; j < width; j++){
			if( i != 0 ){
				x = i -1;
				y = j;
				TruePosition(board, size, width, board[i][j], x, y);
				if( board[i][j] == TrueValue(board, size, width, i-1, j) && (x == i && y == j)){
					lineerConflicts++;
				}
			}
			if( j != 0 ){
				x = i;
				y = j - 1;
				TruePosition(board, size, width, board[i][j], x, y);
				if( board[i][j] == TrueValue(board, size, width, i, j-1) && (x == i && y == j)){
					lineerConflicts++;
				}
			}
			if( j != width - 1 ){
				x = i;
				y = j + 1;
				TruePosition(board, size, width, board[i][j], x, y);
				if( board[i][j] == TrueValue(board, size, width, i, j+1) && (x == i && y == j))
					lineerConflicts++;
			}
			if( i != size - 1 ){
				x = i + 1;
				y = j;
				TruePosition(board, size, width, board[i][j], x, y);
				if( board[i][j] == TrueValue(board, size, width, i+1, j) && (x == i && y == j)){
					lineerConflicts++;
				} 
			}
		}
	}
	distance += lineerConflicts * 2;
	
	return distance;
}
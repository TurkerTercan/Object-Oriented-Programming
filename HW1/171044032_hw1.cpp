//*************			TURKER		TERCAN		171044032		HW1		CSE241	OOP				 *************//
#include <iostream>
using namespace std;

//These four functions provide us to move the cell.
void UpMove(int [9][9], int); 
void RightMove(int [9][9], int);
void DownMove(int [9][9], int);
void LeftMove(int [9][9], int);

void IntelligentMove(int puzzle[9][9], int size, int moves, int *lastMove); //get solved the puzzle by ai
void FindCell(int [9][9], int , int *, int *); //it finds the empty cell on the puzzle
void PuzzleMix(int puzzle[9][9], int size); //to get mixed puzzle
void PuzzleInit(int puzzle[9][9], int size); //to initilalize it
void ShowPuzzle(int puzzle[9][9], int size); //to show the puzzle
void Shuffle(int puzzle[9][9], int size); //it shows the solution and than shuffles it
int isCorrect(int puzzle[9][9], int size); //it return how many matched pieces are there on the puzzle
int ChecksAnyMatch(int puzzle[9][9], int x, int y, int size, int moves, int *lastMove); //ai func

int main(){
    int size;
    int moves = 0; //how many moves to get the solution
    char choice; 
    int puzzle[9][9]; //puzzle board
    int lastMove;
    
    cout << "Please enter the problem size: ";
    cin >> size;
    
    PuzzleInit(puzzle, size);
    cout << "Your initial random board is\n";
    ShowPuzzle(puzzle, size);
    
    while( isCorrect(puzzle, size) != (size * size) - 1){
        cout << "Your move: ";
		cin >> choice;
        
        switch(choice){
            case 'L': LeftMove(puzzle, size);
            break;
            case 'U': UpMove(puzzle, size);
            break;
            case 'R': RightMove(puzzle, size);
            break;
            case 'D': DownMove(puzzle, size);
            break;
            case 'I': IntelligentMove(puzzle, size, moves, &lastMove);
            break;
            case 'S': Shuffle(puzzle, size);
            moves = 0;
            break;
            case 'Q': return 0;
            break;
            default: cout << "Invalid choice!\n";
        }
        moves++;
        ShowPuzzle(puzzle, size);
    }
    cout << "Problem Solved!\n" <<  "Total number of moves " << moves << "\n";
    return 0;
}


void PuzzleMix(int puzzle[9][9], int size){
    int x, y; 
    srand(time(NULL));
    int count = 0;
    int choice;
	//to get the puzzle without unsolvable situations, i used to move blank space size * size times arond on the puzzle.
    while( count < (size * size)){
        FindCell(puzzle, size, &x, &y);
        choice = rand() % 4;
        if(choice == 0 && x != size - 1){
            DownMove(puzzle, size);
        }
        else if(choice == 1 && x != 0){
            UpMove(puzzle,size);
        }
        else if(choice == 2 && y != size - 1){
            RightMove(puzzle, size);
        }
        else if(choice == 3 && y != 0){
            LeftMove(puzzle, size);
        }
        else{
            count--; //If cell does not move, i'll be sure that is not counted for.
        }
        count++;
    }
}
//this function helps to get 1 to size -1 puzzle creation
void PuzzleInit(int puzzle[9][9], int size){
    int x = 1;
    for(int i = 0; i < size ; i++){
        for(int j = 0; j < size; j++){
            puzzle[i][j] = x;
            x++;
            x = x % (size * size);
        }
    }
    PuzzleMix(puzzle, size);
}

//Prints the puzzle to console
void ShowPuzzle(int puzzle[9][9], int size){
    for(int i = 0; i < size; i++){
        for(int a = 0; a < size; a++){
            cout << "----";
        }
        cout << "-\n";
        for(int j = 0; j < size; j++){
            cout << "| ";
            if( puzzle[i][j] == 0){
                cout << "  ";
            }
            else{
                if(puzzle[i][j] >= 10){
                    cout << puzzle[i][j];
                }
                else{
                    cout << puzzle[i][j] << " ";
                }
            }
        }
        cout << "|\n";
    }
    for(int a = 0; a < size; a++){
            cout << "----";
    }
    cout << "\n";
}

//how many true pieces in the current puzzle to get the solution
int isCorrect(int puzzle[9][9], int size){
    int x = 1;
    int count = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(puzzle[i][j] == x){
                count++;
            }
            x++;
        }
    }
    return count;
}

//it runs like restart the game, it shows the final solution and resets the game.
void Shuffle(int puzzle[9][9], int size){
    int x = 1; 
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            puzzle[i][j] = x;
            x++;
            x = x % (size * size);
        }
    }
    
    cout << "Final Solution" << endl;
    ShowPuzzle(puzzle, size);
    PuzzleMix(puzzle, size);
}
//it locates the blank space on the place because i needed to its coordinates.
void FindCell(int puzzle[9][9], int size, int *x, int *y){
    for(int i = 0; i < size; i++){
        for(int j = 0 ; j < size; j++){
            if(puzzle[i][j] == 0){
                *x  = i;
                *y = j;
                return;
            }
        }
    }
}
//it transfer blank space to one direction to the left.
void LeftMove(int puzzle[9][9], int size){
    int x,y;
    FindCell(puzzle, size, &x, &y);
    if( y == 0 ){
        cout << "There is no room on the left side.\n";
        return; 
    }
    puzzle[x][y] = puzzle[x][y-1];
    puzzle[x][y-1] = 0;
}
//it transfer blank space to one direction to the right.
void RightMove(int puzzle[9][9], int size){
    int x,y;
    FindCell(puzzle, size, &x, &y);
    if( y == size - 1 ){
        cout << "There is no room on the right side.\n";
        return; 
    }
    puzzle[x][y] = puzzle[x][y+1];
    puzzle[x][y+1] = 0;
}
//it transfer blank space to one direction to the top.
void UpMove(int puzzle[9][9], int size){
    int x,y;
    FindCell(puzzle, size, &x, &y);
    if( x == 0 ){
        cout << "There is no room on the up side.\n";
        return; 
    }
    puzzle[x][y] = puzzle[x-1][y];
    puzzle[x-1][y] = 0;
}
//it transfer blank space to one direction to the down.
void DownMove(int puzzle[9][9], int size){
    int x,y;
    FindCell(puzzle, size, &x, &y);
    if( x == size - 1 ){
        cout << "There is no room on the down side.\n";
        return; 
    }
    puzzle[x][y] = puzzle[x+1][y];
    puzzle[x+1][y] = 0;
}

//It returns the total distance of all wrong tiles to their true coordinates.
int ManhattanDistance(int puzzle[9][9], int size){
    int distance = 0;
    int count = 1;
    int wrongPiece, x, y, lineerConflicts = 0;
    
	//to get the real coordinates of the tile and how many spaces needed to go to there from current position
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if( puzzle[i][j] != count && ( i != size -1 || j != size -1) && puzzle[i][j] != 0){
                wrongPiece = puzzle[i][j];
                //it needs to locate where it should be
                wrongPiece -= 1;
                x = ( wrongPiece / size);
                wrongPiece = wrongPiece - ( x * size);
                y = wrongPiece;
                
                distance += abs(x - i) + abs(y - j);
            }
            count++;
        }
    }
    
	//Lineer Conflict is may be unnecessary but i want to use it any case. It logic works like this:
	// RandomPuzzle:
	// 1	3	2			In this example, to get the solution 3 needs to be in the location where is in the 2 value and also 2 needs to be
	//	4		5		in the location where is in the 3 value. It makes harder to get the solution so i tried to avoid them.
	//	6	7	8
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            
            if( i != 0){
                if(puzzle[i][j] == ( i -1) *size + j + 1 && puzzle[i-1][j] == puzzle[i][j])
                    lineerConflicts++;
            }
            if( j != 0){
                if(puzzle[i][j] == i *size + j  && puzzle[i][j-1] == puzzle[i][j])
                    lineerConflicts++;
            }
            if( j != size -1){
                if(puzzle[i][j] == i *size + j + 2 && puzzle[i][j+1] == puzzle[i][j])
                    lineerConflicts++;
            }
            if( i != size -1){
                if(puzzle[i][j] == ( i +1) *size + j + 1 && puzzle[i+1][j] == puzzle[i][j])
                    lineerConflicts++;
            }
        }
    }
    
    distance = distance + 2*lineerConflicts;
    
    return distance;
}

int ChecksAnyMatch(int puzzle[9][9], int x, int y, int size, int moves, int *lastMove){
	//I used last move to get sure it will not be able to go back the choice.
    int piece[4] = {1000,1000,1000,1000};	//if there is not a value in there, i will be sure that it cant be counted for a min value.
    srand(time(NULL));
    int randN = rand() % 4; //to get the random solution in any case.
    
	//to check all possibilities for which one is more optimal and to check it i used ManhattanDistance function.
    if(x != 0 && *lastMove != 3){//up side is not empty
        UpMove(puzzle, size);
        piece[0] = ManhattanDistance(puzzle, size);
        DownMove(puzzle,size);
    }
    if(y != 0 && *lastMove != 2){//left side is not empty
        LeftMove(puzzle, size);
        piece[1] = ManhattanDistance(puzzle, size);
        RightMove(puzzle,size);
    }
    if(y != size -1 && *lastMove != 1){//right side is not empty
        RightMove(puzzle,size);
        piece[2] = ManhattanDistance(puzzle, size);
        LeftMove(puzzle, size);
    }
    if(x != size -1 && *lastMove != 0){//down side is not empty
        DownMove(puzzle,size);
        piece[3] = ManhattanDistance(puzzle, size);
        UpMove(puzzle, size);
    }
    int result = randN;
    int min =  piece[randN];
    int dir[4];
    int count = 0;
    
    //if there is more than one minimum, it randomly chooses between minimums.
	for(int i = 0; i < 4 ; i ++){
		if(piece[i] < min){
			min = piece[i];
		}
	}
	for(int i = 0; i < 4 ; i ++){
		if(piece[i] == min){
			dir[count] = i;
			count++;
		}
	}
    
    result = dir[rand() % count];
    
    *lastMove = result;
    return result;
}

void IntelligentMove(int puzzle[9][9], int size, int moves, int *lastMove){
    int x, y;
    int whereToGo;
    FindCell(puzzle, size, &x, &y);
    //If there is a match for cell to move
    whereToGo = ChecksAnyMatch(puzzle,x,y,size, moves, lastMove);
    switch(whereToGo){
        
        case 0: UpMove(puzzle, size);
        break;
        case 1: LeftMove(puzzle, size);
        break;
        case 2: RightMove(puzzle, size);
        break;
        case 3: DownMove(puzzle, size);
        
        break;
        default: cout << "Unable to calculate\n";
    }
}



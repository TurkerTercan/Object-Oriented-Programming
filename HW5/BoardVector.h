//*************			TURKER		TERCAN		171044032		HW4		CSE241	OOP				 *************//

#ifndef BOARDVECTOR_H
#define BOARDVECTOR_H

//Declarations for BoardArray

#include <iostream>
#include <vector>
#include <fstream>
#include "AbstractBoard.h"

using namespace std;

namespace TurkerTercanHW5{

	class BoardVector : public AbstractBoard{
	public:
		BoardVector();
		BoardVector(int, int);
		BoardVector(const AbstractBoard&);
		~BoardVector();
		BoardVector& operator=(const AbstractBoard& );
		void readFromFile(istream&) override;
		void move(char) override;
		int* getBoard() const override;
		int operator ()(int, int) const override;
		void randomMoves() override;
		void setTile(int, int, int) override;
		void initializeVectorBoard();
		int getTile(int, int) const override;
	private:
		bool check() const;
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void swapBlank(int, int);
		vector <vector <int>> board;
	};
}
#endif //BOARDVECTOR_H
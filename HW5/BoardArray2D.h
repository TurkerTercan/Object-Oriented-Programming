//*************			TURKER		TERCAN		171044032		HW4		CSE241	OOP				 *************//

//Declarations for BoardArray2D
#ifndef BOARDARRAY2D_H
#define BOARDARRAY2D_H

#include <iostream>
#include <fstream>
#include "AbstractBoard.h"

using namespace std;

namespace TurkerTercanHW5{

	class BoardArray2D : public AbstractBoard {
	public:
		BoardArray2D();
		BoardArray2D(int, int);
		BoardArray2D(const AbstractBoard&);
		BoardArray2D& operator =(const AbstractBoard&);
		~BoardArray2D();
		
		void readFromFile(istream&) override;
		void move(char) override;
		int* getBoard() const override;
		int operator ()(int, int) const override;
		void randomMoves() override;
		void setTile(int, int, int) override;
		int getTile(int, int) const override;

	private:
		bool check() const;
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void swapBlank(int, int);
		int** board;
		
	};
}
#endif //BOARDARRAY2D_H
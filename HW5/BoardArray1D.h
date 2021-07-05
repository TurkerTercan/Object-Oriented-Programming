//*************			TURKER		TERCAN		171044032		HW4		CSE241	OOP				 *************//

//Declarations for BoardArray1D
#ifndef BOARDARRAY1D_H
#define BOARDARRAY1D_H

#include <iostream>
#include <fstream>
#include "AbstractBoard.h"

using namespace std;

namespace TurkerTercanHW5{
	class BoardArray1D : public AbstractBoard
	{
	public:
		BoardArray1D();
		BoardArray1D(int, int);
		BoardArray1D(const AbstractBoard&);
		BoardArray1D& operator =(const AbstractBoard&);
		~BoardArray1D();
		
		void readFromFile(istream&) override;
		void move(char) override;
		int* getBoard() const override;
		int operator ()(int, int) const override;
		void setTile(int, int, int) override;
		void randomMoves() override;
		int getTile(int, int) const override;

	private:
		bool check() const;
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void swapBlank(int, int);
		int* board;
	};
}
#endif //BOARDARRAY1D_H
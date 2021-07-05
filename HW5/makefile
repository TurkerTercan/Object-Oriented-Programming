all: hw5

hw5: BoardVector.o AbstractBoard.o driver.o BoardArray2D.o BoardArray1D.o
	g++ -Wall -o hw5  AbstractBoard.o driver.o BoardVector.o BoardArray2D.o BoardArray1D.o

BoardVector.o: BoardVector.cpp BoardVector.h 
	g++ -std=c++11 -Wall BoardVector.cpp -c

AbstractBoard.o: AbstractBoard.cpp AbstractBoard.h
	g++ -Wall AbstractBoard.cpp -c
	
BoardArray2D.o: BoardArray2D.cpp BoardArray2D.h
	g++ -std=c++11 -Wall BoardArray2D.cpp -c
	
BoardArray1D.o: BoardArray1D.cpp BoardArray1D.h
	g++ -std=c++11 -Wall BoardArray1D.cpp -c
	
driver.o:  driver.cpp
	g++ -std=c++11 -Wall -c driver.cpp
	
clean:
	rm *.o 
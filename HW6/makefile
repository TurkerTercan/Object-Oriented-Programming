all: hw6

hw6: gtuiterator.o gtuiteratorconst.o main.o gtuset.o gtuvector.o gtucontainer.o
	g++ -std=c++11 -Wall -o hw6  gtuiterator.o gtuiteratorconst.o main.o gtuset.o gtuvector.o gtucontainer.o

gtuiterator.o: gtuiterator.cpp gtuiterator.h 
	g++ -std=c++11 -Wall gtuiterator.cpp -c

gtuiteratorconst.o: gtuiteratorconst.cpp gtuiteratorconst.h
	g++ -std=c++11 -Wall gtuiteratorconst.cpp -c
	
gtuset.o: gtuset.cpp gtuset.h
	g++ -std=c++11 -Wall gtuset.cpp -c
	
gtuvector.o: gtuvector.cpp gtuvector.h
	g++ -std=c++11 -Wall gtuvector.cpp -c

gtucontainer.o: gtucontainer.cpp gtucontainer.h
	g++ -std=c++11 -Wall gtucontainer.cpp -c

main.o:  main.cpp
	g++ -std=c++11 -Wall -c main.cpp
	
clean:
	rm *.o 

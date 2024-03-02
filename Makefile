main: main.o DoublyLinkedList.o
	g++ -o main main.o DoublyLinkedList.o

main.o: main.cpp
	g++ -c -g -Wall -std=c++14 -pedantic-errors main.cpp

DoublyLinkedList.o: DoublyLinkedList.h DoublyLinkedList.cpp
	g++ -c -g -Wall -std=c++14 -pedantic-errors DoublyLinkedList.cpp

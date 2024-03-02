/*
This is the DoublyList.h file. It defines all the methods and variables that will be used implemented in the code
*/


#ifndef DOUBLYLINKEDLIST
#define DOUBLYLINKEDLIST

#include <iostream>

using namespace std;

// struct for NodeType
template <typename T>
struct NodeType {
  T data;
  NodeType<T>* next;
  NodeType<T>* back;
};

// DoublyLinkedList class

template <typename T>
class DoublyLinkedList {

public:

  DoublyLinkedList(); //constructor

  ~DoublyLinkedList(); //destructor

  int lengthIs() const; //lenghtis code

  void insertItem(T& item); // This method inserts an item

  void deleteItem(T& item); // This method deletes an item

  void deleteIndexItem(int itemIndex); // This deletes the index of an item

  T searchItem(int itemIndex); // this method searches for an item

  void print(); // this method prints the list

  void printReverse(); // this method prints the list in reverse

  void deleteSubsection(T& lower, T& upper); // this method deletes a subsection based on upper and lower bounds the user gives

  T mode(); // this method returns the mode of the list

  void swapAlternate();// thia methods swaps the two adjacent values 
  
private:

  NodeType<T>* head; // this is the head value

  NodeType<T>* tail; // this is the tail value of the list

  int length; // this is the length value
};
#endif

#include <iostream>
#include "DoublyLinkedList.h"
#include <string>
#include <iostream>
#include <ostream>
#include <cstddef>

using namespace std;

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() { //constructor 
  head = nullptr;
  tail = nullptr;
  length = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() { //deconstructor 
  NodeType<T>* current = nullptr;

  while (head != nullptr && tail != nullptr) { 
    current = head;
    head = head->next;
    delete current;
  }

  tail = nullptr;
}

template <typename T>
int DoublyLinkedList<T>::lengthIs() const {  //method gets length
  return length;
}

template <typename T>
void DoublyLinkedList<T>::insertItem(T& item) { // method inserts item 
  NodeType<T>* node = new NodeType<T>; // creates node 
  NodeType<T>* current = head; // cretes current 
    
  node->data = item;
  node->next = nullptr;
  node->back = nullptr;
    
  if (head == nullptr && tail == nullptr) { //checks is list is empty 
    head = node;  //adds new node
    tail = node; // adds new node
	
    length++; //increases length 
    return;
  }
    
  bool isDuplicate = false;
  while (current != nullptr) {
    if (item > current->data)
      current = current->next;
    //duplicate item
    // else if(item == current->data) {
    // cout << endl;
    //cout << "Item already exists" << endl;
    //isDuplicate = true;

    //delete node;
    //break;
    //}
	
    else // found the location to insert item
      break;
  }
  //inserted as last element
  if(current == nullptr && !isDuplicate) { 
    tail->next = node; //inserts
    node->back = tail;
    tail = node;
	
    length++;
  }

  // inserting at beginning 
  else if(current->back == nullptr && !isDuplicate) {
    node->next = current;  //inserts
    current->back = node;
    head = node;

    length++;
  }
  //general-case
  else if(!isDuplicate) { 
    node->back = current->back; // relaized that we didnt need to check dupilcate 
    current->back->next = node;
    node->next = current; //inserts 
    current->back = node;

    length++;
  }
}

template <typename T>
void DoublyLinkedList<T>::deleteItem(T& item) { //this method deletes item 
  NodeType<T>* current = head;

  if (head == nullptr && tail == nullptr) { //checks if empty list 
    cout << endl;
    cout << "You cannot delete from an empty list." << endl;

    return;
  }

  if ((item == current->data) && (current->next != nullptr)) { //deleting the first item
    current->next->back = nullptr;
    head = current->next;
    length--;
    delete current;
    return;
  }

  // deleting the only item
  if ((item == current->data) && (current->next == nullptr)) {
    head = nullptr;
    tail = nullptr;
    length--;
    delete current;
    return;
  }

  if (item == tail->data) { // deleting the last item
    NodeType<T>* tempNode = tail->back;

    tempNode->next = nullptr;

    length--;
    delete tail;
    tail = tempNode;
    return;
  }

  bool isFound = false;
    
  while (current != nullptr) {
    if (item > current->data) { // keep going
      current = current->next;
    }

    else if(item == current->data) { // item found
      isFound = true;	    
      break;
    }

    else 
      break;
  }

  if (isFound) { //general-case delete
    current->back->next = current->next;
    current->next->back = current->back;
    length--;
	
    delete current;
  }

  else { // item not found
    cout << endl;
    cout << "Item not in list!" << endl;
  }
}

template <typename T>
void DoublyLinkedList<T>::deleteIndexItem(int itemIndex) {
  T item = searchItem(itemIndex); //find item at index
  deleteItem(item); //delete item and the index
}
/*
  This function is a helper function that we use to supplement/help the other methods 
*/
template <typename T>
T DoublyLinkedList<T>::searchItem(int itemIndex) { // this method searches item 
  T item; // creates generic item 
    
  // index is out of bounds or empty list 
  if((itemIndex < 0) || (itemIndex > length-1) || (head == nullptr && tail == nullptr))
    return item; 

  NodeType<T>* current = head; 

  int i = 0;
  while(current != nullptr) {	 // while loop
    if(i == itemIndex) // found item
      return current->data; 

    current = current->next; // sets next node as current 
    i++;
  }

  return item; // returns search 
}

template <typename T>
void DoublyLinkedList<T>::print() { //This method will print the list
  NodeType<T>* current = head; // starts by defining current as head, front of the list

  while(current != nullptr) { // will make sure we go thru the entire list
    cout << current->data << " "; // prints each node

    current = current->next; //sets to next node 
  }

  cout << endl;
}
/*
  The print reverse methods works very similarly to the print method. Except we set the current node to tail instead of head.
*/
template <typename T>
void DoublyLinkedList<T>::printReverse() { //This is the print reverse method which prints the list in reverse
  NodeType<T>* current = tail; //start by setting current Node to tail 

  while(current != nullptr) { // make sure we go thru the entire list
    cout << current->data << " " ; //prints current node
 
    current = current->back; //instead of going foward to the next node we go backwards  
  }

  cout << endl;
}

template <typename T>
void DoublyLinkedList<T>::deleteSubsection(T& lower, T& upper){ // this is Delete Subsection method 
  NodeType<T> *current;
  
  if (head==NULL){ //returns if theres no values 
    return;
  }
  
  if (head->data > upper){ // if the first value is greater then our upper, nothing is returned
    return; 
  }
  
  if (tail->data < lower){ //if the last value is less than the lower nothing is returned 
    return;
  }
  
  current = head; // create current 
  while (current != nullptr && current->data<lower){ // make sure we go to the list till lower 
    current = current->next; 
  }
  
  if (current != nullptr){ // makes sure the current is not null
    if (current->back == nullptr && current->next == nullptr){ 
      head = nullptr;
      tail = nullptr;
      free(current); // will get rid of uncessary nodes 

      return;
    }
    else if (current->back == nullptr){ // checks if last node is not null
      head = head->next;
      head->back = nullptr;
      free(current); 
      deleteSubsection(lower, upper); // uses recursion to recall the method 

      return;
    }
    else if (current->next == nullptr){ // once again repeats and checks if the next val is not a null
      tail = tail->back; // tail goes back one node
      tail->next = nullptr;
      free(current); // rid of unesscary nodes 

      return;
    }
    else {
      NodeType<T> *val = tail; // defines tail value 

      while (val != nullptr && val->data>upper){  // makes sure we go through the subsection 
	val = val->back;
      }
      
      if (val->next == current){ 
	return;
      }
      else{
	current->back->next = val->next; // moves nodes for current and val 

	if (val->next != nullptr){
	  val->next->back = current->back;
	}
	NodeType<T> *temp; //new node type temp 

	while (current != val){ //checks if val is null
	  temp = current; 
	  current = current->next;
	  free(temp);
	}
	free(current);
      }
      return;
    }
  }
}

template <typename T>
T DoublyLinkedList<T>::mode() { // this function returns the mode of the list(most appeared value on the list)
  T mode = 0; // intializes varaibles that will be used in the methid 
  int val = 0;
  int count = 0;
  
  if (head == nullptr){ // checks if list is empty and returns 0 if it is
    return mode;
  }
  
  NodeType<T> *current = head->next; //defines the current node
  mode = head->data; // sets value for mode
  T last = head->data; // creates another node type variable 
  val = 1;
  count = 1;

  while (current != nullptr){ //loop to make sure we go thru the entire list 
    if (current->data == current->back->data){ //if that checks for multiple values 
      count++;
    }
    else{
      if(count > val){ // finds a count for each val 
	val = count;
	count = 1;
	mode = last; 
      }
    }
    last = current->data; 
    current = current->next;
  }

  return mode; //returns mode 
}

template <typename T>
void DoublyLinkedList<T>::swapAlternate() { //this is the method for Swap alternate which swaps the value for every two adajcent nodes 
  if (head == nullptr || head == tail){ // checks to make sure that the list isnt empty and that there is more than one node 
    return;
  }
  NodeType<T> *current = head; // sets current to first valuse
  NodeType<T> *last = nullptr; //sets last to null 
  while (current != nullptr && current->next != nullptr) { // current is not empty and the next is empty 
    NodeType<T> *temp = current->next; // sets temp 
    current->next = temp->next; // gets the next value for current and next 

    if (temp->next != nullptr){ // checks if next node value is not null
	temp->next->back = current;
      }
    temp->next = current; // switches 
      current->back = temp;
         
      if (last == nullptr) { //checks if last value is null
	head = temp;
	temp->back = nullptr;
      }
      else {
	last->next = temp; 
	temp->back = last;
      }
         
      last = current;
      current = current->next;
    }
  
  if (current == nullptr){ // checks if last is null
    tail = last; //switches
  }
}

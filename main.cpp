#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <istream>

#include "DoublyLinkedList.h"
#include "DoublyLinkedList.cpp"

using namespace std;

//function prototype for reading the input file
template <typename T>
void readFile(DoublyLinkedList<T>& list, char* filename);

//function prototype for running the main interface
template <typename T>
void runInterface(DoublyLinkedList<T>& list, string type);

int main(int argc, char* argv[]) {

  // while loop that asks for list type and runs the function prototypes above accordingly
  bool startLoop = true;
  string inputType = "";
  
  while (startLoop) {
    cout << "Enter list type (i - int, f - float, s - std:string): ";
    getline(cin, inputType);
	
    cout << endl;

    if (inputType.compare("i") == 0) { //int
      DoublyLinkedList<int> list;

      readFile(list, argv[1]);
      runInterface(list, "Int");
      startLoop = false;
    }

    else if(inputType.compare("f") == 0) { //float
      DoublyLinkedList<float> list;
		    
      readFile(list, argv[1]);
      runInterface(list, "Float");
      startLoop = false;
    }

    else if(inputType.compare("s") == 0) { //std::string
      DoublyLinkedList<string> list;

      readFile(list, argv[1]);
      runInterface(list, "String");
      startLoop = false;
    }

    else { //invalid command found
      cout << "Invalid command, try again!" << endl;  
      cout << endl;
    }
  }
    
  return 0;
}

//function for reading the input file
template <typename T>
void readFile(DoublyLinkedList<T>& list, char* filename) {
  fstream fs;
    
  fs.open(filename, fstream::in);
	
  T inputValue;
  if(fs.is_open()) {
    fs >> inputValue;
	
    while(!fs.eof()) {
      list.insertItem(inputValue);
      fs >> inputValue;
    }

    fs.close();
  }
  else {
    cout << "Failed to open the input file" << endl;
    exit(1);
  }
}

//function for running the interface
template <typename T>
void runInterface(DoublyLinkedList<T>& list, string type) {
  //all command options available to user
  cout << "insert (i), delete (d), length (l), print (p), deleteSub (b), mode (m), printReverse (r), swapAtl (s), quit (q)" << endl;
  cout << endl;
    
  bool loop = true;
  char command = '\0';

  //while loop for main prgram
  while(loop) {
    cout << "Enter a command: ";
    cin >> command;
    cout << endl;
 
    switch(command) {
    case 'i': { //insert item
      T item;

      cout << type << " to insert: ";
      cin >> item;

      list.insertItem(item);
      
      cout << endl;
      list.print();
      cout << endl;
	    
      break;
    }	    
    case 'd': { //delete item
      T item;

      cout << type << " to delete: ";
      cin >> item;

      list.deleteItem(item);

      cout << endl;
      list.print();
      cout << endl;
	    
      break;
    }
    case 'l': { //length
      cout << "The length is: " << list.lengthIs() << endl;
      cout << endl;
	    
      break;
    }
    case 'p': { //printList
      list.print();
      cout << endl;
	    
      break;
    }
    case 'b': { //deleteSub
      T lower;
      T upper;
	  
      cout << "Enter lower bound: ";
      cin >> lower;
	  
      cout << "Enter upper bound: ";
      cin >> upper;

      cout << "Original List: ";
      list.print();
	  
      list.deleteSubsection(lower, upper);

      cout << "Modified  List: ";
      list.print();

      break;
    }
    case 'm': { //mode
      list.print();
      cout << "Mode: " << list.mode() << endl;

      break;
    }
    case 'r': { //printReverse
      list.printReverse();
      cout << endl;
	    
      break;
    }
    case 's': { //swapAlternate
      cout << "Original List: ";
      list.print();

      list.swapAlternate();
	  
      cout << "Swapped List: ";
      list.print();
      break;
    }
    case 'q': { //quit
      cout << "Quitting program..." << endl;
      cout << endl;
      loop = false;
      
      break;
    }
    default: //inavlid command
      cout << "Invalid command, try again!" << endl;	  
      cout << endl;
	    
      break;
    }
  }
}

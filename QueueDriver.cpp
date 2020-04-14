/*
Names: Tay Cavett, Josh Brown, Jalyn Cosby, Whittney Schwarz
Assignment: Project 3
Description: Create an interactive driver that will easily allow user to manipulate a queue. 
Your queue should have a list cursor (a pointer that points to the “current”  item in the list).  The user should be able to enter one command 
and arguments per line or the user should be able to stack commands.  Again, the list should be printed the line above the UI cursor,
so the user knows the current state of the queue.  
Class: CS 355-01
*/
#include <iostream>
#include <limits>
#include "Queue.h"
using namespace std;
void menu();
int main(){
	Queue<int> queue;
	
	char operation;
	int operand;
	bool run = true;
	
	menu();
	while(run){
		queue.PrintList();
		cout << endl;
		cin >> operation;
		
		switch(operation){
		    //Enqueue
			case '+':
				cin >> operand;
                if(cin.fail()){
                	cin.clear();
                	cin.ignore(numeric_limits<int>::max(),'\n');
                	cout << "Invalid input. + must be followed by an int." << endl;
				} else {
					cout << endl << "Enq(" << operand << ")" << endl;
					queue.Enq(operand);
				}
				break;
			
			//Dequeue
			case '-':
				cout << endl <<"Deq(): {" << queue.Deq() << "}" << endl;
				break;
			
			//Search
			case '?':
				cin >> operand;
				if(cin.fail()){
                	cin.clear();
                	cin.ignore(numeric_limits<int>::max(),'\n');
                	cout << "Invalid input. ? must be followed by an int." << endl;
				} else {
					cout << endl <<"Search(" << operand << "): ";
					if(queue.Search(operand))
						cout << "Found" << endl;
					else
						cout << "Not found" << endl;
				}
				break;
			
			//PrintList
			case 'P':
			case 'p':
			    cout << endl << "PrintList: ";
			    queue.PrintList(); cout << endl;
			    break;
			
			//PrintItem
			case '@':
			    cout << endl << "PrintItem: ";
			    queue.PrintItem(); cout << endl;
			    break;
			
			//Move(right)
            case '>':
                cout << endl << "Move(right): " << endl;
            	queue.Move(operation);
                break;
            
            //Move(left)
            case '<':
                cout << endl << "Move(left): " << endl;
                queue.Move(operation);
                break;
            
            //Move(begining)
            case 'B':
            case 'b':
                cout << endl << "Move(begining): " << endl;
                queue.Move(operation);
                break;
            
            //Move(end)
            case 'E':
            case 'e':
                cout << endl << "Move(end): " << endl;
                queue.Move(operation);
                break;
            case '1':
                  cout << "See attached file for testing." << endl;
                 break;
            case '2':
                 cout << "See attached file for testing." << endl;
                 break;
            case '3':
                 queue.~Queue();
                 cout << endl;
                 cout << "List destroyed" << endl;
                 break;
            //Print Main Menu
            case 'M':
            case 'm':
                menu();
                break;
            
            //Quit Program
            case 'Q':
        	case 'q':
        	    cout << endl << "Quitting..." << endl;
        		run = false;      //break the main loop
        		break;
        	
        	//Default Case/Invalid Input
			default:
				cout << endl <<"Not a valid menu option"<< endl;
				break;
		}
	}
	return 0;
}


//************************************
//Main Menu Print Function
void menu(){

   cout << "********************************************************" << endl;
   cout << "* +X  To Insert an Item.                               *" << endl;
   cout << "* -   To Remove an Item.                               *" << endl;
   cout << "* ?X  To Search for an item in the list.               *" << endl;
   cout << "* p   To print the list.                               *" << endl;
   cout << "* @   To Print the item at the cursor.                 *" << endl;
   cout << "* >   To Move the cursor to the right.                 *" << endl;
   cout << "* <   To Move the cursor to the left.                  *" << endl;
   cout << "* b   To Move the cursor to the beginning of the list. *" << endl;
   cout << "* e   To Move the cursor to the end  of the list.      *" << endl;
   cout << "* 1   To test the copy constructor.                    *" << endl;
   cout << "* 2   To test the assignment operator.                 *" << endl;
   cout << "* 3   To test the destructor.                          *" << endl; 
   cout << "* m   To display this menu.                            *" << endl;
   cout << "* Q  To quit the program                               *" << endl;
   cout << "********************************************************" << endl;
}



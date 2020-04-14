#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
using namespace std;


//************************************
//Templated Queue Class
template <class T>
class Queue;


//************************************
//QNode Class Declaration
//************************************
template <class T>
class QNode{
	T data;  
	
public: 

    QNode<T>* next;
    QNode<T>* prev;
    
    QNode(T d);
    QNode(T d, QNode<T>* n, QNode<T>* p);
    
    friend class Queue<T>;
};


//************************************
//QNode Class Implementation
//************************************
template <class T>
QNode<T>::QNode(T d):data(d), next(NULL), prev(NULL){}
template <class T>
QNode<T>::QNode(T d, QNode<T>* n, QNode<T>* p):data(d), next(n), prev(p){}


//************************************
//Queue Class Declaration
//************************************
template <class T>
class Queue{
    QNode<T>* front;
    QNode<T>* back;
    QNode<T>* cursor;
public:
	Queue();							//constructor
	Queue(const Queue<T>& src);			//copy constructor
	Queue<T>& operator=(const Queue<T>& q);	//assignment operator
	~Queue();							//destructor
	
    void Enq(T item);					//Enqueue
    T Deq();							//Dequeue
    bool Search(T item);				//Search
    void PrintList();					//Print list
    void PrintItem();					//Print item at cursor
    bool Move(char choice);				//Move the cursor in the chosen direction
};


//************************************
//Queue Class Implementation
//************************************


//************************************
//Queue Default Constructor
template <class T>
Queue<T>::Queue(){
	front = NULL;
	back = NULL;
	cursor = NULL;
}


//************************************
//Queue Copy Constructor
template <class T>
Queue<T>::Queue(const Queue<T>& src){
	if(src.front != NULL){									//if the source is not an empty list
		front = new QNode<T>(src.front->data);					//create first node at the front with the copied data
		if(src.front == src.cursor)
			cursor = front;
		QNode<T>* prev_temp = front;							
		QNode<T>* dest_temp = front;							//temporary pointers
		QNode<T>* src_temp = src.front->next;					
		while(src_temp != NULL){								//while the source still has data
			dest_temp->next = new QNode<T>(src_temp->data);			//attach a new node containing the copied data
			if(src_temp == src.cursor)								//if the current node is a cursor
				cursor = dest_temp->next;								//update the cursor for the copied list
			src_temp = src_temp->next;								//move to the next node in the source (or NULL)
			dest_temp = dest_temp->next;							//move to the next node in the destination (or NULL)
			dest_temp->prev = prev_temp;							//link the newly created node to the previous one
			prev_temp = prev_temp->next;							//move the previous node helper pointer to the next one
		}
		back = prev_temp;										//set the back pointer to the most recent node copied
	}
	else {													//else if the source is an empy list
		front = NULL;											//set all pointers to null
		back = NULL;
		cursor = NULL;
	}
}


//************************************
//Assignment Opperator
template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& src){
	if(src.front != NULL){									//if the source is not an empty list
		front = new QNode<T>(src.front->data);					//create first node at the front with the copied data
		if(src.front == src.cursor)
			cursor = front;
		QNode<T>* prev_temp = front;							
		QNode<T>* dest_temp = front;							//temporary pointers
		QNode<T>* src_temp = src.front->next;					
		while(src_temp != NULL){								//while the source still has data
			dest_temp->next = new QNode<T>(src_temp->data);			//attach a new node containing the copied data
			if(src_temp == src.cursor)								//if the current node is a cursor
				cursor = dest_temp->next;								//update the cursor for the copied list
			src_temp = src_temp->next;								//move to the next node in the source (or NULL)
			dest_temp = dest_temp->next;							//move to the next node in the destination (or NULL)
			dest_temp->prev = prev_temp;							//link the newly created node to the previous one
			prev_temp = prev_temp->next;							//move the previous node helper pointer to the next one
		}
		back = prev_temp;										//set the back pointer to the most recent node copied
	}
	else {													//else if the source is an empy list
		front = NULL;											//set all pointers to null
		back = NULL;
		cursor = NULL;
	}
}


//************************************
//Queue Destructor
template <class T>
Queue<T>::~Queue(){
	while(front!=NULL){            //while the list is not empty
		QNode<T>* temp = front;       //use temporary pointer to front
		front = front->next;          //move front to the next node (or NULL)
		delete [] temp;               //delete what the temp pointer is pointing to
	}
}


//************************************
//Enqueue
template <class T>
void Queue<T>::Enq(T item){
	if(front != NULL){						//if the list is not empty
		QNode<T>* temp = back;					//temp pointer to the "old back"
		back->next = new QNode<T>(item);		//create the new node containing enqueued data
		back = back->next;						//move the "old back" to the "new back"
		back->prev = temp;						//link the new back to the previous old back (what temp points to)
		cursor = back;							//set the cursor to the newly added node
	}
	else{									//else if the list is empty
		front = new QNode<T>(item);				//create the new node at the front containing the enqueued data
		cursor = front;							//set cursor to front
		back = front;							//set back to front (list has size: 1)
	}
	
}


//************************************
//Dequeue
template <class T>
T Queue<T>::Deq(){
	T retval;						//declare return value
	
	if(front != NULL){				//if the list is not empty
		retval = front->data;			//return value gets the data from the front of the queue
		QNode<T>* temp = front;			//temp pointer to front node of queue
		
		if(front->next)					//if the next node exists (list has size: >1)
			front = front->next;			//set the new front to the next node
		else {							//otherwise,
			front = NULL;					//the list is now empty
			back = NULL;
			cursor = NULL;
		}
		delete temp;					//delete the dequeued node (what temp points to)
		
		if(front)						//if the list is not empty
			front->prev = NULL;				//update the new front's previous pointer to NULL (since there is nothing before the front)
		cursor = front;					//point ther cursor to the new front (NULL if the list is empty)
	}
	return retval;					//return the data that has been dequeued
}


//************************************
//Search
template <class T>
bool Queue<T>::Search(T item){
	QNode<T>* curr = front;			//temp pointer to front of list
	bool found = false;				//data has not yet been found
   
	while(curr != NULL && !found){	//while list is not empty and the data isn't found
	if (curr->data == item){		//if the current node's data is equal to the value being searched for,
    	found = true;               	//then we've found our data in the list and the loop can break
    }
    curr = curr->next;				//move to the next item in the list (or NULL if we've reached the end)
    }
    return found;					//return if we've found the data or not
}


//************************************
//Print List
template <class T>
void Queue<T>::PrintList(){
	QNode<T>* temp = front;					//temp pointer to front of list
	cout << "[ ";							//print opening bracket of entire list
	while (temp != NULL){					//while nodes exist
		if(temp == cursor)						//if the current node is the cursor node
			cout << "[" << temp->data << "] ";		//print the data with brackets around it
		else									//otherwise
			cout << temp->data << " ";				//print the data without brackets
		temp = temp->next;						//move to the next node (or NULL if at the end)
	}
	cout << "]";							//print closing bracket of entire list
}


//************************************
//Print Item
template <class T>
void Queue<T>::PrintItem(){
	if(cursor)
    	cout << "[" << cursor->data << "]";     //print the data at the cursor in brackets
    else
    	cout << "Empty list";
}


//************************************
//Move
template <class T>
bool Queue<T>::Move(char choice){  
    switch(choice){
        case '>':                   //Move Right
            if (cursor == NULL)       	//if the list is emoty
            	cursor = NULL;				//cursor = NULL
            else if(cursor == back)		//if the cursor is at the back
                cursor = front;				//the cursor moves to the front
            else						//otherwise,
                cursor = cursor->next;		//the cursor moves to the right
            break;
        
        case '<':                   //Move Left
            if (cursor == NULL)			//if the list is empty
            	cursor = NULL;				//cursor = NULL
            else if (cursor == front)	//if the cursor is at the front
                cursor = back;				//the cursor moves to the back 
            else						//otherwise
            	cursor = cursor->prev;      //the cursor moves to the left
            break;
        
        case 'B':
        case 'b':                   //Move Begining
            if (cursor == NULL)			//if the list is empty
            	cursor = NULL;				//cursor = NUll
            else						//otherwise
            	cursor = front;				//the cursor moves to the beginning
            break;
        
        case 'E':
        case 'e':                   //Move End
            if (cursor == NULL)			//if the list is empty
                cursor = NULL;				//cursor=NULL
            else						//otherwise
                cursor = back;				//the cursor moves to the back
            break;
        default:
            break;
            
    }
    return cursor;
}



#endif

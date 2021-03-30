/*Poppy La
File name: Simulation.h
Instructor: Dr.Stiber
Date: 02/26/2021
Course: CSS343
Program 3: The PriorityQueue class
   This class is a priority queue implemented as min heap. It takes many events and add them to a Event vector. 
   The events are added into the vector in a min heap order. The smallest event at the front of the queue will be 
   removed first and the queue will re-adjust itself.
*/

#pragma once
#include "Event.h"
#include <vector>

using namespace std;

class PriorityQueue
{
   public:
//--------------------------------------------------------------
//                  CONSTRUCTORS & DESTRUCTOR
//--------------------------------------------------------------
   //default contructor
   PriorityQueue();

   //destructor
   ~PriorityQueue();

//--------------------------------------------------------------
//                         FUNCTIONS
//--------------------------------------------------------------
	//pre-condition: the priority queue valid
	//return: the size of priority queue
   int getSize();

   //takes a Event object in parameter to insert to the priority queue vector
   //pre-condition: Event object passed in parameter valid
   //post-condition: a new Event is added to the priority queue in a min heap order
   //return: true when insertion completed
   bool insert(Event); 

   //return the first Event in queue without deleting it from the priority queue
   //pre-condition: priority queue is not empty
   //return: the first Event in the priority queue
   Event peek();


   //return the first Event in priority queue and delete it
   //pre-condition: priority queue is not empty
   //return: the first Event in the priority queue
   Event pop(); 

   //display all the Events stored in priority queue
	//pre-condition: priority queue is valid
	//post-condition: printout all Event's arrival time.
   void display();

   //check if the priority queue is empty or not
   //pre-condition: priority queue is valid
   //return: true if the priority queue is empty
   bool isEmpty();
   

   protected:
   //takes 2 Event object's addresses of priority queue in parameter and swap them
   //pre-condition: 2 Event objects are valid
   //post-condition: 2 Events objects are swapped together
   //return: true when swapping process completed
   bool swap(Event*, Event*);

   //takes a root Event index in parameter. If the root is not the smallest one, bubble it
   //down until all the Events in min heap order
   //pre-condition: priority queue valid and not in min heap order
   //post-condition: priority queue is adjusted in min heap order
   //return: true when adjustment process is completed
   bool adjustMinHeap(int);

   //take in integer number and find its parent in the min heap
   //pre-condition: the priority queue valid
	//return: the parent of number passed in parameter
   int getParent(int);

   //take in integer number and find its left child in the min heap
   //pre-condition: the priority queue valid
	//return: the left child of number passed in parameter
   int getLeft(int);

   //take in integer number and find its right child in the min heap
   //pre-condition: the priority queue valid
	//return: the right child of number passed in parameter
   int getRight(int);

   private:
//--------------------------------------------------------------
//                          VARIABLES
//--------------------------------------------------------------
   vector<Event> priority_queue_;   //stores all events in min heap order
};
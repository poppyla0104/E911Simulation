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

#include "PriorityQueue.h"

//default constructor
PriorityQueue::PriorityQueue()
{}

//destructor
PriorityQueue::~PriorityQueue()
{}


//pre-condition: the priority queue valid
//return: the size of priority queue
int PriorityQueue::getSize()
{
   return priority_queue_.size();
}


//takes 2 Event object's addresses of priority queue in parameter and swap them
//pre-condition: 2 Event objects are valid
//post-condition: 2 Events objects are swapped together
//return: true when swapping process completed
bool PriorityQueue::swap(Event *x, Event *y)
{
   Event temp = *x;
   *x = *y;
   *y = temp;
   return true;
}


//takes a Event object in parameter to insert to the priority queue vector
//pre-condition: Event object passed in parameter valid
//post-condition: a new Event is added to the priority queue in a min heap order
//return: true when insertion completed
bool PriorityQueue::insert(Event theEvent)
{
   //insert new event at the end of queue
   priority_queue_.push_back(theEvent);
   
   int i = priority_queue_.size() - 1; //new event index

   //bubble the new event up by swapping it with its parent if it's smaller than parent
   while (i != 0 && priority_queue_[getParent(i)] > priority_queue_[i]) {

      swap(&priority_queue_[i], &priority_queue_[getParent(i)]);
      i = getParent(i);    //find its new parent after swap
   }

   return true;
}


//return the first Event in queue without deleting it from the priority queue
//pre-condition: priority queue is not empty
//return: the first Event in the priority queue
Event PriorityQueue::peek()
{
   Event temp;
   //return the first event in queue if queue is not empty
   if (priority_queue_.size() != 0) {

      temp = priority_queue_[0];
   } 

   return temp;
}


//return the first Event in priority queue and delete it
//pre-condition: priority queue is not empty
//return: the first Event in the priority queue
Event PriorityQueue::pop()
{
   Event temp;
   if (priority_queue_.size() != 0) {

      //swap smallest event with last event in queue
      swap(&priority_queue_[0], &priority_queue_[priority_queue_.size() -1]);
      temp = priority_queue_[priority_queue_.size() -1];    //store smallest event to return 
      priority_queue_.pop_back();      //delete smallest event now at the back
      
      //adjust the queue in min heap order
      if (priority_queue_.size() != 0) {
         adjustMinHeap(0);
      }
   }

   return temp;      //return smallest event value
}


//takes a root Event index in parameter. If the root is not the smallest one, bubble it
//down until all the Events in min heap order
//pre-condition: priority queue valid and not in min heap order
//post-condition: priority queue is adjusted in min heap order
//return: true when adjustment process is completed
bool PriorityQueue::adjustMinHeap(int root)
{
   //get left and right children of the root
   int left = getLeft(root); 
   int right = getRight(root);
   int smallest = root;

   //compare root with its children to determine the smallest value among 
   if (left < priority_queue_.size() && priority_queue_[left] < priority_queue_[root]) {
      
      smallest = left;
   }

   if(right < priority_queue_.size() && priority_queue_[right] < priority_queue_[smallest]) {
      
      smallest = right;
   }

   //swap root with the child if the child has has smaller value
   if(smallest != root) {

      swap(&priority_queue_[root], &priority_queue_[smallest]);
      adjustMinHeap(smallest);   //continue adjusting until root has smallest value
   }

   return true;
}


//display all the Events stored in priority queue
//pre-condition: priority queue is valid
//post-condition: printout all Event's arrival time.
void PriorityQueue::display()
{
   for(int i = 0; i < priority_queue_.size(); i++) {

      cout << priority_queue_[i] << " ";
   }

   cout <<  endl;
}


//check if the priority queue is empty or not
//pre-condition: priority queue is valid
//return: true if the priority queue is empty
bool PriorityQueue::isEmpty()
{
   return priority_queue_.size() == 0;
}


//take in integer number and find its parent in the min heap
//pre-condition: the priority queue valid
//return: the parent of number passed in parameter
int PriorityQueue::getParent(int i)
{
   return (i-1)/2;
}


//take in integer number and find its left child in the min heap
//pre-condition: the priority queue valid
//return: the left child of number passed in parameter
int PriorityQueue::getLeft(int i)
{
   return (2*i + 1);
}


//take in integer number and find its right child in the min heap
//pre-condition: the priority queue valid
//return: the right child of number passed in parameter
int PriorityQueue::getRight(int i)
{
   return (2*i + 2);
}


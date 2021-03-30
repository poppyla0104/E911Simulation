/*Poppy La
File name: Simulation.h
Instructor: Dr.Stiber
Date: 02/26/2021
Course: CSS343
Program 3: The Simulation class
   This class is a event-driven simulation. It takes input datas (number of call takers, average number 
   of legitimate calls per hour, average legitimate call service time in seconds and number of bot), 
   use them to generate legitimate calls and bot calls events, then add them to a priority queue to process. 
   The bot calls will be generate with a random arrival-time in the range of (1, 3600) seconds and 
   the fixed 6 second service-time. Legitimate call will be generated with a randomarrival-time and 
   service-time using the input data. Average length of service-time of each legitimate call will be 
   calculated as the result.

*/

#pragma once
#include "PriorityQueue.h"
#include <queue>

class Simulation
{
   public:
//--------------------------------------------------------------
//                  CONSTRUCTORS & DESTRUCTOR
//--------------------------------------------------------------
   //default contructor
   Simulation();

   //destructor
   ~Simulation();


//--------------------------------------------------------------
//                         FUNCTIONS
//--------------------------------------------------------------
   //takes input datas in parameter, use them to generate legitimate calls and bot calls events, 
   //create a priority queue and add all events in, then process each events.
	//pre-condition: input datas have to be valid
	//post-condition: all the events in priority queue are processed and average total service-time 
   //        of each legitimate call is calculated
	//function called: Simulation::generateLegitimateCall(), Simulation::generateBotCall(), 
   //                 Simulation::processQueue(),  Simulation::calculateAverageTotal()
	//return: true if stimulation completed
   bool simulationProcess(int, double, double, int);

   //calculate average service-time of one legitimate call using number of processed legitimate calls and
   //their total service-time.
	//pre-condition: all events are processed, processed legitimate calls and their total service-time are counted
	//post-condition: calculate average service-time of one legitimate call and store in average_total_time variable
   //return: true when calculation completed
   bool calculateAverageTotal();

   //display total service time of all legitimate calls processed, all legitimate calls processed and
   //the average service-time of one legitimate call
	//pre-condition: input datas is valid, average total service-time of each legitimate call is calculated
	//post-condition: printout total service time of all legitimate calls processed, all legitimate calls 
   //processed and the average service-time of one legitimate call
   void display();


   protected:
   //generate legitimate calls and add them to priority queue. Use average number of legitimate calls per hour to determine
   //call's arrival-time and average legitimate call service-time to determine call's service-time.
	//pre-condition: input datas is valid
	//post-condition: generate all the legitimate calss and add them to priority queue.
   //return: true when generation completed and priority queue has all the legitiate call events.
   bool generateLegitimateCall();

   //generate bot calls and add them to priority queue. Label events as bot eventa, use uniform distribution to generate 
   //bot call's arrival-time in range of (1,3600) and with 6 seconds of service-time.
	//pre-condition: input datas is valid
	//post-condition: generate all the bot calss and add them to priority queue. Priority queue then has all the bot call events.
   //return: true when generation completed
   bool generateBotCall();

   //process all the call events in priority queue at their process-time. The function use 2 different other functions 
   //to process call-placed events and service-ended events.
	//pre-condition: input datas valid, all events are generated and added to priority queue
	//post-condition: all events in priority queue are processed
	//function called: Simulation::processCallPlaced(Event), Simulation::processServiceEnd(Event)
	//return: true when the procession completed
   bool processQueue();

   //take a call-placed event in parameter, process the events, store it in waiting list if there are no available
   //call-taker to process the event at its process time. The function take one call-taker to process event, set 
   //departuretime and total-time for the event, label it as not call-placed event, then add it back to priority queue.
	//pre-condition: the call-placed event is valid
	//post-condition: call-placed event is either processed with its departure-time and total service-time determined 
   //                or added to waiting-list
	//return: return true when procession completed
   bool processCallPlaced(Event);

   //take service-ended event in parameter, process the events, free a call-taker and process waiting-list
   //before move on to the next event in priority queue. All legitimate calls and their total service-time 
   //are counted and stored in call_processed and total_time variables.
	//pre-condition: the service-ended event is valid
	//post-condition: service-ended event processed, 1 call-placed event in waiting-list is process if 
   //                there is any, legitimate calls and their total service-time are updated.
	//return: return true when procession completed
   bool processServiceEnd(Event);

   //take 1 call-taker, process the call-placed events in waiting-list, set wait-time, departuretime and total-time for 
   //the event, label it as not call-placed event, then add it back to priority queue.
	//pre-condition: the call-taker available
	//post-condition: 1 call-placed event in waiting-list is processed. event's wait-time, departuretime and total-time are 
   //                set and event is added back to priority queue.
	//return: return true when procession completed
   bool processWaitingList();

   private:
//--------------------------------------------------------------
//                          VARIABLES
//--------------------------------------------------------------
   int current;      //the current time at the time events are processed

   PriorityQueue event_queue;    //priority queue stores all legitimate and bot call events
   queue<Event> waiting_list;    //stores all the events that are waiting for available call-taker
   vector<int> taker_available;  //number of available call-taker
   int n_call_takers;            //number of call-takers
   double call_per_second;       //number of legitimate call per second
   double avg_service;           //average service-time of one legitimate call
   int bot;                      //number of bot, each bot makes 1 bot call

   int call_processed;           //total legitimate call processed
   int total_time;               //total processed legitimate calls's service-times
   int average_total_time;       //average total service-time of each legitimate call
  
};
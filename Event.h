/*Poppy La
File name: Simulation.h
Instructor: Dr.Stiber
Date: 02/26/2021
Course: CSS343
Program 3: The Event class
   This is an Event class that contains all the call event information and data. It determines the call's 
   call type(legitmate or bot), event type (call-placed or service-ended) and set arrival-time, service-time, 
   wait-time, departure-time and total service-time of each phone call.
*/

#pragma once
#include <string>
#include <iostream>

using namespace std;

class Event
{
   public:
//--------------------------------------------------------------
//                  CONSTRUCTORS & DESTRUCTOR
//--------------------------------------------------------------
   //default contructor
   Event();

   //contructure that takes a call type in parameter, determine it the call is bot
   //set service-time for bot call and change bot_call boolean variable to true
   Event(string);

   //destructor
   ~Event();

   //takes the arrival-time passed in parameter and set arrival-time for call-placed Event
   //the process_time of call-placed Event will be the arrival-time
   //post-condition: set arrival_time and process_time
   //return: true when setting completed
   bool setArrival(int);

   //takes the service-time passed in parameter and set service-time for call-placed Event
   //post-condition: set service_time for Event
   //return: true when setting completed
   bool setService(int);

   //take a current time in parameter to calculate wait-time for service-ended Event 
   //pre-condition: current time and arrival_time valid
   //post-condition: wait_time is set
   //return: true when setting completed
   bool setWait(int);

   //calculate departure-time for service-ended Event using arrival_time, wait_time, and service_time
   //and calculate total service time using departure_time and arrival_time
   //change Event into not-call-placed event, the process_time will be the departure-time
   //pre-condition: arrival_time, wait_time, and service_time valid
   //post-condition: Event turn in to service-ended, departure_time, process_time and total_time are set.
   //return: true when setting completed
   bool setDeparture();

   //pre-condition: the Event arrival_time valid
   //return: arrival_time value
   int getArrival() const;

   //pre-condition: the Event service_time valid
   //return: service_time value
   int getService() const;

   //pre-condition: the Event wait_time valid
   //return: wait_time value
   int getWait() const;

   //pre-condition: the Event departure_time valid
   //return: departure_time value
   int getDeparture() const;

   //pre-condition: the Event process_time valid
   //return: process_time value
   int getProcessTime() const;

   //pre-condition: the Event total_time valid
   //return: total_time value (total service time)
   int getTotal() const;

   //check if the call type of Event is a bot call Event
   //return: true if it's bot call
   bool isBot() const;

   //check if the Event type is a call_placed Event
   //return: true if it's bot call
   bool isCallPlaced() const;

//--------------------------------------------------------------
//                       OPERATORS OVERLOAD
//--------------------------------------------------------------
   //pre-condition: Event object valid
   //post-condition: printout Event process_time
   //function called: Event::getProcessTime()
   //return: os
   friend ostream& operator<<(ostream& os, const Event &event);

   //class operator that takes other Event object to compare
   //pre-condition: event and the comparison event objects valid
   //post-condition: compare if this event's process_time > other's
   //return: true if this event's process_time > other's
   bool operator>(const Event& other) const;

   //class operator that takes other Event object to compare
   //pre-condition: event and the comparison event objects valid
   //post-condition: compare if this event's process_time < other's
   //return: true if this event's process_time < other's
   bool operator<(const Event& other) const;

   private:
//--------------------------------------------------------------
//                        VARIABLES
//--------------------------------------------------------------
   bool bot_call;          //determine if call is bot call event
   bool call_placed;       //determine if event is a call-placed event
   int arrival_time;       //event's arrival time
   int service_time;       //event's service time
   int wait_time;          //event's wait time
   int departure_time;     //event's departure time
   int total_time;         //event's total service time (service + wait time)
   int process_time;       //time that event will be processed in queue

};
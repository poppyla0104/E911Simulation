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

#include "Event.h"
#include <iostream>


//default contructor
Event::Event()
{
   //initialize all variables
   call_placed = true;
   bot_call = false;
   arrival_time = 0;
   service_time = 0;
   wait_time = 0;
   departure_time = 0;
   process_time = 0;
   total_time = 0;
}


//contructure that takes a call type in parameter, determine it the call is bot
//set service-time for bot call and change bot_call boolean variable to true
Event::Event(string callType)
{
   //initialize all variables
   call_placed = true;
   bot_call = false;
   arrival_time = 0;
   service_time = 0;
   wait_time = 0;
   departure_time = 0;
   process_time = 0;
   total_time = 0;

   //determine bot call
   if (callType == "bot") {
      
      bot_call = true;  
      service_time = 6;    //set all bot call's service_time to 6 seconds
   }
}


//destructor
Event::~Event()
{}

//takes the arrival-time passed in parameter and set arrival-time for call-placed Event
//the process_time of call-placed Event will be the arrival-time
//post-condition: set arrival_time and process_time
//return: true when setting completed
bool Event::setArrival(int arrival)
{
   arrival_time = arrival;
   process_time = arrival_time;     //process_time of call-placed Event
   return true;
}


//takes the service-time passed in parameter and set service-time for call-placed Event
//post-condition: set service_time for Event
//return: true when setting completed
bool Event::setService(int service)
{
   service_time = service;
   return true;
}


//take a current time in parameter to calculate wait-time for service-ended Event 
//pre-condition: current time and arrival_time valid
//post-condition: wait_time is set
//return: true when setting completed
bool Event::setWait(int current)
{
   wait_time = current - arrival_time;
   return true;
}


//calculate departure-time and total service time
//pre-condition: arrival_time, wait_time, and service_time valid
//post-condition: Event turn in to service-ended, departure_time, process_time and total_time are set.
//return: true when setting completed
bool Event::setDeparture()
{
   call_placed = false;    //change to service-ended event
   departure_time = arrival_time + wait_time + service_time;
   process_time = departure_time;   //process time in priority queue of service-ended event
   total_time = departure_time - arrival_time;     //total service time of the event
   return true;
}


//pre-condition: the Event arrival_time valid
//return: arrival_time value
int Event::getArrival() const
{
   return arrival_time;
}


//pre-condition: the Event service_time valid
//return: service_time value
int Event::getService() const
{
   return service_time;
}


//pre-condition: the Event wait_time valid
//return: wait_time value
int Event::getWait() const
{
   return wait_time;
}


//pre-condition: the Event departure_time valid
//return: departure_time value
int Event::getDeparture() const
{
   return departure_time;
}


//pre-condition: the Event process_time valid
//return: process_time value
int Event::getProcessTime() const
{
   return process_time;
}


//pre-condition: the Event total_time valid
//return: total_time value (total service time)
int Event::getTotal() const
{
   return total_time;
}


//check if the call type of Event is a bot call Event
//return: true if it's bot call
bool Event::isBot() const
{
   return bot_call;
}


//check if the Event type is a call_placed Event
//return: true if it's bot call
bool Event::isCallPlaced() const
{
   return call_placed;
}


//class operator that takes other Event object to compare
//pre-condition: event and the comparison event objects valid
//post-condition: compare if this event's process_time > other's
//return: true if this event's process_time > other's
bool Event::operator>(const Event& other) const
{
   return process_time > other.process_time;
}


//class operator that takes other Event object to compare
//pre-condition: event and the comparison event objects valid
//post-condition: compare if this event's process_time < other's
//return: true if this event's process_time < other's
bool Event::operator<(const Event& other) const
{
   return process_time < other.process_time;
}


//pre-condition: Event object valid
//post-condition: printout Event process_time
//function called: Event::getProcessTime()
//return: os
ostream& operator<<(ostream& os, const Event &event)
{
   os << event.getProcessTime();
   return os;
} 
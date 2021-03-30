/*Poppy La
File name: Simulation.cpp
Instructor: Dr.Stiber
Date: 02/26/2021
Course: CSS343
Program 3: The Simulation class
   This class is a event-driven simulation. It takes input datas (number of call takers, average number 
   of legitimate calls per hour, average legitimate call service time in seconds and number of bot), 
   use them to generate legitimate calls and bot calls, then add them to a priority queue to process. 
   The bot calls will be generate with a random arrival-time in the range of (1, 3600) seconds and 
   the fixed 6 second service-time. Legitimate call will be generated with a randomarrival-time and 
   service-time using the input data. Average length of service-time of each legitimate call will be 
   calculated as the result.

*/

#include "Simulation.h"
#include <cmath>
#include <random>


//default contructor
//initialize the variables
Simulation::Simulation()
{
   current = 0;
   total_time = 0;
   call_processed = 0;
   average_total_time = 0;
}


//destructor
Simulation::~Simulation()
{}


//takes input datas in parameter, use them to generate legitimate calls and bot calls events, 
//create a priority queue and add all events in, then process each events.
//pre-condition: input datas have to be valid
//post-condition: all the events in priority queue are processed and average total service-time 
//        of each legitimate call is calculated
//function called: Simulation::generateLegitimateCall(), Simulation::generateBotCall(), 
//                 Simulation::processQueue(),  Simulation::calculateAverageTotal()
//return: true if stimulation completed
bool Simulation::simulationProcess(int taker, double call, double ts, int b)
{
   //set class's variable from input
   n_call_takers = taker;
   call_per_second = call/3600.0;
   avg_service = 1/ts;
   bot = b;
   taker_available.resize(taker);

   //generate legitimate calls and bot calls, then add them all in priority queue
   generateLegitimateCall();
   generateBotCall();

   //process priority queue with all call events
   processQueue();

   //calculate the average total service-time of each legitimate call
   calculateAverageTotal();

   return true;
}


//generate legitimate calls and add them to priority queue. Use average number of legitimate calls per hour to determine
//call's arrival-time and average legitimate call service-time to determine call's service-time.
//pre-condition: input datas is valid
//post-condition: generate all the legitimate calss and add them to priority queue.
//return: true when generation completed and priority queue has all the legitiate call events.
bool Simulation::generateLegitimateCall()
{
   //create generator to determine arrival-time and service-time
   default_random_engine arrivalGenerator;
   exponential_distribution<double> expDistC(call_per_second);
   
   default_random_engine serviceGenerator;
   exponential_distribution<double> expDistS(avg_service);

   //1st event in queue at t = 0
   Event legit;
   legit.setArrival(0);
   legit.setService(int(ceil(expDistS(serviceGenerator)))); //generate service-time

   int interval = 0;
   int previous = 0;    //previous arrival-time

   //insert previous event to queue and create next event
   //previous event is inserted if its arrival-time is before 3600 second
   while(previous < 3600) {

      event_queue.insert(legit);  //add previous event   
      interval = int(ceil(expDistC(arrivalGenerator)));
      legit.setArrival(previous + interval);    //set new event's arrival-time
      int temp_service = int(ceil(expDistS(serviceGenerator)));      //generate new event's service-time

      //re-generate service-time if it's longer than 3600 seconds
      while (temp_service >= 3600) {
         temp_service = int(ceil(expDistS(serviceGenerator)));
      }

      legit.setService(temp_service);     //set new event's service-time
      previous = legit.getArrival();      //previous arrival-time is new event's arrival-time
   }
   return true;
}


//generate bot calls and add them to priority queue. Label events as bot eventa, use uniform distribution to generate 
//bot call's arrival-time in range of (1,3600) and with 6 seconds of service-time.
//pre-condition: input datas is valid
//post-condition: generate all the bot calss and add them to priority queue. Priority queue then has all the bot call events.
//return: true when generation completed
bool Simulation::generateBotCall()
{
   //create generator to determin bot arrival-time
   default_random_engine botGenerator;
   uniform_int_distribution<int> uniform(1,3600);

   int number = 0;
   //number of bot call = number of bot 
   while(number != bot){

      //create bot call event and add to priority queue
      Event bot("bot");  
      bot.setArrival(uniform(botGenerator));
      event_queue.insert(bot);
      number++;
   }
   return true;
}


//process all the call events in priority queue at their process-time. The function use 2 different other functions 
//to process call-placed events and service-ended events.
//pre-condition: input datas valid, all events are generated and added to priority queue
//post-condition: all events in priority queue are processed
//function called: Simulation::processCallPlaced(Event), Simulation::processServiceEnd(Event)
//return: true when the procession completed
bool Simulation::processQueue()
{
   //process first event in queue at it's process-time
   while (event_queue.getSize() != 0 && event_queue.peek().getProcessTime() == current) {

      Event event = event_queue.pop();    //take front Event   
      
      //process call-placed event
      if(event.isCallPlaced()) {
         processCallPlaced(event);
   
      //process service-ended event
      } else if (!event.isCallPlaced()) {
         processServiceEnd(event); 
      }

      //stop at 3600 seconds
      // if(current >= 3600)
      // {
      //    break;
      // }
   }
   return true;
}


//take a call-placed event in parameter, process the events, store it in waiting list if there are no available
//call-taker to process the event at its process time. The function take one call-taker to process event, set 
//departuretime and total-time for the event, label it as not call-placed event, then add it back to priority queue.
//pre-condition: the call-placed event is valid
//post-condition: call-placed event is either processed with its departure-time and total service-time determined 
//                or added to waiting-list
//return: return true when procession completed
bool Simulation::processCallPlaced(Event event)
{  
   //add to waiting-list if call-taker are not available
   if(taker_available.size() == 0){ 
      waiting_list.push(event);
   
   //set departure data for event and add it back to queue as service-ended event
   } else {
      taker_available.pop_back();   //take a call taker
      event.setDeparture();
      event_queue.insert(event);
   }

   //update current time
   current = event_queue.peek().getProcessTime();
   return true;
}


//take service-ended event in parameter, process the events, free a call-taker and process waiting-list
//before move on to the next event in priority queue. All legitimate calls and their total service-time 
//are counted and stored in call_processed and total_time variables.
//pre-condition: the service-ended event is valid
//post-condition: service-ended event processed, 1 call-placed event in waiting-list is process if 
//                there is any, legitimate calls and their total service-time are updated.
//return: return true when procession completed
bool Simulation::processServiceEnd(Event event)
{
   //legitimate call
   if(!event.isBot()) {
      total_time += event.getTotal();     //update total service time  
      call_processed++;            //count legitimate call
   }

   taker_available.push_back(0);    //free a call taker

   //process waiting list with new available call taker before move to next event in queue
   if (waiting_list.size() != 0) {

      processWaitingList();
   
   } else if (event_queue.getSize() != 0) {
      current = event_queue.peek().getProcessTime();  //set current time to next event's process time
   }

   return true;
}


//take 1 call-taker, process the call-placed events in waiting-list, set wait-time, departuretime and total-time for 
//the event, label it as not call-placed event, then add it back to priority queue.
//pre-condition: the call-taker available
//post-condition: 1 call-placed event in waiting-list is processed. event's wait-time, departuretime and total-time are 
//                set and event is added back to priority queue.
//return: return true when procession completed
bool Simulation::processWaitingList()
{
   //1st event and delete it from waiting list
   Event event = waiting_list.front();   
   waiting_list.pop();
   taker_available.pop_back();   //take a call taker

   //set wait time and departure data, then add it back to queue as servicec-ended event
   event.setWait(current);
   event.setDeparture();
   event_queue.insert(event);

   current = event_queue.peek().getProcessTime();  //update current time

   return true;
}


//calculate average service-time of one legitimate call using number of processed legitimate calls and
//their total service-time.
//pre-condition: all events are processed, processed legitimate calls and their total service-time are counted
//post-condition: calculate average service-time of one legitimate call and store in average_total_time variable
//return: true when calculation completed
bool Simulation::calculateAverageTotal()
{
   return average_total_time = total_time / call_processed;

}


//display total service time of all legitimate calls processed, all legitimate calls processed and
//the average service-time of one legitimate call
//pre-condition: input datas is valid, average total service-time of each legitimate call is calculated
//post-condition: printout total service time of all legitimate calls processed, all legitimate calls 
//processed and the average service-time of one legitimate call
void Simulation::display()
{
   cout << "Total service time: " << total_time << " seconds" << endl;
   cout << "Legitimate calls processed: " << call_processed << " calls" << endl;
   cout << "Average service time per call: " << average_total_time << " seconds" << endl << endl;
}

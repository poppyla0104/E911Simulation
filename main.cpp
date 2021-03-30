/*Poppy La
File name: main.cpp
Instructor: Dr.Stiber
Date: 02/26/2021
Course: CSS343
Program 3: Simulating E911 DDoS Attacks
   The purpose of this program is to calculate the average total service time for each legitimate calls of 
   the E911 system in the presence of a distributed denial of service attack (bot) for a duration of one hour 
   using priority queue implemented as a min heap. 2 types of call types (legitimate calls and bot calls) will 
   be generated and added into a priority queue. Multiple test cases will be run with a different number of 
   bots {0, 100, 1000, 2000, 3000, 6000, 10000} to determine the different average total service times for 
   legitimate calls. The program will only calcute the service time of legitimate calls and total number of legitimate
   call for the result. The program will take number of call takers, average number of legitimate calls per hour, average 
   legitimate call service time in seconds and number of bot from the command line argument.The output will be the 
   total service time of all legitimate calls processed, all legitimate calls processed and the average service-time of 
   one legitimate call (an integer number). A Simulation class will be used to process the input data and process them with
   PriorityQueue class and Event class.
*/

#include "Simulation.h"

using namespace std;

int main(int argc, char* argv[])
{
   //notice the missing input data
   if(argv[1] == nullptr) {
      cout << "Please input 4 data information! " << endl;
      abort();
   
   //ignore all the other input after corpus file in command line argument, then process
   } else if (argc > 5) {
      cout << "Data after the file name will be ignored. " << endl << endl;
   }

   //stores input in compatible data variables
   int call_taker = stoi(argv[1]);
   double avg_call_per_hour = stod(argv[2]);
   double avg_service_time = stod(argv[3]);
   int bot = stoi(argv[4]);


   //Create Simulation object and process input data
   Simulation mySimulation;
   mySimulation.simulationProcess(call_taker, avg_call_per_hour, avg_service_time, bot);

   mySimulation.display();    //print out output
}
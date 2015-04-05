#include "Eventlist.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>

const std::string LOGFILE = "log.txt" ;

char buffer[1000];

Eventlist::Eventlist(void){
}


Eventlist::~Eventlist(void){
}

void Eventlist::clearEventlist(){ 
	_allEvent.clear();
}

void Eventlist::addEvent(Event newEvent){
	_allEvent.push_back(newEvent); 
	std::ofstream destination;
	destination.open(LOGFILE,std::ofstream::app);
	time_t rawtime;
	struct tm  timeinfo;
	rawtime = time (0);
	localtime_s(&timeinfo, &rawtime);
	asctime_s(buffer,&timeinfo) ;
	std::cout << timeinfo.tm_wday << std::endl;
	destination	<< buffer <<newEvent.readEvent() << "Add Event successfully"<< std::endl;
	destination.close();

}

//Delete one Event from the list by searching from the front of the list.
void Eventlist::deleteEvent(int index){
	std::list<Event>::iterator deleteposition;
	deleteposition = _allEvent.begin();
	advance (deleteposition, index-1);
	_allEvent.erase(deleteposition);
}

//Find the Event at the index position and return the Event.
Event Eventlist::getEvent(int index){	
	std::list<Event>::iterator eventPosition;
	eventPosition = _allEvent.begin();
	advance (eventPosition, index-1);
	return *eventPosition;
}

//Replaced the index position Event with new event.
void Eventlist::updateEvent (int index, Event newEvent){
	std::list<Event>::iterator eventPosition;
	eventPosition = _allEvent.begin();
	advance (eventPosition, index-1);
	*eventPosition = newEvent;
}

std::list<Event> Eventlist:: returnAllEvent(){
	return _allEvent;
}

int Eventlist::getTotalNumberOfEvents (void){	
	return _allEvent.size();
}

//Sort the Event in Eventlist according to smallest month, day and time.
void Eventlist::sortEvent(void){  
	_allEvent.sort([](const Event & a, const Event & b) { return a._dueRanking< b._dueRanking; });
}

//Make a copy of list, for undo delete Eventlist
void Eventlist::copyFromNewList(std::list<Event> newList){
	_allEvent.assign(newList.begin(), newList.end());
}
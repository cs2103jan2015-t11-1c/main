#include "Eventlist.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>

const std::string LOGFILE = "log.txt" ;

char buffer[1000];

Eventlist::Eventlist(void)
{
}


Eventlist::~Eventlist(void)
{
}

void Eventlist::clearEventlist()
{ delete this;
}

void Eventlist::addEvent(Event newEvent)
{	_allEvent.push_back(newEvent); 
	std::ofstream destination;
	destination.open(LOGFILE,std::ofstream::app);
	time_t rawtime;
	struct tm  timeinfo;
	rawtime = time (0);
	localtime_s(&timeinfo, &rawtime);
	asctime_s(buffer,&timeinfo) ;
	destination	<< buffer <<newEvent.readEvent() << "added"<< std::endl;
	destination.close();

}

void Eventlist::deleteEvent(int index)
{	std::list<Event>::iterator deleteposition;
	deleteposition = _allEvent.begin();
	advance (deleteposition, index-1);
	_allEvent.erase(deleteposition);
}

Event Eventlist::getEvent(int index)
{	std::list<Event>::iterator eventPosition;
	eventPosition = _allEvent.begin();
	advance (eventPosition, index-1);
	std::cout << "eventlist: " <<std::endl;
	return *eventPosition;
}

void Eventlist::updateEvent (int index, Event newEvent){
	std::list<Event>::iterator eventPosition;
	eventPosition = _allEvent.begin();
	advance (eventPosition, index-1);
	*eventPosition = newEvent;
}

std::list<Event> Eventlist:: returnAllEvent()
{ return _allEvent;
}

int Eventlist::getTotalNumberOfEvents (void)
{	return _allEvent.size();
}

void Eventlist::sortEvent(void)
{   _allEvent.sort([](const Event & a, const Event & b) { return a._dueRanking < b._dueRanking; });
}


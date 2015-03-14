#include "Eventlist.h"



Eventlist::Eventlist(void)
{
}


Eventlist::~Eventlist(void)
{
}


void Eventlist::addEvent(Event newEvent)
{	_allEvent.push_back(newEvent); 
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
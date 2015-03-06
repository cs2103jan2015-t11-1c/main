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
{	_allEvent.erase(_allEvent.begin()+index-1);
}


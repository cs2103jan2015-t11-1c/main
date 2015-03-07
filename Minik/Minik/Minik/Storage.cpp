#include "Storage.h"


Storage::Storage(void)
{
}

Storage::Storage(string newTitle, string newDate, string newTime)
{	_currentEvent = Event(newTitle, newDate, newTime);
}

Storage::~Storage(void)
{
}
void Storage::addEvent(string newTitle, string newDate, string newTime)
{	_currentEvent = Event(newTitle, newDate, newTime);
	_activeEvent.addEvent(_currentEvent); 
}

void Storage::deleteEvent(int index)
{	_activeEvent.deleteEvent(index);
}

Eventlist Storage::displayEvent(void) 
{	return _activeEvent;
}

void Storage::updateEvent (int index, Event newEvent)
{	_activeEvent.getEvent(index) = newEvent;
}

Event Storage::getEvent(int index)
{	return _activeEvent.getEvent(index);
}


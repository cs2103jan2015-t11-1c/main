#include "Storage.h"


Storage::Storage(void)
{
}

Storage::Storage(Event newEvent)
{	_currentEvent = newEvent;
}

Storage::~Storage(void)
{
}

void Storage::addEvent(Event newEvent)
{	_currentEvent = newEvent;
	_activeEvent.addEvent(_currentEvent); 
}

void Storage::markEventAsDone (int index)
{   _currentEvent = _activeEvent.getEvent(index);
	_activeEvent.deleteEvent(index);
	_doneEvent.addEvent(_currentEvent);
}


void Storage::deleteEvent(int index)
{	_currentEvent = _activeEvent.getEvent(index);
	_activeEvent.deleteEvent(index);
	_deletedEvent.addEvent(_currentEvent);
}

Eventlist Storage::displayEvent(void) 
{	return _activeEvent;
}

Eventlist Storage::displayDoneEvent (void)
{	return _doneEvent;
}

void Storage::updateEvent (int index, Event newEvent)
{	_activeEvent.updateEvent(index,newEvent);
}

Event Storage::getEvent(int index)
{	return _activeEvent.getEvent(index);
}

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

void Storage::clearActiveEvent()
{	_deletedEvent = _activeEvent;
	_activeEvent.clearEventlist();
}

void Storage::clearDoneEvent()
{	_deletedEvent = _doneEvent;
	_doneEvent.clearEventlist();
}

void Storage::unDoClearActiveEvent()
{	_activeEvent = _deletedEvent;
}

void Storage::unDoClearDoneEvent()
{	_doneEvent = _deletedEvent;
}

void Storage::addEvent(Event newEvent)
{	_currentEvent = newEvent;
	_activeEvent.addEvent(_currentEvent); 
}

void Storage::unDoAddEvent ()
{	int index = _activeEvent.getTotalNumberOfEvents();
	_activeEvent.deleteEvent(index);
}


void Storage::markEventAsDone (std::list<int> allIndex)
{   int i;
	_numberForUndo=allIndex.size();
	while(!allIndex.empty()){
	i=allIndex.back();
	_currentEvent = _activeEvent.getEvent(i);
	_activeEvent.deleteEvent(i);
	_doneEvent.addEvent(_currentEvent);
	allIndex.pop_back();
	}
}

void Storage::unDomarkEventAsDone()
{	while(_numberForUndo>0) {
	int lastEventNumber = _doneEvent.getTotalNumberOfEvents();
	Event unDoEvent = _doneEvent.getEvent(lastEventNumber);
	_doneEvent.deleteEvent(lastEventNumber);
	_activeEvent.addEvent(unDoEvent);
	_numberForUndo--;
	}
}



void Storage::deleteEvent(std::list<int> allIndex)
{	int i;
	_numberForUndo=allIndex.size();
	while(!allIndex.empty()){
	i=allIndex.back();
	_currentEvent = _activeEvent.getEvent(i);
	_activeEvent.deleteEvent(i);
	_deletedEvent.addEvent(_currentEvent);
	allIndex.pop_back();
	}
}
void Storage::unDoDeleteEvent ()
{	while(_numberForUndo>0){
	int lastEventNumber = _deletedEvent.getTotalNumberOfEvents();
	Event unDoEvent = _deletedEvent.getEvent(lastEventNumber);
	_deletedEvent.deleteEvent(lastEventNumber);
	_activeEvent.addEvent(unDoEvent);
	_numberForUndo--;
	}
}


Eventlist Storage::displayEvent(void) 
{	return _activeEvent;
}

Eventlist Storage::displayDoneEvent (void)
{	return _doneEvent;
}

void Storage::updateEvent (int index, Event newEvent)
{	_currentEvent = _activeEvent.getEvent(index);
	_numberForUndo = index;
	_activeEvent.updateEvent(index,newEvent);
}

void Storage::unDoUpdateEvent ()
{   _activeEvent.updateEvent(_numberForUndo,_currentEvent);
}

Event Storage::getEvent(int index)
{	return _activeEvent.getEvent(index);
}

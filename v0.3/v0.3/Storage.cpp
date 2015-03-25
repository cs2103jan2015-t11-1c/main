#include "Storage.h"


Storage::Storage(void)
{
}

Storage::~Storage(void)
{
}

bool Storage::unDopreviousActions(std::string unDoCommand)
{	
	if (_possibleToUnDo=false)
		return false;
	else {
		COMMAND_TYPE command = findCommandType(unDoCommand);
		switch (command) {
	case ADD:
		unDoAddEvent();
		return true;
	case DONE:
		unDomarkEventAsDone;
		return true;
	case DELETE:
		unDoDeleteEvent;
		return true;
	case UPDATE:
		unDoUpdateEvent;
		return true;
	case CLEARACTIVE:
		unDoClearActiveEvent;
		return true;
	case CLEARDONE:
		unDoClearDoneEvent;
		return true;
	case INVALID:
		return false;
		}
	}

}

Storage::COMMAND_TYPE Storage::findCommandType(std::string currentCommand)
{		if (currentCommand == "add"){
			return ADD;
		}
		else if (currentCommand == "update"){
			return UPDATE;
		}
		else if (currentCommand == "delete"){
			return DELETE;
		} 
		else if (currentCommand == "done"){
			return DONE;
		}
		else if (currentCommand == "cleardone"){
			return CLEARACTIVE;
		}
		else if (currentCommand == "clearactive"){
			return CLEARACTIVE;
		}
		else return INVALID;
}

void Storage::clearActiveEvent()
{	_deletedEvent = _activeEvent;
	_activeEvent.clearEventlist();
	_possibleToUnDo = true;
}

void Storage::clearDoneEvent()
{	_deletedEvent = _doneEvent;
	_doneEvent.clearEventlist();
	_possibleToUnDo = true;
}

void Storage::unDoClearActiveEvent()
{	_activeEvent = _deletedEvent;
	_possibleToUnDo = false;
}

void Storage::unDoClearDoneEvent()
{	_doneEvent = _deletedEvent;
	_possibleToUnDo = false;
}

void Storage::addEvent(Event newEvent)
{	_currentEvent = newEvent;
	_activeEvent.addEvent(_currentEvent); 
	_possibleToUnDo = true;
}

void Storage::unDoAddEvent ()
{	int index = _activeEvent.getTotalNumberOfEvents();
	_activeEvent.deleteEvent(index);
	_possibleToUnDo = false;
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
	_possibleToUnDo = true;
}

void Storage::unDomarkEventAsDone()
{	while(_numberForUndo>0) {
	int lastEventNumber = _doneEvent.getTotalNumberOfEvents();
	Event unDoEvent = _doneEvent.getEvent(lastEventNumber);
	_doneEvent.deleteEvent(lastEventNumber);
	_activeEvent.addEvent(unDoEvent);
	_numberForUndo--;
	}
	_possibleToUnDo = false;
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
	_possibleToUnDo = true;
}
void Storage::unDoDeleteEvent ()
{	while(_numberForUndo>0){
	int lastEventNumber = _deletedEvent.getTotalNumberOfEvents();
	Event unDoEvent = _deletedEvent.getEvent(lastEventNumber);
	_deletedEvent.deleteEvent(lastEventNumber);
	_activeEvent.addEvent(unDoEvent);
	_numberForUndo--;
	}
	_possibleToUnDo = false;
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
	_possibleToUnDo = true;
}

void Storage::unDoUpdateEvent ()
{   _activeEvent.updateEvent(_numberForUndo,_currentEvent);
	_possibleToUnDo = false;
}

Event Storage::getEvent(int index)
{	return _activeEvent.getEvent(index);
}

void Storage::sortActiveEventlist()
{	_activeEvent.sortEvent();
}

void Storage::sortDoneEventlist()
{	_doneEvent.sortEvent();
}

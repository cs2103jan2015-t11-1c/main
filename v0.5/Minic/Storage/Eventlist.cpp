//@author A0116455H
//This class is used to store multiple Events.

#include "Eventlist.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>

const int GO_TO_PREVIOUS = -1;
const std::string ERROR_INDEX = "Error: index not valid.\n";

Eventlist::Eventlist(void) {
}


Eventlist::~Eventlist(void) { 
}

void Eventlist::clearEventlist() { 
	_allEvent.clear();
}

void Eventlist::addEvent(Event newEvent) {
	_allEvent.push_back(newEvent); 
}

//Delete one Event from the list by searching from the front of the list.
void Eventlist::deleteEvent(unsigned int index) {
	if (index < 1 || index > _allEvent.size()) {
		throw std::string(ERROR_INDEX);
	}
	std::list<Event>::iterator deleteposition = _allEvent.begin();
	advance(deleteposition, index + GO_TO_PREVIOUS);
	_allEvent.erase(deleteposition);
}

//Find the Event at the index position and return the Event.
Event Eventlist::getEvent(unsigned int index) {	
	if (index < 1 || index > _allEvent.size()) {
		throw std::string(ERROR_INDEX);
	}
	std::list<Event>::iterator eventPosition = _allEvent.begin();
	advance(eventPosition, index + GO_TO_PREVIOUS);
	return *eventPosition;
}

//Replaced the index position Event with new event.
void Eventlist::updateEvent (unsigned int index, Event newEvent) {
	if (index < 1 || index > _allEvent.size()) {
		throw std::string(ERROR_INDEX);
	}
	std::list<Event>::iterator eventPosition = _allEvent.begin();
	advance(eventPosition, index + GO_TO_PREVIOUS);
	*eventPosition = newEvent;
}

std::list<Event> Eventlist:: returnAllEvent() {
	return _allEvent;
}

int Eventlist::getTotalNumberOfEvents (void) {	
	return _allEvent.size();
}

//Sort the Event in Eventlist according to smallest month, day and time.
//Event with no due time will be put to the end.
void Eventlist::sortEvent(void) {  
	_allEvent.sort([](const Event & a, const Event & b) { //given two event.
	return a._dueRanking < b._dueRanking; });			  //compare their ranking.
}

//Make a copy of list, for undo delete Eventlist
void Eventlist::copyFromNewList(std::list<Event> newList) {
	_allEvent.assign(newList.begin(), newList.end());
}
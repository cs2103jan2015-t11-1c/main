//@author A0116455H
//This is a class for storing multiple Event class.
//When a particular event is needed, Eventlist class will find the
//Event and perform respective functions.

#pragma once
#include "Event.h"
#include <vector>
#include <list>


class Eventlist {
private:
	std::list <Event> _allEvent;
public:
	Eventlist(void);
	~Eventlist(void);
	void clearEventlist();
	void addEvent (Event newEvent);
	void deleteEvent (unsigned int index);
	void copyFromNewList( std::list<Event> newList);
	void updateEvent (unsigned int index, Event newEvent);
	void sortEvent(void);
	int getTotalNumberOfEvents (void);
	std::list<Event> returnAllEvent();
	bool compareDueRanking (const Event& firstEvent,const Event& secondEvent);
	Event getEvent(unsigned int index);
};


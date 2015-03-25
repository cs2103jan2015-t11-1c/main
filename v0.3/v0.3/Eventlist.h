#pragma once
#include "Event.h"
#include <vector>
#include <list>


class Eventlist
{
private:
	std::list <Event> _allEvent;
public:
	Eventlist(void);
	~Eventlist(void);
	void clearEventlist();
	void addEvent (Event newEvent);
	void deleteEvent (int index);
	int getTotalNumberOfEvents (void);
	Event getEvent(int index);
	std::list<Event> returnAllEvent();
	void updateEvent (int index, Event newEvent);
	void sortEvent(void);
	bool compareDueRanking (const Event& firstEvent, const Event& secondEvent);
};


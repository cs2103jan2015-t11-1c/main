#pragma once
#include "Event.h"
#include <vector>
#include <list>

class Eventlist
{
private:
	list <Event> _allEvent;
public:
	Eventlist(void);
	~Eventlist(void);
	void addEvent (Event newEvent);
	void deleteEvent (int index);
	Event getEvent(int index);
};


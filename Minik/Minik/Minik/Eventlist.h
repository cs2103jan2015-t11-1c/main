#pragma once
#include "Event.h"
#include <vector>

class Eventlist
{
private:
	vector <Event> _allEvent;
public:
	Eventlist(void);
	~Eventlist(void);
	void addEvent (Event newEvent);
	void deleteEvent (int index);
	
};


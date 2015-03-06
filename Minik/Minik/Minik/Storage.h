#pragma once
#include "Eventlist.h"

class Storage
{
private:
	Eventlist _eventInStorage;
public:
	Storage(void);
	~Storage(void);
	void addEvent (Event newEvent);
	void deleteEvent (int index);
};


#pragma once
#include "Eventlist.h"

class Storage
{
private:
	Event _currentEvent;
	Eventlist _activeEvent;
	Eventlist _doneEvent;
	Eventlist _deletedEvent;
public:
	Storage(void);
	~Storage(void);

	Storage(string newTitle, string newDate, string newTime);
	void addEvent (string newTitle, string newDate, string newTime);
	void deleteEvent (int index);
	void updateEvent (int index, Event newEvent);
	Eventlist displayEvent (void);
	Event getEvent(int index);

};


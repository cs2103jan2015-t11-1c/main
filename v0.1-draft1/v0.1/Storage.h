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

	Storage(Event newEvent);
	void addEvent (Event newEvent);
	void deleteEvent (int index);
	void updateEvent (int index, Event newEvent);
	void markEventAsDone (int index);
	Eventlist displayEvent (void);
	Eventlist displayDoneEvent (void);
	Event getEvent(int index);

};


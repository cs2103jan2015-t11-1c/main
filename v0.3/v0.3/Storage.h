#pragma once
#include "Eventlist.h"

class Storage
{
private:
	int _numberForUndo;
	Event _currentEvent;
	Eventlist _activeEvent;
	Eventlist _doneEvent;
	Eventlist _deletedEvent;
	bool _possibleToUnDo;
	enum COMMAND_TYPE { ADD,DELETE,UPDATE,DONE,CLEARDONE,CLEARACTIVE,INVALID};
	COMMAND_TYPE findCommandType(std::string currentCommand);
public:
	Storage(void);
	~Storage(void);
	void addEvent (Event newEvent);
	void unDoAddEvent ();
	void deleteEvent (std::list<int> allIndex);
	void unDoDeleteEvent ();
	void updateEvent (int index, Event newEvent);
	void unDoUpdateEvent ();
	void markEventAsDone (std::list<int> allIndex);
	void unDomarkEventAsDone();
	void clearActiveEvent();
	void unDoClearActiveEvent();
	void clearDoneEvent();
	void unDoClearDoneEvent();
	bool unDopreviousActions(std::string);
	Eventlist displayEvent (void);
	Eventlist displayDoneEvent (void);
	Event getEvent(int index);

};


//The storage class support the storing of data in Eventlist and stored in a local files
//Events are classified into incomplete and complete Events and stored in respective Eventlist.

#pragma once
#include "Eventlist.h"
#include <fstream>

class Storage
{
private:
	int _numberForUndo;
	Event _currentEvent;
	Eventlist _activeEvent;
	Eventlist _doneEvent;
	Eventlist _deletedActiveEvent;
	Eventlist _deletedDoneEvent;
	bool _possibleToUnDo;
	enum COMMAND_TYPE { ADD,UPDATE,DELETEEVENT,DONE,CLEARDONE,CLEARACTIVE,CLEAR,INVALID};
	COMMAND_TYPE findCommandType(std::string currentCommand);
	std::string _filename;

public:
	Storage(void);
	~Storage(void);
	void addEvent (Event);
	void unDoAddEvent ();
	void deleteEvent (std::list<int>);
	void unDoDeleteEvent ();
	void updateEvent (int, Event);
	void unDoUpdateEvent ();
	void markEventAsDone (std::list<int>);
	void unDomarkEventAsDone();
	void clearActiveEvent();
	void unDoClearActiveEvent();
	void clearDoneEvent();
	void unDoClearDoneEvent();
	void sortActiveEventlist();
	void sortDoneEventlist();
	void writeFile(std::string);
	void saveActiveEventsToFile();
	void saveDoneEventsToFile();
	void synchronizeDrive();
	void clearLocalDrive();
	void readFile();
	void readEventsFromFile(std::string);
	void changeCurrentDirectory(const char*);
	bool unDopreviousActions(std::string);
	Eventlist displayEvent (void);
	Eventlist displayDoneEvent (void);
	Event getEvent(int);
};


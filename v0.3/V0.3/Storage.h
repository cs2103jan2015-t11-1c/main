//@author A0116455H
//The storage class support the storing of data in Eventlist and stored in a local files
//Events are classified into incomplete and complete Events and stored in respective Eventlist.

#pragma once
#include "Eventlist.h"
#include <fstream>

const int MAX_PATH = 260;

class Storage {
private:
	Event _currentEvent;
	Eventlist _activeEvent;
	Eventlist _doneEvent;
	std::list<Eventlist> _previousActiveEvent;
	std::list<Eventlist> _previousDoneEvent;
	enum COMMAND_TYPE { ADD,UPDATE,DELETEEVENT,DONE,CLEARDONE,CLEARACTIVE,
		CLEAR,REPEAT,UPDATE_REPEAT,DELETE_REPEAT,DIRECTORY,INVALID};
	COMMAND_TYPE findCommandType(std::string currentCommand);
	std::string _filename;
	std::string _locationFile;
	char _defaultDirectory[MAX_PATH];
	std::list<std::string> _previousDirectory;
	int _numberOfRecuring;

public:
	Storage(void);
	~Storage(void);
	void addEvent (Event);
	void unDoAddEvent ();
	void repeatEvent(std::list<Event>);
	void unDoRepeatEvent();
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
	void undoChangeDirectory();
	void saveCurrentActiveEventList();
	void saveCurrentDoneEventList();
	void changeToPreviousActiveEventList();
	void changeToPreviousDoneEventList();
	void writeToLogfile(std::string, std::string);
	void getDirectory();
	void initialiseDirectory(const char* );
	void deleteRecurring(int);
	void undoDeleteRecurring();
	void updateRecurring(int, Event);
	void updateRecurringStartTime(int, int);
	void updateRecurringEndTime(int, int);
	void undoUpdateRecurring();
	bool unDopreviousActions(std::string);
	Eventlist displayEvent (void);
	Eventlist displayDoneEvent (void);
	Event getEvent(int);
	Event getDoneEvent(int);
	int getTotalNumberOfRecurringSeries();
};


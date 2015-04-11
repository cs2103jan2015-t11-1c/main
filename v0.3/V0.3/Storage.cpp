//@author A0116455H
//The Storage class will store all the data used in a program.
//Every time changes are made, it will save the data to a local file.

#include "Storage.h"
#include "windows.h"
#include <assert.h>

const std::string LOGFILE = "log.txt";
const std::string WARNING = "Warning";
const std::string INFOMATION = "Info";
const std::string WRONG = "Error";
const std::string CLEAR_ACTIVE_EVENTLIST = "Delete all incomplete events.";
const std::string CLEAR_DONE_EVENTLIST = "Delete all completed events.";
const std::string UNDO_CLEAR_ACTIVE_EVENTLIST = "Undo deleted all incomplete events.";
const std::string UNDO_CLEAR_DONE_EVENTLIST = "Undo deleted all completed events.";
const std::string ADD_ACTIVE_EVENT = "added to incomplete events.";
const std::string ADD_DONE_EVENT = "Event(s) has been marked as done.";
const std::string REPEAT_EVENTS = "Recuring events added.";
const std::string UNDO_REPEAT_EVENTS = "Undo recuring events";
const std::string UNDO_ADD_ACTIVE_EVENT = "Undo add event.";
const std::string UNDO_ADD_DONE_EVENT = "Undo mark event as done.";
const std::string DELETE_ACTIVE_EVENT = "Incomplete event(s) has been deleted.";
const std::string UNDO_DELETE_ACTIVE_EVENT = "Undo delete active event(s).";
const std::string UPDATE_ACTIVE_EVENT = "Update active event.";
const std::string UNDO_UPDATE_ACTIVE_EVENT = "Undo update active event.";
const std::string WRITE_TO_FILE = "Save data to local drive.";
const std::string READ_FROM_FILE = "Read data from local drive.";
const std::string INCOMPLETE_TASK = "Incomplete tasks: ";
const std::string DONE_TASK = "Done tasks: ";
const std::string WRITEFILE = "Writefile.";
const std::string SET_CURRENT_DIRECTORY = "Directory changed to: ";
const std::string DIRECTORY = "changing directory";
const std::string FRONT_TOKEN = " <";
const std::string BACK_TOKEN = "> ";
const std::string DEFAULT_FILE_NAME = "Minic.txt";
const std::string CMD_ADD = "add";
const std::string CMD_CLEAR = "clear";
const std::string CMD_DELETE = "delete";
const std::string CMD_UPDATE = "update";
const std::string CMD_DONE = "done";
const std::string CMD_CLEAR_DONE = "cleardone";
const std::string CMD_CLEAR_ACTIVE = "clearactive";
const std::string CMD_REPEAT = "repeat";
const std::string CMD_UPDATE_REPEAT = "update repeat";
const std::string CMD_DELETE_REPEAT = "delete repeat";
const std::string LOG_BACK_SYMBOL = "> ";
const std::string LOG_FRONT_SYMBOL = " <";
const std::string EMPTY_SPACE = " ";
const std::string START_INfO = "Starting Info: ";
const std::string END_INFO = "Ending Info: ";
const std::string NIL_IDENTIFIER = "Nil";
const std::string DEFAULT_LOCATION_NAME = "Directory.txt";
const std::string READ_A_EVENT = "analysing event from local file.";
const std::string RECURRING_NUMBER = "Recurring number: ";
const std::string NOT_RECURRING = "The event is not a recurring event.";
const std::string UPDATE_RECURRING = "Update recurring events.";
const std::string DELETE_RECURRING = "Recurring events deleted";
const std::string UNDO_DELETE_RECURRING = "Undo delete recurring events";
const std::string UNDO_UPDATE_RECURRING = "Undo update recurring events.";
const int ZERO = 0;
const int NUMBER_OF_DIGIT_FOR_DATE = 2;
const int NUMBER_OF_DIGIT_FOR_TIME = 4;
const int INVALID_NUMBER = -1;
const int ONE = 1;
char buffer[1000];
const int bufferSize = MAX_PATH;


Storage::Storage(void) {	
	_filename = DEFAULT_FILE_NAME;
	_locationFile = DEFAULT_LOCATION_NAME;
	GetCurrentDirectory(bufferSize, _defaultDirectory);
	getDirectory();
	_numberOfRecuring = ZERO;
}

Storage::~Storage(void) {
}

//Take in the previous command and perform the necessary undo functions
bool Storage::unDopreviousActions(std::string unDoCommand) {	
	COMMAND_TYPE command = findCommandType(unDoCommand);
	switch (command) {
	case ADD:
		unDoAddEvent();
		return true;
	case DONE:
		unDomarkEventAsDone();
		return true;
	case DELETEEVENT:
		unDoDeleteEvent();
		return true;
	case UPDATE:
		unDoUpdateEvent();
		return true;
	case CLEARACTIVE:
		unDoClearActiveEvent();
		return true;
	case CLEARDONE:
		unDoClearDoneEvent();
		return true;
	case CLEAR:
		unDoClearActiveEvent();
		unDoClearDoneEvent();
		return true;
	case REPEAT:
		unDoRepeatEvent();
		return true;
	case UPDATE_REPEAT:
		undoUpdateRecurring();
		return true;
	case DELETE_REPEAT:
		undoDeleteRecurring();
		return true;
	case INVALID:
		return false;
		}
	return false;
}

//Convert the command string to enum type.
Storage::COMMAND_TYPE Storage::findCommandType(std::string currentCommand) {		
	if (currentCommand == CMD_ADD) {
		return ADD;
	} else if (currentCommand == CMD_UPDATE) {
		return UPDATE;
	} else if (currentCommand == CMD_DELETE) {
		return DELETEEVENT;
	} else if (currentCommand == CMD_DONE) {
		return DONE;
	} else if (currentCommand == CMD_CLEAR_DONE) {
		return CLEARDONE;
	} else if (currentCommand == CMD_CLEAR_ACTIVE) {
		return CLEARACTIVE;
	} else if (currentCommand == CMD_CLEAR) {
		return CLEAR;
	} else if (currentCommand == CMD_REPEAT) {
		return REPEAT;
	} else if (currentCommand == CMD_UPDATE_REPEAT) {
		return UPDATE_REPEAT;
	} else if (currentCommand == CMD_DELETE_REPEAT) {
		return DELETE_REPEAT;
	} else {
		return INVALID;
	}
}
//When clear functions are called, current Eventlist is saved for undo purpose.
void Storage::clearActiveEvent() {
	saveCurrentActiveEventList();
	_activeEvent = Eventlist();
	writeToLogfile(INFOMATION, CLEAR_ACTIVE_EVENTLIST);
}

void Storage::clearDoneEvent() {	
	saveCurrentDoneEventList();
	_doneEvent = Eventlist();
	writeToLogfile(INFOMATION, CLEAR_DONE_EVENTLIST);
}

void Storage::unDoClearActiveEvent() {	
	changeToPreviousActiveEventList();
	writeToLogfile(INFOMATION, UNDO_CLEAR_ACTIVE_EVENTLIST);
}

void Storage::unDoClearDoneEvent() {
	changeToPreviousDoneEventList();
	writeToLogfile(INFOMATION, UNDO_CLEAR_DONE_EVENTLIST);
}

void Storage::saveCurrentActiveEventList() {
	_previousActiveEvent.push_back(_activeEvent);
}

void Storage::saveCurrentDoneEventList() {
	_previousDoneEvent.push_back(_doneEvent);
}

void Storage::changeToPreviousActiveEventList() {
	_activeEvent = _previousActiveEvent.back();
	_previousActiveEvent.pop_back();
}

void Storage::changeToPreviousDoneEventList() {
	_doneEvent = _previousDoneEvent.back();
	_previousDoneEvent.pop_back();
}

void Storage::addEvent(Event newEvent) {
	try {
		saveCurrentActiveEventList();
		_currentEvent = newEvent;
		_activeEvent.addEvent(_currentEvent); 
		std::string addInfomation;
		addInfomation = _currentEvent.displayEvent() + EMPTY_SPACE;
		addInfomation = addInfomation	+ ADD_ACTIVE_EVENT;
		writeToLogfile(INFOMATION, addInfomation);
	}
	catch(...) {
		std::cout << WRONG << EMPTY_SPACE << ADD_ACTIVE_EVENT;
	}
}

void Storage::unDoAddEvent () {
	changeToPreviousActiveEventList();
	writeToLogfile(INFOMATION, UNDO_ADD_ACTIVE_EVENT);
}

void Storage::repeatEvent(std::list<Event> allEvents) {
	saveCurrentActiveEventList();
	int identifier = _numberOfRecuring + ONE;
	try {
		while (!allEvents.empty()) {
		_currentEvent = allEvents.back();
		_currentEvent.changeRecurringTaskSeries(identifier);
		_activeEvent.addEvent(_currentEvent);
		allEvents.pop_back();
		}
		writeToLogfile(INFOMATION, REPEAT_EVENTS);
	}
	catch(...) {
		std::cout << WRONG << EMPTY_SPACE << REPEAT_EVENTS;
	}
	_numberOfRecuring = _numberOfRecuring + ONE;
}

void Storage::unDoRepeatEvent() {
	changeToPreviousActiveEventList();
	_numberOfRecuring = _numberOfRecuring - 1;
	writeToLogfile(INFOMATION, UNDO_REPEAT_EVENTS);
}

//Transfer the list of index Events from active Eventlist to done Eventlist.
void Storage::markEventAsDone (std::list<int> allIndex) {
	saveCurrentActiveEventList();
	saveCurrentDoneEventList();
	int i;
	try {
		allIndex.sort();
		while(!allIndex.empty()) {
			i=allIndex.back();
			_currentEvent = _activeEvent.getEvent(i);
			_activeEvent.deleteEvent(i);
			_doneEvent.addEvent(_currentEvent);
			allIndex.pop_back();
		}
		writeToLogfile(INFOMATION, ADD_DONE_EVENT);
	}
	catch(...) {
		std::cout << WRONG << EMPTY_SPACE << ADD_DONE_EVENT;
	}
}

void Storage::unDomarkEventAsDone() {	
	changeToPreviousActiveEventList();
	changeToPreviousDoneEventList();
	writeToLogfile(INFOMATION, UNDO_ADD_DONE_EVENT);
}

//Delete Events from the back of the active Eventlist.
void Storage::deleteEvent(std::list<int> allIndex) {	
	saveCurrentActiveEventList();
	int i;
	try {
		allIndex.sort();
		while(!allIndex.empty()) {
			i = allIndex.back();
			_currentEvent = _activeEvent.getEvent(i);
			_activeEvent.deleteEvent(i);
			allIndex.pop_back();
		}
		writeToLogfile(INFOMATION, DELETE_ACTIVE_EVENT);
	}
	catch(...) {
		std::cout << WRONG << EMPTY_SPACE << DELETE_ACTIVE_EVENT;
	}
}

void Storage::deleteRecurring(int inputIndex) {
	std::list<Event> allEvents = _activeEvent.returnAllEvent();
	std::list<Event>::iterator iter;
	int index = ZERO;
	_currentEvent = _activeEvent.getEvent(inputIndex);
	int recurringNumber = _currentEvent.getRecurringTaskSeries();
	if(recurringNumber == 0) {
		throw std::string(NOT_RECURRING);
	}
	std::list<int> numbers;
	for(iter = allEvents.begin(); iter != allEvents.end(); iter++) {
		index = index + ONE;
		if((*iter).getRecurringTaskSeries() == recurringNumber) {
			numbers.push_back(index);
		}
	}
	deleteEvent(numbers);
	_numberOfRecuring = _numberOfRecuring - ONE;
	writeToLogfile(INFOMATION, DELETE_RECURRING);
}

void Storage::unDoDeleteEvent() {	
	changeToPreviousActiveEventList();
	writeToLogfile(INFOMATION, UNDO_DELETE_ACTIVE_EVENT);
}

void Storage::undoDeleteRecurring(){
	changeToPreviousActiveEventList();
	_numberOfRecuring = _numberOfRecuring + ONE;
	writeToLogfile(INFOMATION, UNDO_DELETE_RECURRING);
}

Eventlist Storage::displayEvent(void) {	
	return _activeEvent;
}

Eventlist Storage::displayDoneEvent (void) {	
	return _doneEvent;
}

void Storage::updateEvent(int index, Event newEvent) {	
	saveCurrentActiveEventList();
	try {
		_activeEvent.updateEvent(index,newEvent);
		writeToLogfile(INFOMATION, UPDATE_ACTIVE_EVENT);
	}
	catch(...) {
		std::cout << WRONG << EMPTY_SPACE << UPDATE_ACTIVE_EVENT;
	}
}

void Storage::updateRecurring(int index, Event newEvent) {
	saveCurrentActiveEventList();
	std::list<Event> allEvents = _activeEvent.returnAllEvent();
	std::list<Event>::iterator iter;
	int indexForRecurring = ZERO;
	_currentEvent = _activeEvent.getEvent(index);
	int recurringNumber = _currentEvent.getRecurringTaskSeries();
	if(recurringNumber == 0) {
		throw std::string(NOT_RECURRING);
	}
	newEvent.changeRecurringTaskSeries(recurringNumber);
	for(iter = allEvents.begin(); iter != allEvents.end(); iter++) {
		indexForRecurring = indexForRecurring + ONE;
		if((*iter).getRecurringTaskSeries() == recurringNumber) {
			_activeEvent.updateEvent(indexForRecurring, newEvent);
		}
	}
	writeToLogfile(INFOMATION, UPDATE_RECURRING);
}

void Storage::unDoUpdateEvent() {   
	changeToPreviousActiveEventList();
	writeToLogfile(INFOMATION, UNDO_UPDATE_ACTIVE_EVENT);
}

void Storage::undoUpdateRecurring() {
	changeToPreviousActiveEventList();
	writeToLogfile(INFOMATION, UNDO_UPDATE_RECURRING);
}

Event Storage::getEvent(int index) {
	return _activeEvent.getEvent(index);
}

Event Storage::getDoneEvent(int index) {
	return _doneEvent.getEvent(index);
}

void Storage::sortActiveEventlist() {	
	_activeEvent.sortEvent();
}

void Storage::sortDoneEventlist() {	
	_doneEvent.sortEvent();
}

//Add the string to the system default file.
void Storage::writeFile(std::string eventToFile) {	
	try {
		std::ofstream destination;
		destination.open(_filename, std::ofstream::app);
		destination << eventToFile << std::endl;
		destination.close();
	}
	catch(...) {
		std::cout << WRONG << EMPTY_SPACE << WRITEFILE;
	}
}

//Save all the active Events to a local file.
void Storage::saveActiveEventsToFile() {
	std::list<Event> currentList = _activeEvent.returnAllEvent();
	std::list<Event>::iterator iter;
	for(iter = currentList.begin(); iter != currentList.end(); ++iter) { 
		writeFile(INCOMPLETE_TASK + (*iter).saveEvent());
	}
}

//Save all the done Events to a local file.
void Storage::saveDoneEventsToFile() {
	std::list<Event> currentList = _doneEvent.returnAllEvent();
	std::list<Event>::iterator iter;
	for(iter = currentList.begin(); iter != currentList.end(); ++iter) {
		writeFile(DONE_TASK + (*iter).saveEvent());
	}
}

//Synchonized storage data with the local file.
void Storage::synchronizeDrive() {
	clearLocalDrive();
	saveDoneEventsToFile();
	saveActiveEventsToFile();
	writeToLogfile(INFOMATION, WRITE_TO_FILE);
}

//Empty a local file.
void Storage::clearLocalDrive() {
	std::ofstream outputFile;
	outputFile.open(_filename);
	outputFile.close();
}

//Transfer the data from a local file to Storage.
void Storage::readFile() {
	std::ifstream textFile;
	std::string currentLine;
	textFile.open(_filename);
	while(getline(textFile,currentLine)) {
	readEventsFromFile(currentLine);
	}
	textFile.close();
	writeToLogfile(INFOMATION, READ_FROM_FILE);
}

void Storage::getDirectory() {
	std::ifstream textFile;
	std::string directory;
	textFile.open(_locationFile);
	getline(textFile,directory);
	initialiseDirectory(directory.c_str());
}

//Retrieve the Event information from a local file
//and store them in an Event then stored in the appropriate Eventlist.
void Storage::readEventsFromFile(std::string line) {
	std::string doneEventidentifier = DONE_TASK;
	std::size_t foundDone = line.find(doneEventidentifier);
	std::size_t startInfoFinder;
	std::size_t endInfoFinder;
	std::size_t recurringFinder;
	std::string title;
	std::string startday;
	std::string startmonth;
	std::string starttime;
	std::string startyear;
	std::string endday;
	std::string endmonth;
	std::string endtime;
	std::string endyear;
	std::string recurringNumber;
	Event newEvent;
	bool isActive = true;
	bool isRecurring = false;
	bool hasStartInfo = true;
	bool hasEndInfo = true;

	try {
		if (foundDone < std::string::npos) {
			line = line.substr(DONE_TASK.size());
			isActive = false;
		} else {
			line = line.substr(INCOMPLETE_TASK.size());
		}
		startInfoFinder = line.find(START_INfO);
		title = line.substr(ZERO,startInfoFinder - EMPTY_SPACE.size());
		line = line.substr(startInfoFinder + START_INfO.size());
		if (line.substr(ZERO,NIL_IDENTIFIER.size()) == NIL_IDENTIFIER) {
			line = line.substr(NIL_IDENTIFIER.size() + EMPTY_SPACE.size());
			hasStartInfo = false;
		} else {
			startday = line.substr(ZERO,NUMBER_OF_DIGIT_FOR_DATE);
			line = line.substr(NUMBER_OF_DIGIT_FOR_DATE + EMPTY_SPACE.size());
			startmonth = line.substr(ZERO,NUMBER_OF_DIGIT_FOR_DATE);
			line = line.substr(NUMBER_OF_DIGIT_FOR_DATE + EMPTY_SPACE.size());
			starttime = line.substr(ZERO,NUMBER_OF_DIGIT_FOR_TIME);
			line = line.substr(NUMBER_OF_DIGIT_FOR_TIME + EMPTY_SPACE.size());
			startyear = line.substr(ZERO,NUMBER_OF_DIGIT_FOR_TIME);
		}
		endInfoFinder = line.find(END_INFO);
		line = line.substr(endInfoFinder + END_INFO.size());
		if (line.substr(ZERO,NIL_IDENTIFIER.size()) == NIL_IDENTIFIER) {
			line = line.substr(NIL_IDENTIFIER.size() + EMPTY_SPACE.size());
			hasEndInfo = false;
		} else {
			endday = line.substr(ZERO,NUMBER_OF_DIGIT_FOR_DATE);
			line = line.substr(NUMBER_OF_DIGIT_FOR_DATE + EMPTY_SPACE.size());
			endmonth = line.substr(ZERO,NUMBER_OF_DIGIT_FOR_DATE);
			line = line.substr(NUMBER_OF_DIGIT_FOR_DATE + EMPTY_SPACE.size());
			endtime = line.substr(ZERO,NUMBER_OF_DIGIT_FOR_TIME);
			line = line.substr(NUMBER_OF_DIGIT_FOR_TIME + EMPTY_SPACE.size());
			endyear = line.substr(ZERO,NUMBER_OF_DIGIT_FOR_TIME);
			line = line.substr(NUMBER_OF_DIGIT_FOR_TIME);
		}
		recurringFinder = line.find(RECURRING_NUMBER);
		if ( recurringFinder < std::string::npos) {
			line = line.substr(RECURRING_NUMBER.size() + EMPTY_SPACE.size());
			recurringNumber = line;
			isRecurring = true;
		}
	}
	catch(...) {
		std::cout << WRONG << EMPTY_SPACE << READ_A_EVENT;
	}
	if(hasEndInfo) {
		newEvent = Event(title,stoi(endday), stoi(endmonth),stoi(endtime));
		newEvent.changeEndYear(stoi(endyear));
	} else {
		newEvent = Event(title,INVALID_NUMBER,INVALID_NUMBER,INVALID_NUMBER);
	}
	if (hasStartInfo) {	
		newEvent.changeStartDay(stoi(startday));
		newEvent.changeStartMonth(stoi(startmonth));
		newEvent.changeStartTime(stoi(starttime));
		newEvent.changeStartYear(stoi(startyear));
	}
	if (isRecurring) {
		newEvent.changeRecurringTaskSeries(stoi(recurringNumber));
	}
	if (isActive) {	
		_activeEvent.addEvent(newEvent);
	} else { 
		_doneEvent.addEvent(newEvent);
	}
}

//Allow user to change the directory of the local file.
void Storage::changeCurrentDirectory(const char* newDirectory) {
	try {
		const char* newDir = newDirectory;
		SetCurrentDirectory(_defaultDirectory);
		std::ofstream destination;
		destination.open(_locationFile);
		destination << newDir;
		SetCurrentDirectory(newDir);
		synchronizeDrive();
		std::string messageForLog;
		messageForLog = SET_CURRENT_DIRECTORY + newDir;
		writeToLogfile(INFOMATION, messageForLog);
	}
	catch(...) {
		std::cout << WRONG << EMPTY_SPACE << DIRECTORY;
	}
}

void Storage::initialiseDirectory(const char* newDirectory) {
	SetCurrentDirectory(newDirectory);
}


void Storage::writeToLogfile(std::string type, std::string message) {
	std::ofstream destination;
	destination.open(LOGFILE,std::ofstream::app);
	time_t rawtime;
	struct tm  timeinfo;
	rawtime = time (ZERO);
	localtime_s(&timeinfo, &rawtime);
	asctime_s(buffer,&timeinfo) ;
	destination	<< buffer << LOG_FRONT_SYMBOL << type << LOG_BACK_SYMBOL;
	destination	<< message << std::endl;
}

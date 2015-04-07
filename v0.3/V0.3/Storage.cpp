//The Storage class will store all the data used in a program.
//Every time changes are made, it will save the data to a local file.

#include "Storage.h"
#include "windows.h"


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
const std::string SET_CURRENT_DIRECTORY = "Directory changed to: ";
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
const std::string LOG_BACK_SYMBOL = "> ";
const std::string LOG_FRONT_SYMBOL = " <";
const std::string EMPTY_SPACE = " ";
const std::string START_INfO_IDENTIFIER = "Starting Info: ";
const std::string END_INFO_IDENTIFIER = "Ending Info: ";
const std::string NIL_IDENTIFIER = "Nil";
const int ZERO = 0;
const int NUMBER_OF_DIGIT_FOR_DATE = 2;
const int NUMBER_OF_DIGIT_FOR_TIME = 4;
const int INVALID_NUMBER = -1;
char buffer[1000];


Storage::Storage(void) {	
	_filename = DEFAULT_FILE_NAME;
}

Storage::~Storage(void) {
}

//Take in the previous command and perform the necessary undo functions
bool Storage::unDopreviousActions(std::string unDoCommand){	
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
	case INVALID:
		return false;
		}
	return false;
}

//Convert the command string to enum type.
Storage::COMMAND_TYPE Storage::findCommandType(std::string currentCommand){		
	if (currentCommand == CMD_ADD){
			return ADD;
		}
	else if (currentCommand == CMD_UPDATE){
			return UPDATE;
		}
	else if (currentCommand == CMD_DELETE){
			return DELETEEVENT;
		} 
	else if (currentCommand == CMD_DONE){
			return DONE;
		}
	else if (currentCommand == CMD_CLEAR_DONE){
			return CLEARDONE;
		}
	else if (currentCommand == CMD_CLEAR_ACTIVE){
			return CLEARACTIVE;
		}
	else if (currentCommand == CMD_CLEAR){
			return CLEAR;
		}
		else return INVALID;
}

//When clear functions are called, current Eventlist is saved for undo purpose.
void Storage::clearActiveEvent(){
	saveCurrentActiveEventList();
	_activeEvent = Eventlist();
	writeToLogfile(INFOMATION, CLEAR_ACTIVE_EVENTLIST);
}

void Storage::clearDoneEvent(){	
	saveCurrentDoneEventList();
	_doneEvent = Eventlist();
	writeToLogfile(INFOMATION, CLEAR_DONE_EVENTLIST);
}

void Storage::unDoClearActiveEvent(){	
	changeToPreviousActiveEventList();
	writeToLogfile(INFOMATION, UNDO_CLEAR_ACTIVE_EVENTLIST);
}

void Storage::unDoClearDoneEvent(){
	changeToPreviousDoneEventList();
	writeToLogfile(INFOMATION, UNDO_CLEAR_DONE_EVENTLIST);
}

void Storage::saveCurrentActiveEventList(){
	_previousActiveEvent.push_back(_activeEvent);
}

void Storage::saveCurrentDoneEventList(){
	_previousDoneEvent.push_back(_doneEvent);
}

void Storage::changeToPreviousActiveEventList(){
	_activeEvent = _previousActiveEvent.back();
	_previousActiveEvent.pop_back();
}

void Storage::changeToPreviousDoneEventList(){
	_doneEvent = _previousDoneEvent.back();
	_previousDoneEvent.pop_back();
}

void Storage::addEvent(Event newEvent){
	saveCurrentActiveEventList();
	_currentEvent = newEvent;
	_activeEvent.addEvent(_currentEvent); 
	std::string addInfomation;
	addInfomation = _currentEvent.displayEvent() + EMPTY_SPACE + ADD_ACTIVE_EVENT;
	writeToLogfile(INFOMATION, addInfomation);
}

void Storage::unDoAddEvent (){
	changeToPreviousActiveEventList();
	writeToLogfile(INFOMATION, UNDO_ADD_ACTIVE_EVENT);
}

//Transfer the list of index Events from active Eventlist to done Eventlist.
void Storage::markEventAsDone (std::list<int> allIndex){
	saveCurrentActiveEventList();
	saveCurrentDoneEventList();
	int i;
	allIndex.sort();
	while(!allIndex.empty()){
	i=allIndex.back();
	_currentEvent = _activeEvent.getEvent(i);
	_activeEvent.deleteEvent(i);
	_doneEvent.addEvent(_currentEvent);
	allIndex.pop_back();
	}
	writeToLogfile(INFOMATION, ADD_DONE_EVENT);
}

void Storage::unDomarkEventAsDone(){	
	changeToPreviousActiveEventList();
	changeToPreviousDoneEventList();
	writeToLogfile(INFOMATION, UNDO_ADD_DONE_EVENT);
}

//Delete Events from the back of the active Eventlist.
void Storage::deleteEvent(std::list<int> allIndex){	
	saveCurrentActiveEventList();
	int i;
	allIndex.sort();
	while(!allIndex.empty()){
	i=allIndex.back();
	_currentEvent = _activeEvent.getEvent(i);
	_activeEvent.deleteEvent(i);
	allIndex.pop_back();
	}
	writeToLogfile(INFOMATION, DELETE_ACTIVE_EVENT);
}

void Storage::unDoDeleteEvent (){	
	changeToPreviousActiveEventList();
	writeToLogfile(INFOMATION, UNDO_DELETE_ACTIVE_EVENT);
}

Eventlist Storage::displayEvent(void) {	
	return _activeEvent;
}

Eventlist Storage::displayDoneEvent (void){	
	return _doneEvent;
}

void Storage::updateEvent (int index, Event newEvent){	
	saveCurrentActiveEventList();
	_activeEvent.updateEvent(index,newEvent);
	writeToLogfile(INFOMATION, UPDATE_ACTIVE_EVENT);
}

void Storage::unDoUpdateEvent (){   
	changeToPreviousActiveEventList();
	writeToLogfile(INFOMATION, UNDO_UPDATE_ACTIVE_EVENT);
}

Event Storage::getEvent(int index){
	return _activeEvent.getEvent(index);
}

Event Storage::getDoneEvent(int index){
	return _doneEvent.getEvent(index);
}

void Storage::sortActiveEventlist(){	
	_activeEvent.sortEvent();
}

void Storage::sortDoneEventlist(){	
	_doneEvent.sortEvent();
}

//Add the string to the system default file.
void Storage::writeFile(std::string eventToFile){	
	std::ofstream destination;
	destination.open(_filename, std::ofstream::app);
	destination << eventToFile << std::endl;
	destination.close();
}

//Save all the active Events to a local file.
void Storage::saveActiveEventsToFile(){
	std::list<Event> currentList = _activeEvent.returnAllEvent();
	std::list<Event>::iterator iter;
	for(iter = currentList.begin(); iter != currentList.end(); ++iter){
		writeFile(INCOMPLETE_TASK + (*iter).saveEvent());
	}
}

//Save all the done Events to a local file.
void Storage::saveDoneEventsToFile(){
	std::list<Event> currentList = _doneEvent.returnAllEvent();
	std::list<Event>::iterator iter;
	for(iter = currentList.begin(); iter != currentList.end(); ++iter){
		writeFile(DONE_TASK + (*iter).saveEvent());
	}
}

//Synchonized storage data with the local file.
void Storage::synchronizeDrive(){
	clearLocalDrive();
	const int bufferSize = MAX_PATH;
    char oldDir[bufferSize];
	GetCurrentDirectory(bufferSize, oldDir);
	writeFile(oldDir);
	saveDoneEventsToFile();
	saveActiveEventsToFile();
	writeToLogfile(INFOMATION, WRITE_TO_FILE);
}

//Empty a local file.
void Storage::clearLocalDrive(){
	std::ofstream outputFile;
	outputFile.open(_filename);
	outputFile.close();
}

//Transfer the data from a local file to Storage.
void Storage::readFile(){
	std::ifstream textFile;
	std::string currentLine;
	textFile.open(_filename);
	getline(textFile,currentLine);
	if (!currentLine.empty()) {
	const char * oldDirectory = currentLine.c_str();
	changeCurrentDirectory(oldDirectory);
	while(getline(textFile,currentLine)){
		readEventsFromFile(currentLine);
		}
	}
	textFile.close();
	writeToLogfile(INFOMATION, READ_FROM_FILE);
}

//Retrieve the Event information from a local file
//and store them in an Event then stored in the appropriate Eventlist.
void Storage::readEventsFromFile(std::string currentEventLine){
	std::string doneEventidentifier = DONE_TASK;
	std::size_t foundDone = currentEventLine.find(doneEventidentifier);
	std::size_t startInfoFinder;
	std::size_t endInfoFinder;
	std::string title;
	std::string startday;
	std::string startmonth;
	std::string starttime;
	std::string startyear;
	std::string endday;
	std::string endmonth;
	std::string endtime;
	std::string endyear;
	Event newEvent;
	bool isActive = true;
	bool hasStartInfo = true;
	bool hasEndInfo = true;

	if (foundDone < std::string::npos){
		currentEventLine = currentEventLine.substr(DONE_TASK.size());
		isActive = false;
	} else {
		currentEventLine = currentEventLine.substr(INCOMPLETE_TASK.size());
	}
	startInfoFinder = currentEventLine.find(START_INfO_IDENTIFIER);
	title = currentEventLine.substr(ZERO,startInfoFinder - EMPTY_SPACE.size());
	currentEventLine = currentEventLine.substr(startInfoFinder + START_INfO_IDENTIFIER.size());
	if (currentEventLine.substr(ZERO,NIL_IDENTIFIER.size()) == NIL_IDENTIFIER) {
		currentEventLine = currentEventLine.substr(NIL_IDENTIFIER.size() + EMPTY_SPACE.size());
		hasStartInfo = false;
	} else {
		startday = currentEventLine.substr(ZERO,NUMBER_OF_DIGIT_FOR_DATE);
		currentEventLine = currentEventLine.substr(NUMBER_OF_DIGIT_FOR_DATE + EMPTY_SPACE.size());
		startmonth = currentEventLine.substr(ZERO,NUMBER_OF_DIGIT_FOR_DATE);
		currentEventLine = currentEventLine.substr(NUMBER_OF_DIGIT_FOR_DATE + EMPTY_SPACE.size());
		starttime = currentEventLine.substr(ZERO,NUMBER_OF_DIGIT_FOR_TIME);
		currentEventLine = currentEventLine.substr(NUMBER_OF_DIGIT_FOR_TIME + EMPTY_SPACE.size());
		startyear = currentEventLine.substr(ZERO,NUMBER_OF_DIGIT_FOR_TIME);
	}
	endInfoFinder = currentEventLine.find(END_INFO_IDENTIFIER);
	currentEventLine = currentEventLine.substr(endInfoFinder + END_INFO_IDENTIFIER.size());
	if (currentEventLine.substr(ZERO,NIL_IDENTIFIER.size()) == NIL_IDENTIFIER) {
		currentEventLine = currentEventLine.substr(NIL_IDENTIFIER.size() + EMPTY_SPACE.size());
		hasEndInfo = false;
	} else {
		endday = currentEventLine.substr(ZERO,NUMBER_OF_DIGIT_FOR_DATE);
		currentEventLine = currentEventLine.substr(NUMBER_OF_DIGIT_FOR_DATE + EMPTY_SPACE.size());
		endmonth = currentEventLine.substr(ZERO,NUMBER_OF_DIGIT_FOR_DATE);
		currentEventLine = currentEventLine.substr(NUMBER_OF_DIGIT_FOR_DATE + EMPTY_SPACE.size());
		endtime = currentEventLine.substr(ZERO,NUMBER_OF_DIGIT_FOR_TIME);
		currentEventLine = currentEventLine.substr(NUMBER_OF_DIGIT_FOR_TIME + EMPTY_SPACE.size());
		endyear = currentEventLine.substr(ZERO,NUMBER_OF_DIGIT_FOR_TIME);
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
	if (isActive) {	
		_activeEvent.addEvent(newEvent);
	} else { _doneEvent.addEvent(newEvent);
		}
}

//Allow user to change the directory of the local file.
void Storage::changeCurrentDirectory(const char* newDirectory){
	const int bufferSize = MAX_PATH;
    char oldDir[bufferSize];
	GetCurrentDirectory(bufferSize, oldDir);
	const char* newDir = newDirectory;
	if (oldDir != newDir) {
	SetCurrentDirectory(newDir);
	std::string messageForLog;
	messageForLog = SET_CURRENT_DIRECTORY + newDir;
	writeToLogfile(INFOMATION, messageForLog);
	}
}

void Storage::writeToLogfile(std::string type, std::string message){
	std::ofstream destination;
	destination.open(LOGFILE,std::ofstream::app);
	time_t rawtime;
	struct tm  timeinfo;
	rawtime = time (ZERO);
	localtime_s(&timeinfo, &rawtime);
	asctime_s(buffer,&timeinfo) ;
	destination	<< buffer << LOG_FRONT_SYMBOL << type << LOG_BACK_SYMBOL << message << std::endl;
}
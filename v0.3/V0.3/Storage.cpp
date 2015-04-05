#include "Storage.h"
#include "windows.h"


Storage::Storage(void){	
	_filename = "Minic.txt";
}

Storage::~Storage(void){
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
	if (currentCommand == "add"){
			return ADD;
		}
		else if (currentCommand == "update"){
			return UPDATE;
		}
		else if (currentCommand == "delete"){
			return DELETEEVENT;
		} 
		else if (currentCommand == "done"){
			return DONE;
		}
		else if (currentCommand == "cleardone"){
			return CLEARDONE;
		}
		else if (currentCommand == "clearactive"){
			return CLEARACTIVE;
		}
		else if (currentCommand == "clear"){
			return CLEAR;
		}
		else return INVALID;
}

//When clear functions are called, current Eventlist is saved for undo purpose.
void Storage::clearActiveEvent(){	
	saveCurrentActiveEventList();
	_activeEvent = Eventlist();
}

void Storage::clearDoneEvent(){	
	saveCurrentDoneEventList();
	_doneEvent = Eventlist();
}

void Storage::unDoClearActiveEvent(){	
	changeToPreviousActiveEventList();
}

void Storage::unDoClearDoneEvent(){
	changeToPreviousDoneEventList();
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
}

void Storage::unDoAddEvent (){
	changeToPreviousActiveEventList();
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
}

void Storage::unDomarkEventAsDone(){	
	changeToPreviousActiveEventList();
	changeToPreviousDoneEventList();
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
}

void Storage::unDoDeleteEvent (){	
	changeToPreviousActiveEventList();
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
}

void Storage::unDoUpdateEvent (){   
	changeToPreviousActiveEventList();
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
		writeFile("Incomplete tasks: " + (*iter).readEvent());
	}
}

//Save all the done Events to a local file.
void Storage::saveDoneEventsToFile(){
	std::list<Event> currentList = _doneEvent.returnAllEvent();
	std::list<Event>::iterator iter;
	for(iter = currentList.begin(); iter != currentList.end(); ++iter){
		writeFile("Done tasks: " + (*iter).readEvent());
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
}

//Retrieve the Event information from a local file
//and store them in an Event then stored in the appropriate Eventlist.
void Storage::readEventsFromFile(std::string currentEventLine){
	int index;
	std::string doneEventidentifier = "Done tasks: ";
	std::string activeEventidentifier = "Incomplete tasks: ";
	std::string floatingEventidentifier = " no specific deadline";
	std::string changeOfYearidentifier = "Year: ";
	std::size_t foundDone = currentEventLine.find(doneEventidentifier);
	std::size_t floatingEventFinder;
	std::size_t startingEvent;
	std::string title;
	std::string startday;
	std::string startmonth;
	std::string starttime;
	std::string endday;
	std::string endmonth;
	std::string endtime;
	Event newEvent;
	bool isActive = false;
	bool hasStartInfo = false;
	bool hasNoDeadline = false;

	if (foundDone < std::string::npos){
		currentEventLine = currentEventLine.substr(12);
		floatingEventFinder = currentEventLine.find(floatingEventidentifier);
		if (floatingEventFinder < std::string::npos)
		{	title = currentEventLine.substr(0,floatingEventFinder);
			hasNoDeadline = true;}
		else {
		startingEvent = currentEventLine.find(" start from ");
		if (startingEvent < std::string::npos)
		{	
			index = currentEventLine.find(" start from ");
			title = currentEventLine.substr(0, index);
			currentEventLine = currentEventLine.substr(index+12);
			startday = currentEventLine.substr(0,2);
			startmonth = currentEventLine.substr(3,2);
			starttime = currentEventLine.substr(6,4);
			endday = currentEventLine.substr(18,2);
			endmonth = currentEventLine.substr(21,2);
			endtime = currentEventLine.substr(24,4);
			hasStartInfo = true;
		}
		else {	index = currentEventLine.find(" is due ");
				title = currentEventLine.substr(0, index);
				currentEventLine = currentEventLine.substr(index+8);
				endday = currentEventLine.substr(0,2);
				endmonth = currentEventLine.substr(3,2);
				endtime = currentEventLine.substr(6,4);
		}
		}
	} else {
		isActive = true;
		currentEventLine = currentEventLine.substr(18);
		floatingEventFinder = currentEventLine.find(floatingEventidentifier);
		if (floatingEventFinder < std::string::npos)
		{	title = currentEventLine.substr(0,floatingEventFinder);
		hasNoDeadline = true;}
		else {
		startingEvent = currentEventLine.find(" start from ");
		if (startingEvent < std::string::npos)
		{	index = currentEventLine.find(" start from ");
			title = currentEventLine.substr(0, index);
			currentEventLine = currentEventLine.substr(index+12);
			startday = currentEventLine.substr(0,2);
			startmonth = currentEventLine.substr(3,2);
			starttime = currentEventLine.substr(6,4);
			endday = currentEventLine.substr(18,2);
			endmonth = currentEventLine.substr(21,2);
			endtime = currentEventLine.substr(24,4);
			hasStartInfo = true;
		}
		else {	index = currentEventLine.find(" is due ");
				title = currentEventLine.substr(0, index);
				currentEventLine = currentEventLine.substr(index+8);
				endday = currentEventLine.substr(0,2);
				endmonth = currentEventLine.substr(3,2);
				endtime = currentEventLine.substr(6,4);
		}
	}
	}
	if(hasNoDeadline) {
		newEvent = Event(title,-1,-1,-1);}
	else {
		newEvent = Event(title,stoi(endday), stoi(endmonth),stoi(endtime));}

	if (hasStartInfo)
	{	newEvent.changeStartDay(stoi(startday));
		newEvent.changeStartMonth(stoi(startmonth));
		newEvent.changeStartTime(stoi(starttime));
	}
	if (isActive){	
		_activeEvent.addEvent(newEvent);}
	else _doneEvent.addEvent(newEvent);
}

//Allow user to change the directory of the local file.
void Storage::changeCurrentDirectory(const char* newDirectory){
	const int bufferSize = MAX_PATH;
    char oldDir[bufferSize];
	GetCurrentDirectory(bufferSize, oldDir);
	const char* newDir = newDirectory;
	SetCurrentDirectory(newDir);
	/*std::cout << "Set current directory to " << newDir << '\n'; */
}

/*const int bufferSize = MAX_PATH;
    char oldDir[bufferSize];
	GetCurrentDirectory(bufferSize, oldDir);
	std::cout << "Current directory: " << oldDir << '\n';
	const char* newDir;
	char newdir[100];
	cin >> newdir;
	newDir = newdir;
	SetCurrentDirectory(newDir);
	std::cout << "Set current directory to " << newDir << '\n';

	*/
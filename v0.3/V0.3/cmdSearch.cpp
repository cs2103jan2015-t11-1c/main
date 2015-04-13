//@author A0115429H
#include "cmdSearch.h"
#include <sstream>

const static std::string MESSAGE_EVENT_NOT_FOUND = "Sorry! No relevant event found.\n\n"; 
const static std::string DOT = ".";
const static std::string TWO_LINES = "\n\n";

CmdSearch::CmdSearch(void){
}


CmdSearch::~CmdSearch(void){
}

//search for key words from task list
std::string CmdSearch::executecmdSearch(Storage& _storage){
	Eventlist events = _storage.displayEvent();
	std::list<Event> allEvents = events.returnAllEvent();
	int eventsNumber = events.getTotalNumberOfEvents();

	searchForEvent(allEvents, eventsNumber);

	if (_eventFound.getTotalNumberOfEvents() != 0) {
		_feedback = printEventFound();
	}else{
		_feedback = MESSAGE_EVENT_NOT_FOUND;
	}

	_eventFound.clearEventlist();
	_eventNumbers.clear();

	return _feedback;

}

//this function converts upper case letter to lower case
std::string CmdSearch::lowercaseCommandWord(std::string commandWord){
	int n = commandWord.size();
	for( int i = 0; i < n; i++){
		if(commandWord[i] <='Z' && commandWord[i] >= 'A'){
			commandWord[i] = commandWord[i] - ('Z'-'z');
		}
	}

  return commandWord;
}

void CmdSearch::searchForEvent(std::list<Event> allEvents, int){
	std::string keyword = _taskName;
	std::string taskName = lowercaseCommandWord(keyword);
	std::list<Event>::iterator Tcount;
	std::string eventName;
	int Tindex;
	int eventNumber = 0;
	Event currentEvent;

	//tokenize key words
	using namespace std;
	stringstream ss(taskName);
	string buffer;
	vector<string> tokens;
	while (ss >> buffer) {
		tokens.push_back(buffer);
	}
	int i = 0;
	int size = tokens.size();

	for (Tcount = allEvents.begin(); Tcount != allEvents.end(); Tcount++) {
		eventNumber++;
		currentEvent = *Tcount;
		eventName = currentEvent.getTaskName();
		stringstream str(eventName);
		string buf;
		vector<string> task;
		while (str >> buf) {
			task.push_back(buf);
		}
		int taskSize = task.size();
		std::string newEventName = lowercaseCommandWord(eventName);

		//check if each token of key words match each token of task name
	for (i = 0 ; i < taskSize ; i++) {
		for (int j = 0; j < size; j++){
			if(tokens[j] == task[i]) {
			_eventNumbers.push_back(eventNumber);
			_eventFound.addEvent(currentEvent);
			break;
			}
		}
	}
	}
}

std::string CmdSearch::printEventFound(){
	std::ostringstream feedback;
	std::list<Event>::iterator Titer;
	Event currentEvent;
	int eventNumber;
	int Tcount = 0;
	std::list<Event> eventFound = _eventFound.returnAllEvent();
	
	for(Titer = eventFound.begin(); Titer != eventFound.end(); Titer++){
		currentEvent = *Titer;
		eventNumber = _eventNumbers[Tcount];
		feedback << std::setw(3) << eventNumber << DOT << currentEvent.displayEvent() << TWO_LINES;
		Tcount ++;
	}

	return feedback.str();
}
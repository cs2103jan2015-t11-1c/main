//@author A0115429H
#include "cmdDisplay.h"
#include "Storage\Storage.h"
#include <sstream>

const static std::string MESSAGE_EMPTY_ACTIVE_EVENTS = "Currently no active event. \n\n";
const static std::string MESSAGE_NO_EVENT_TODAY = "No Event today! \n\n";
const static std::string MESSAGE_NO_EVENT_TOMORROW = "No Event tomorrow! \n\n";
const static int NUMBER_OF_TASK_TO_DISPLAY = 21;
const static std::string NEW_LINE = "\n";
const static std::string DOT = ".";
const static std::string INFO = "Info";
const static std::string EMPTY_STRING = "";
const static std::string LOG_DISPLAY = "executed cmdDisplay";
const static std::string LOG_DISPLAYALL = "executed cmdDisplayall";

CmdDisplay::CmdDisplay(void){
}

CmdDisplay::~CmdDisplay(void){
}

//check if number of task is zero
bool CmdDisplay::isEmptyEventsStorage(Storage& _storage){
	bool isEmpty = false;
	Eventlist activeEvents = _storage.displayEvent();
	if(activeEvents.getTotalNumberOfEvents() == 0){
		isEmpty = true;
	}

	return isEmpty;
}
//Display all tasks, active tasks, tasks done, tasks due/start today or tasks due/start tomorrow.
std::string CmdDisplay::executecmdDisplay(Storage& _storage){
	if(isEmptyEventsStorage(_storage)){
		return MESSAGE_EMPTY_ACTIVE_EVENTS;
	}

	switch (_commandWord)
	{
	case DISPLAY:
		return cmdDisplayActive(_storage);
	case DISPLAYDONE:
		return cmdDisplayDone(_storage);
	case DISPLAYTODAY:
		return cmdDisplayToday(_storage);
	case DISPLAYALL:
		return cmdDisplayAll(_storage);
	case DISPLAYTOMORROW:
		return cmdDisplayTomorrow(_storage);
	default:
		break;
	} 	
	return EMPTY_STRING;
}

//display active events
std::string CmdDisplay::cmdDisplayActive(Storage& _storage){
	Eventlist activeEvents = _storage.displayEvent();
	std::list<Event> currentList = activeEvents.returnAllEvent();

	std::string feedback;
	feedback = eventsToDisplay(currentList);
	return feedback;
}

//@author A0114301E
//display completed events
std::string CmdDisplay::cmdDisplayDone(Storage& _storage) {
	Eventlist doneEvents = _storage.displayDoneEvent();
	std::list<Event> currentList = doneEvents.returnAllEvent();
	std::string feedback;
	feedback = eventsToDisplay(currentList);
	Storage storage;
	storage.writeToLogfile(INFO,LOG_DISPLAY);
	return feedback;
}

std::string CmdDisplay::cmdDisplayAll(Storage& _storage) {
	Eventlist allTasks = _storage.displayEvent();
	std::list<Event> allEventList = allTasks.returnAllEvent();
	std::string feedback;
	feedback = allEvents(allEventList);
	Storage storage;
	storage.writeToLogfile(INFO,LOG_DISPLAYALL);
	return feedback;
}

//@author A0115429H
//display events today
std::string CmdDisplay::cmdDisplayToday(Storage& _storage){
	std::string feedback;

	std::list<Event> eventsToday;
	Eventlist events = _storage.displayEvent();
	std::list<Event> allEvents = events.returnAllEvent();
	int eventsNumber = events.getTotalNumberOfEvents();

	std::list<Event>::iterator Tcount;

	Event currentEvent;
	int taskStartMonth;
	int taskStartDay;
	int taskEndMonth;
	int taskEndDay;

	for(Tcount = allEvents.begin(); Tcount != allEvents.end(); Tcount++){
		currentEvent = *Tcount;
		taskStartMonth = currentEvent.getStartMonth();
		taskStartDay = currentEvent.getStartDate();
	    taskEndMonth = currentEvent.getEndMonth();
	    taskEndDay = currentEvent.getEndDate();

		if(isEventToday(taskStartMonth, taskStartDay, taskEndMonth, taskEndDay)){
			eventsToday.push_back(currentEvent);
		}
	}

	if (eventsToday.size() != 0){
		feedback = eventsToDisplay(eventsToday);
	}else{
		feedback = MESSAGE_NO_EVENT_TODAY;
	}

	return feedback;
}

bool CmdDisplay::isEventToday(int taskStartMonth, int taskStartDay, int taskEndMonth, int taskEndDay){
	bool isEventToday = false;
	
	time_t t = time(0);
	struct tm now;
	localtime_s (&now, &t);
	int currentMonth = now.tm_mon + 1;
	int currentDay = now.tm_mday;

	if (((taskStartMonth == currentMonth) & (taskStartDay == currentDay)) || ((taskEndMonth == currentMonth) & (taskEndDay == currentDay))) {
		isEventToday = true;
	}

	return isEventToday;
}

//@author A0114301E

bool CmdDisplay::isEventTomorrow(int taskStartMonth, int taskStartDay, int taskEndMonth, int taskEndDay) {
	bool isEventTomorrow = false;
	
	time_t t = time(0);
	struct tm now;
	localtime_s (&now, &t);
	int currentMonth = now.tm_mon + 1;
	int currentDay = now.tm_mday + 1;

	if (((taskStartMonth == currentMonth) & (taskStartDay == currentDay)) || ((taskEndMonth == currentMonth) & (taskEndDay == currentDay))) {
		isEventTomorrow = true;
	}

	return isEventTomorrow;
}

//set the number of tasks to be displayed to be 20
std::string CmdDisplay::eventsToDisplay(std::list<Event> events) {
	std::ostringstream display;
	int i = 1;
	std::list<Event>::iterator iter;
	for (iter = events.begin(); iter != events.end() && i < NUMBER_OF_TASK_TO_DISPLAY; ++iter) {
		display  << std::setw(3) << i << DOT << (*iter).displayEvent() << NEW_LINE;
		i++;
	}
	display << NEW_LINE;

	return display.str();
}

//display events due tomorrow or start from tomorrow
std::string CmdDisplay::cmdDisplayTomorrow(Storage& _storage) {
	std::string feedback;
	std::list<Event> eventsTomorrow;
	Eventlist events = _storage.displayEvent();
	std::list<Event> allEvents = events.returnAllEvent();
	int eventsNumber = events.getTotalNumberOfEvents();

	std::list<Event>::iterator Tcount;

	Event currentEvent;
	int taskStartMonth;
	int taskStartDay;
	int taskEndMonth;
	int taskEndDay;

	for (Tcount = allEvents.begin(); Tcount != allEvents.end(); Tcount++){
		currentEvent = *Tcount;
		taskStartMonth = currentEvent.getStartMonth();
		taskStartDay = currentEvent.getStartDate();
	    taskEndMonth = currentEvent.getEndMonth();
	    taskEndDay = currentEvent.getEndDate();

		if (isEventTomorrow(taskStartMonth, taskStartDay, taskEndMonth, taskEndDay)){
			eventsTomorrow.push_back(currentEvent);
		}
	}

	if (eventsTomorrow.size() != 0){
		feedback = eventsToDisplay(eventsTomorrow);
	} else {
		feedback = MESSAGE_NO_EVENT_TOMORROW;
	}

	return feedback;
}

//@author A0114301E
//all events
std::string CmdDisplay::allEvents(std::list<Event> events) {
	std::ostringstream display;
	int i = 1;
	std::list<Event>::iterator iter;
	for (iter = events.begin(); iter != events.end(); ++iter) {
		display  << std::setw(3) << i << DOT << (*iter).displayEvent() << NEW_LINE;
		i++;
	}
	display << NEW_LINE;

	return display.str();
}
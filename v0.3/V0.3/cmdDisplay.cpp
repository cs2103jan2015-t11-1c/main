#include "cmdDisplay.h"
#include <sstream>
#include <assert.h>

const static std::string MESSAGE_EMPTY_ACTIVE_EVENTS = "Currently no active event. \n\n";
const static std::string MESSAGE_NO_EVENT_TODAY = "No Event today! \n\n";
const static int NUMBER_OF_TASK_TO_DISPLAY = 21;
const static std::string NEW_LINE = "\n";
const static std::string Dot = ".";

cmdDisplay::cmdDisplay(void){
}


cmdDisplay::~cmdDisplay(void){
}

//check if number of task is zero
bool cmdDisplay::isEmptyEventsStorage(Storage& _storage){
	bool isEmpty = false;
	Eventlist activeEvents = _storage.displayEvent();
	if(activeEvents.getTotalNumberOfEvents() == 0){
		isEmpty = true;
	}

	return isEmpty;
}
//display active tasks, tasks done or tasks due/start today
std::string cmdDisplay::executecmdDisplay(Storage& _storage){
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
	default:
		assert(false);
		break;
	} 	
	return "";
}

//display active events
std::string cmdDisplay::cmdDisplayActive(Storage& _storage){
	Eventlist activeEvents = _storage.displayEvent();
	std::list<Event> currentList = activeEvents.returnAllEvent();

	std::string feedback;
	feedback = eventsToDisplay(currentList);
	return feedback;
}

//display completed events
std::string cmdDisplay::cmdDisplayDone(Storage& _storage){
	Eventlist doneEvents = _storage.displayDoneEvent();
	std::list<Event> currentList = doneEvents.returnAllEvent();

	std::string feedback;
	feedback = eventsToDisplay(currentList);
	return feedback;
}

//display events today
std::string cmdDisplay::cmdDisplayToday(Storage& _storage){
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

bool cmdDisplay::isEventToday(int taskStartMonth, int taskStartDay, int taskEndMonth, int taskEndDay){
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

//set the number of tasks to be displayed to be 20
std::string cmdDisplay::eventsToDisplay(std::list<Event> events){
	std::ostringstream display;
	int i = 1;
	std::list<Event>::iterator iter;
	for (iter = events.begin(); iter != events.end() && i < NUMBER_OF_TASK_TO_DISPLAY; ++iter) {
		display  << std::setw(3) << i << Dot << (*iter).displayEvent() << NEW_LINE;
		i++;
	}
	display << NEW_LINE;

	return display.str();
}
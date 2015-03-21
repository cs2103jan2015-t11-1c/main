#include "cmdMarkAsDone.h"


cmdMarkAsDone::cmdMarkAsDone(void)
{
}


cmdMarkAsDone::~cmdMarkAsDone(void)
{
}

string cmdMarkAsDone::exercuteMarkAsDone(){
	Eventlist activeEvents = _storage.displayEvent();
	int number = stoi(_toDoList);
	Event eventDone = _storage.getEvent(number);
	_storage.markEventAsDone(number);
	_feedback = "\"" + eventDone.readEvent() + "\" is marked as done.\n";
	return _feedback;
}
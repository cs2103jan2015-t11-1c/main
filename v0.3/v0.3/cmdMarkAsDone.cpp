#include "cmdMarkAsDone.h"


cmdMarkAsDone::cmdMarkAsDone(void)
{
}


cmdMarkAsDone::~cmdMarkAsDone(void)
{
}

std::string cmdMarkAsDone::exercuteMarkAsDone(){
	Eventlist activeEvents = _storage.displayEvent();
	//t number = std::stoi(_taskName);
	//ent eventDone = _storage.getEvent(number);
	_storage.markEventAsDone(_taskNumberList);
	_feedback = "is marked as done.\n";
	return _feedback;
}
#include "cmdUpdate.h"


cmdUpdate::cmdUpdate(void){
}


cmdUpdate::~cmdUpdate(void){
}

std::string cmdUpdate::executecmdUpdate(Storage& _storage){
	int eventNumber;
	eventNumber= _taskNumberList.front();
	std::cerr<< eventNumber;
	Event eventToUpdate; 
	eventToUpdate= _storage.getEvent(eventNumber);
	std::cout << eventToUpdate.readEvent();
	switch(_commandWord){
	case UPDATENAME:
		return updateName(eventToUpdate, eventNumber, _storage);
	case UPDATESTARTINGTIME:
		return updateStartingTime(eventToUpdate, eventNumber, _storage);
	case UPDATEENDINGTIME:
		return updateEndingTime(eventToUpdate, eventNumber, _storage);
	default:
		break;
	}
	return "no";
}
/*	Event newEvent;
	cout << buffer << endl;
	newEvent= getEventInformation(buffer);
	_storage.updateEvent(eventNumber, newEvent);
	_feedback = "\"" + Tempt + "\" is updated to " + "\"" + newEvent.readEvent() +"\" \n";
	}
	return _feedback;*/

std::string cmdUpdate::updateName(Event eventToUpdate, int eventNumber, Storage& _storage){
	std::string Tempt = eventToUpdate.readEvent();
	eventToUpdate.changeTitle(_taskName);
	_storage.updateEvent(eventNumber, eventToUpdate);
	_feedback = printFeedback(Tempt, eventToUpdate);
	return _feedback;
}

std::string cmdUpdate::updateEndingTime(Event eventToUpdate, int eventNumber, Storage& _storage){
	std::string Tempt = eventToUpdate.readEvent();
	eventToUpdate.changeEndDay(_endingDate);
	eventToUpdate.changeEndMonth(_endingMonth);
	eventToUpdate.changeEndTime(_endingTime);
	_storage.updateEvent(eventNumber, eventToUpdate);
	_feedback = printFeedback(Tempt, eventToUpdate);
	return _feedback; 
}

std::string cmdUpdate::updateStartingTime(Event eventToUpdate, int eventNumber, Storage& _storage){
	std::string Tempt = eventToUpdate.readEvent();
	eventToUpdate.changeStartDay(_startingDate);
	eventToUpdate.changeStartMonth(_startingMonth);
	eventToUpdate.changeStartTime(_startingTime);
	_storage.updateEvent(eventNumber, eventToUpdate);
	_feedback = printFeedback(Tempt, eventToUpdate);
	return _feedback;
}

std::string cmdUpdate::printFeedback(std::string Tempt, Event eventToUpdate){
	std::string feedback = "\"" + Tempt + "\" is updated to " + "\"" + eventToUpdate.readEvent() +"\" \n";
	return feedback;
}
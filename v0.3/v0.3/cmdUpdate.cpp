#include "cmdUpdate.h"


cmdUpdate::cmdUpdate(void){
}


cmdUpdate::~cmdUpdate(void){
}

string cmdUpdate::executecmdUpdate(){
	int eventNumber;
	eventNumber= _taskNumberList.front();
	Event eventToUpdate; 
	eventToUpdate= _storage.getEvent(eventNumber);
 	
	switch(_commandWord){
	case UPDATENAME:
		return updateName(eventToUpdate, eventNumber);
	case UPDATESTARTINGTIME:
		return updateStartingTime(eventToUpdate, eventNumber);
	case UPDATEENDINGTIME:
		return updateEndingTime(eventToUpdate, eventNumber);
	default:
		break;
	}	
}
/*	Event newEvent;
	cout << buffer << endl;
	newEvent= getEventInformation(buffer);
	_storage.updateEvent(eventNumber, newEvent);
	_feedback = "\"" + Tempt + "\" is updated to " + "\"" + newEvent.readEvent() +"\" \n";
	}
	return _feedback;*/

string cmdUpdate::updateName(Event eventToUpdate, int eventNumber){
	string Tempt = eventToUpdate.readEvent();
	eventToUpdate.changeTitle(_taskName);
	_storage.updateEvent(eventNumber, eventToUpdate);
	_feedback = printFeedback(Tempt, eventToUpdate);
}

string cmdUpdate::updateEndingTime(Event eventToUpdate, int eventNumber){
	string Tempt = eventToUpdate.readEvent();
	eventToUpdate.changeEndDay(_endingDate);
	eventToUpdate.changeEndMonth(_endingMonth);
	eventToUpdate.changeEndTime(_endingTime);
	_storage.updateEvent(eventNumber, eventToUpdate);
	_feedback = printFeedback(Tempt, eventToUpdate);
}

string cmdUpdate::updateStartingTime(Event eventToUpdate, int eventNumber){
	string Tempt = eventToUpdate.readEvent();
	eventToUpdate.changeStartDay(_startingDate);
	eventToUpdate.changeStartMonth(_startingMonth);
	eventToUpdate.changeStartTime(_startingTime);
	_storage.updateEvent(eventNumber, eventToUpdate);
	_feedback = printFeedback(Tempt, eventToUpdate);
}

string cmdUpdate::printFeedback(string Tempt, Event eventToUpdate){
	string feedback = "\"" + Tempt + "\" is updated to " + "\"" + eventToUpdate.readEvent() +"\" \n";
	return feedback;
}
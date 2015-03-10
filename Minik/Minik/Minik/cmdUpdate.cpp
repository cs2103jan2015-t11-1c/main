#include "Event.h"
#include "Eventlist.h"
#include "cmdUpdate.h"
#include <iostream>
using namespace std;

void CmdUpdate::updateTitle(int taskNumber){
	string updateInfo;
	Event newEvent;
	event.changeTitle(string newTitle);
	
}

void CmdUpdate::updateDate(int taskNumber){
	string updateInfo;
	Event newEvent;
	event.changeDate(string newDate);
	
}

void CmdUpdate::updateTime(int taskNumber){
	string updateInfo;
	Event newEvent;
	event.changeTime(string newTime);
	
}

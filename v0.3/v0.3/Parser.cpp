#include "Parser.h"
#include <string>
#include <iostream>
using namespace std;

Parser::Parser(void)
{
	_taskName ="";
	_startingTime="";
	_endingTime="";
	_startingDate="";
	_endingDate="";
	_taskNumberList.clear();
}

Parser::~Parser(void)
{
}

//**************************************************************************
//Pass all the informations of the user input to logic to execute the command.
//**************************************************************************

string Parser::callToLogic(string command){
	string feedback=_logic.executeCommand( command , _taskName, _startingDate, _startingTime,_endingDate, _endingTime, _taskNumberList);
	//cout <<"command:"<<command <<endl <<"taskname:" <<_taskName <<endl <<"starttime:"<<_startingTime <<endl <<"startdate:"<<_startingDate<<endl <<"enddate:"<< _endingDate <<endl <<"endtime:" <<_endingTime <<endl;
	_taskName ="";
	_startingTime="";
	_endingTime="";
	_startingDate="";
	_endingDate="";
	_taskNumberList.clear();
	return "";
}

//*******************************************************************************************************
//Add function has 3 different subfunctions:1. addTimedEvent, addFloatingEvent and addEventWithDeadline.
//*******************************************************************************************************

string Parser::addEvent(string toDoList){
	if(isTimedTask(toDoList)){
		return addTimedEvent(toDoList);
	}
	else if (isTaskWithDeadline(toDoList)){
		return addEventWithDeadline(toDoList);
	}

	return addFloatingEvent(toDoList);

}

string Parser::addTimedEvent(string toDoList){
	string &buffer =toDoList;
	_taskName=getEventTitle(buffer);
	_startingDate = getEventDate(buffer);
	_startingTime = getEventTime(buffer);
	int ePosition = buffer.find_first_of(":") + 2;
	buffer = buffer.substr(ePosition);
	_endingDate = getEventDate(buffer);
	_endingTime = getEventTime(buffer);
	return callToLogic("addTimedEvent");
}

string Parser::addEventWithDeadline(string toDoList){
	string &buffer = toDoList;
	_taskName=getEventTitle(buffer);
	_endingDate = getEventDate(buffer);
	_endingTime = getEventTime(buffer);
	return callToLogic("addEventWithDeadline");
}

string Parser::addFloatingEvent(string toDoList){
	string& buffer = toDoList;
	_taskName=getEventTitle(buffer);
	return callToLogic("addFloatingEvent");
}

bool Parser::isTaskWithDeadline(string toDoList){
	bool isTaskWithDeadline = false;
	int TIndex = toDoList.find("by:");
	if(TIndex != string::npos){
		isTaskWithDeadline = true;
	}

	return isTaskWithDeadline;
}
bool Parser::isTimedTask(string toDoList){
	bool isTimedTask = false;
	int TIndex = toDoList.find("from:");
	if(TIndex != string::npos){
		isTimedTask = true;
	}
	return isTimedTask;
}

//*****************************************************************************************
//Seperate EventTitle,eventdate and event time
//*****************************************************************************************

string Parser::getEventTitle(string &buffer){
	int TIndex;

    string taskName;
	TIndex = buffer.find("from:");
	if(TIndex!=string::npos && TIndex >=0){
	taskName = buffer.substr(0, TIndex-1);
	buffer = buffer.substr(TIndex+6);
	return taskName;
	}

	TIndex=buffer.find("by:");
	if(TIndex!=string::npos&&TIndex >=0){
		taskName = buffer.substr(0, TIndex-1);
		buffer = buffer.substr(TIndex+4);
		return taskName;
	}

	return buffer;


}

string Parser::getEventDate(string &buffer){
	int TIndex;
	string date;
	string day;
	string month;

	TIndex = buffer.find_first_of(" ");
	day = buffer.substr(0, TIndex);
	buffer = buffer.substr(TIndex+1);

	TIndex = buffer.find_first_of(" ");
	month = buffer.substr(0, TIndex);
	buffer = buffer.substr(TIndex+1);

	date = day + " " + month;
	return date;
}

//assume no spaces within the time input
string Parser::getEventTime(string &buffer){
	int TIndex;
	string time;

	TIndex = buffer.find_first_of(" ");
	time = buffer.substr(0, TIndex);
	buffer = buffer.substr(TIndex+1);

	return time;
}


//****************************************************************************************************************
//Update event has 3 types: update task name, update ending time and date, and update starting time and date.
//****************************************************************************************************************

string Parser::updateEvent(string toDoList){
	string & buffer=toDoList;
	string command;
	int upDateEventNumber = getUpdateEventNumber(buffer);
	_taskNumberList.push_back(upDateEventNumber);
	int index = buffer.find_first_of(" ");
	string updateType = buffer.substr(0, index);
	buffer = buffer. substr(index +1 );

	if(updateType =="name"){
		_taskName=buffer;
		return callToLogic("updateName");
	}
	else if( updateType == "end"){
		_endingDate=getEventDate(buffer);
		_endingTime=getEventTime(buffer);
		return callToLogic("updateEndingTime");
	}
	else if (updateType == "start"){
		_startingDate=getEventDate(buffer);
		_startingTime = getEventTime(buffer);
		return callToLogic("updateStartingTime");
	}
		
}

int Parser :: getUpdateEventNumber(string &buffer){
	int index;
	string TString;
	index=buffer.find_first_of(" ");
	TString=buffer.substr(0, index);
	int eventNumber=stoi(TString);
	index = buffer.find_first_of(".");
	buffer=buffer.substr(index+1);
	return eventNumber;
}

//******************
//Search for a task
//******************

string Parser::searchEvent(string part){
	_taskName=part;
	return callToLogic("search");
}

//*************************
//undo the previous action
//*************************

string Parser::unDo(){
	return callToLogic("unDo");
}

//********************************************************************************************************************
//3 types of display based on command: display today's tasks, display completed tasks and display all the tasks
//********************************************************************************************************************

string Parser::displayEvent(string command){
return callToLogic(command);
}

string Parser::clearEvent(){
	return callToLogic("clear");
}


string Parser::markAsDone(string numberList){
	getNumberList(numberList);
	return callToLogic("markAsDone");
}

string Parser::deleteEvent(string numberList){
	getNumberList(numberList);
	return callToLogic("delete");
}

//**************************************************************************************
//get the list of task numbers input by the user, and store them as integers in a list
//**************************************************************************************
void Parser::getNumberList(string numberList){
	int TIndex= numberList.find_first_of(" ");
	string TString;
	int eventNumber;
	while(TIndex!=string::npos){
		TString=numberList.substr(0,TIndex);
		eventNumber = stoi(TString);
		_taskNumberList.push_back(eventNumber);
		numberList=numberList.substr(TIndex+1);
		TIndex=numberList.find_first_of(" ");
	}
}

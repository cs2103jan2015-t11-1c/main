#include "Parser.h"
#include <string>
#include <iostream>
using namespace std;

Parser::Parser(void)
{
	_taskName ="";
	_startingTime=""; 
	_endingTime="";
	_startingDate=0;//starting date is not assigned when _startingDate = 0
	_endingDate=0;//edinging date is not assigned when _endingDate = -1
	_startingMonth=MONTHNOTASSIGNED;
	_endingMonth = MONTHNOTASSIGNED;
	_taskNumberList.clear();
}

Parser::~Parser(void)
{
}

//**************************************************************************
//Pass all the informations of the user input to logic to execute the command.
//**************************************************************************

string Parser::callToLogic(CommandType command){
	string feedback=_logic.executeCommand( command , _taskName, _startingDate, _startingTime,_endingDate, _endingTime, _taskNumberList);
	
//	cout <<"command:"<<command <<endl <<"taskname:" <<_taskName <<endl <<"starttime:"<<_startingTime <<endl <<"startdate:"<<_startingDate<<endl<<"startingmonth:" <<_startingMonth <<endl <<"enddate:"<< _endingDate <<endl <<"endingMonth:"<<_endingMonth <<endl<<"endtime:" <<_endingTime <<endl;
	_taskName ="";
	_startingTime="";
	_endingTime="";
	_startingDate=0;
	_endingDate=0;
	_startingMonth=MONTHNOTASSIGNED;
	_endingMonth = MONTHNOTASSIGNED;
	_taskNumberList.clear();
	return feedback;
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
	int integer=-1;
	int &date= integer;
	MonthType notAssigned = MONTHNOTASSIGNED;
	MonthType &month= notAssigned;
	_taskName=getEventTitle(buffer);
	getEventDate(buffer,date, month);
	_startingDate = date; 
	_startingMonth = month; 
	_startingTime = getEventTime(buffer);
	int ePosition = buffer.find_first_of(":") + 2;
	buffer = buffer.substr(ePosition);
	getEventDate(buffer,date, month);
	_endingDate = date;
	_endingMonth = month;
	_endingTime = getEventTime(buffer);
	return callToLogic(ADDTIMEDEVENT);
}

string Parser::addEventWithDeadline(string toDoList){
	string &buffer =toDoList;
	_taskName=getEventTitle(buffer);
	int integer=-1;
	int &date= integer;
	MonthType notAssigned = MONTHNOTASSIGNED;
	MonthType &month= notAssigned;
	getEventDate(buffer,date, month);
	_endingDate = date;
	_endingMonth = month;
	_endingTime = getEventTime(buffer);
	return callToLogic(ADDEVENTWITHDEADLINE);
}

string Parser::addFloatingEvent(string toDoList){
	string& buffer = toDoList;
	_taskName=getEventTitle(buffer);
	return callToLogic(ADDFLOATINGEVENT);
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

void Parser::getEventDate(string &buffer,int &date,MonthType &month){
	int TIndex;
	string TDate;
	string TMonth;
	TIndex = buffer.find_first_of(" ");
	TDate = buffer.substr(0, TIndex);
	date = stoi(TDate);
	buffer = buffer.substr(TIndex+1);
	TIndex = buffer.find_first_of(" ");
	TMonth = buffer.substr(0, TIndex);
	month = determineMonthType(TMonth);
	buffer = buffer.substr(TIndex+1);
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

MonthType Parser :: determineMonthType( string TMonth){

	if(TMonth == "jan"){
		return JANUARY;
	}
	else if(TMonth == "feb"){
		return FEBRUARY;
	}
	else if(TMonth == "mar"){
		return MARCH;
	}
	else if(TMonth == "apr"){
		return APRIL;
	}
	else if( TMonth == "may"){
		return MAY;
	}
	else if (TMonth == "jun"){
		return JUNE;
	}
	else if (TMonth == "jul"){
		return JULY;
	}
	else if (TMonth == "aug"){
		return AUGUST;
	}
	else if (TMonth == "sep"){
		return SEPTEMBER;
	}
	else if (TMonth == "oct"){
		return OCTOBER;
	}
	else if (TMonth == "nov"){
		return NOVEMBER;
	}
	else if (TMonth == "dec"){
		return DECEMBER;
	}
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
		return callToLogic(UPDATENAME);
	}
	else if( updateType == "end"){
		int integer=-1;
		int &date= integer;
		MonthType notAssigned = MONTHNOTASSIGNED;
		MonthType &month= notAssigned;
		getEventDate(buffer,date, month);
		_endingDate = date;
		_endingMonth = month;
		_endingTime=getEventTime(buffer);
		return callToLogic(UPDATEENDINGTIME);
	}
	else if (updateType == "start"){
		int integer=-1;
		int &date= integer;
		MonthType notAssigned = MONTHNOTASSIGNED;
		MonthType &month= notAssigned;
		getEventDate(buffer,date, month);
		_startingDate=date;
		_startingMonth = month;
		_startingTime = getEventTime(buffer);
		return callToLogic(UPDATESTARTINGTIME);
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
	return callToLogic(SEARCH);
}

//*************************
//undo the previous action
//*************************

string Parser::unDo(){
	return callToLogic(UNDO);
}

//********************************************************************************************************************
//3 types of display based on command: display today's tasks, display completed tasks and display all the tasks
//********************************************************************************************************************

string Parser::displayEvent(string command){
	CommandType commandT;
	if(command == "displayDone"){
		commandT = DISPLAYDONE;
	}
	else if (command == "displayToday"){
		commandT = DISPLAYTODAY;
	}
	else if (command == "display"){
		commandT = DISPLAY;
	}
	
	return callToLogic(commandT);
}

string Parser::clearEvent(){
	return callToLogic(CLEAR);
}


string Parser::markAsDone(string numberList){
	getNumberList(numberList);
	return callToLogic(MARKASDONE);
}

string Parser::deleteEvent(string numberList){
	getNumberList(numberList);
	return callToLogic(DELETE);
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

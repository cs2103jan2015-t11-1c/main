#include "Parser.h"
#include <string>
#include <iostream>
using namespace std;

Parser::Parser(void)
{
	_taskName ="";
	_startingTime="2400"; 
	_endingTime="2400";
	_startingDate=0;//starting date is not assigned when _startingDate = 0
	_endingDate=0;//edinging date is not assigned when _endingDate = -1
	_startingMonth=MONTHNOTASSIGNED;
	_endingMonth = MONTHNOTASSIGNED;
	_taskNumberList.clear();
}

Parser::~Parser(void)
{
}

int Parser::convertMonthTypeToInteger(MonthType monthType){

	switch(monthType){
	case JANUARY:
		return 1;
		
		
	case FEBRUARY:
		return 2;
	case MARCH:
		return 3;
	case APRIL:
		return 4;
	case MAY:
		return 5;
	case JUNE:
		return 6;
	case JULY:
		return 7;
	case AUGUST:
		return 8;
	case SEPTEMBER:
		return 9;
	case OCTOBER:
		return 10;
	case NOVEMBER:
		return 11;
	case DECEMBER:
		return 12;
	case MONTHNOTASSIGNED:
		return 13;
	}
	return 13;
}

//**************************************************************************
//Pass all the informations of the user input to logic to execute the command.
//**************************************************************************
logic::CommandType Parser::changeToLogicCommandType(CommandType command){
	switch (command){
		
	case ADDEVENTWITHDEADLINE:
		return logic::ADDEVENTWITHDEADLINE;
	case ADDFLOATINGEVENT:
		return logic::ADDFLOATINGEVENT;
	case ADDTIMEDEVENT:
		return logic::ADDTIMEDEVENT;
	case UPDATENAME:
		return logic::UPDATEENDINGTIME;
	case UPDATEENDINGTIME:
		return logic::UPDATEENDINGTIME;
	case UPDATESTARTINGTIME:
		return logic::UPDATESTARTINGTIME;
	case DELETE:
		return logic::DELETE;
	case DISPLAY:
		return logic::DISPLAY;
	case DISPLAYTODAY:
		return logic::DISPLAYTODAY;
	case DISPLAYDONE:
		return logic::DISPLAYDONE;
	case SEARCH:
		return logic::SEARCH;
	case UNDO:
		return logic::UNDO;
	case MARKASDONE:
		return logic::MARKASDONE;
	case CLEAR:
		return logic::CLEAR;
	case HELP:
		return logic::HELP;
	}
	return logic::HELP;
}
string Parser::callToLogic(CommandType command){

	int startingMonth=convertMonthTypeToInteger(_startingMonth);
	int endingMonth = convertMonthTypeToInteger(_endingMonth);
	int integerStartingTime = stoi(_startingTime);
	int integerEndingTime = stoi(_endingTime);
	logic::CommandType _command;
	_command = changeToLogicCommandType(command);
	
	string feedback=_logic.executeCommand(_command , _taskName, _startingDate, startingMonth,  integerStartingTime,_endingDate, endingMonth, integerEndingTime, _taskNumberList);
	

	//Reset the value of all private attributes.
	_taskName ="";
	_startingTime="2400";
	_endingTime="2400";
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
	return MONTHNOTASSIGNED;
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
		return "no";
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

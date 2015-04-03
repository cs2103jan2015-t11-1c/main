#include "Parser.h"
#include <string>
#include <iostream>
using namespace std;

static const string EMPTYSTRING = "";
static const string TIMENOTASSIGNED = "2400";
static const string TASKNAMENOTASSIGNED = "";
static const int DATENOTEASSIGNED = 0;
static const int JAN = 1;
static const int FEB = 2;
static const int MAR = 3;
static const int APR = 4;
static const int INTEGERMAY = 5;
static const int JUN = 6;
static const int JUL = 7;
static const int AUG = 8;
static const int SEP = 9;
static const int OCT = 10;
static const int NOV = 11;
static const int DEC = 12;
static const int NOASSIGNEDMONTH = 13; 


//Pass all the informations of the user input to logic to execute the command.
string Parser::callToLogic(CommandType command){
	int startingMonth=convertMonthTypeToInteger(_startingMonth);
	int endingMonth = convertMonthTypeToInteger(_endingMonth);
	bool isTimeInteger = (isTimeAnInteger(_startingTime) && isTimeAnInteger(_endingTime));
	int integerStartingTime = 2400;
	int integerEndingTime = 2400;

	if(isTimeInteger){
		integerStartingTime = stoi(_startingTime);
		integerEndingTime = stoi(_endingTime);
	}
	else{
		return INVALID_TIMED_DATE_MONTH_MESSAGE;
	}
	
	logic::CommandType _command;
	_command = changeToLogicCommandType(command);
	string feedback = EMPTYSTRING;

	switch(command){

	case UPDATEENDINGTIME:

	case ADDEVENTWITHDEADLINE:
		if(_verificationDateTimeMonth.isDateMonthTimeValid(_endingDate, endingMonth, integerEndingTime)){ 
				feedback = _logic.executeCommand(_command , _taskName, _startingDate, startingMonth,  integerStartingTime,_endingDate, endingMonth, integerEndingTime, _taskNumberList);
				resetAttributesValue();
				return feedback;
		}
		else{
			return INVALID_TIMED_DATE_MONTH_MESSAGE;
		}

	case UPDATESTARTINGTIME:
		if(_verificationDateTimeMonth.isDateMonthTimeValid(_startingDate, startingMonth, integerStartingTime)){ 
				 feedback = _logic.executeCommand(_command , _taskName, _startingDate, startingMonth,  integerStartingTime,_endingDate, endingMonth, integerEndingTime, _taskNumberList);
				resetAttributesValue();
				return feedback;
		}
		else{
			return INVALID_TIMED_DATE_MONTH_MESSAGE;
		}

	case ADDTIMEDEVENT:
		if(_verificationDateTimeMonth.isEndingLaterThanStarting(integerStartingTime, startingMonth, _startingDate, integerEndingTime, endingMonth, _endingDate)){
			feedback = _logic.executeCommand(_command , _taskName, _startingDate, startingMonth,  integerStartingTime,_endingDate, endingMonth, integerEndingTime, _taskNumberList);
			resetAttributesValue();
			return feedback;
		}
		else{
			return INVALID_TIMED_DATE_MONTH_MESSAGE;
		}

	case DELETE:

	case UPDATENAME:

	case UNDO:

	case ADDFLOATINGEVENT:

	case SEARCH:

	case EXIT:

	case HELP:

	case CLEAR:

	case DISPLAY:

	case DISPLAYTODAY:

	case DISPLAYDONE:

	case MARKASDONE:
		feedback = _logic.executeCommand(_command , _taskName, _startingDate, startingMonth,  integerStartingTime,_endingDate, endingMonth, integerEndingTime, _taskNumberList);
		resetAttributesValue();
		return feedback;

	default:
		resetAttributesValue();
		return INVALID_INPUT;
	}
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
	else{
		return addFloatingEvent(toDoList);
	}
}

string Parser::addTimedEvent(string toDoList){
	string &buffer =toDoList;
	int integerdate=0;
	int &date = integerdate;
	MonthType notAssigned = MONTHNOTASSIGNED;
	MonthType &month= notAssigned;

	_taskName=getEventTitle(buffer);

	if (!isAbleToGetEventDate(buffer,date, month)){
		return INVALID_TIMED_DATE_MONTH_MESSAGE;
	}
	else{
		_startingDate = date; 
		_startingMonth = month; 
		_startingTime = getEventTime(buffer);
		int ePosition = buffer.find_first_of(":") + 2;
		buffer = buffer.substr(ePosition);
	}
	
	if( !isAbleToGetEventDate(buffer,date, month)){
		return INVALID_TIMED_DATE_MONTH_MESSAGE;
	}
	else{
		_endingDate = date;
		_endingMonth = month;
		_endingTime = getEventTime(buffer);
		return callToLogic(ADDTIMEDEVENT);
	}
}

string Parser::addEventWithDeadline(string toDoList){
	string &buffer =toDoList;
	_taskName=getEventTitle(buffer);
	int integer=-1;
	int &date= integer;
	MonthType notAssigned = MONTHNOTASSIGNED;
	MonthType &month= notAssigned;

	if(!isAbleToGetEventDate(buffer,date, month)){
		return INVALID_TIMED_DATE_MONTH_MESSAGE;
	}
	else{
		_endingDate = date;
		_endingMonth = month;
		_endingTime = getEventTime(buffer);
		return callToLogic(ADDEVENTWITHDEADLINE);
	}
}

string Parser::addFloatingEvent(string toDoList){
	string& buffer = toDoList;
	_taskName=getEventTitle(buffer);
	return callToLogic(ADDFLOATINGEVENT);
}

bool Parser::isTaskWithDeadline(string toDoList){
	bool isTaskWithDeadline = false;
	int TIndex = toDoList.find("by:");

	if(TIndex != string::npos && TIndex != -1){
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

bool Parser::isAbleToGetEventDate(string &buffer,int &date,MonthType &month){
	int TIndex;
	string TDate;
	string TMonth;
	TIndex = buffer.find_first_of(" ");
	TDate = buffer.substr(0, TIndex);

	for(int i = TDate.size()-1; i >= 0; i--){
		if(!isdigit(TDate[i])){
			return false;			
		}
	}

	date = stoi(TDate);
	buffer = buffer.substr(TIndex+1);
	TIndex = buffer.find_first_of(" ");
	TMonth = buffer.substr(0, TIndex);
	month = determineMonthType(TMonth);
	buffer = buffer.substr(TIndex+1);
	return true;
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

	TMonth = _verificationDateTimeMonth.lowercaseMonth(TMonth);

	if(TMonth == "jan" ||  TMonth == "january" || TMonth == "01" || TMonth == "1" ){
		return JANUARY;
	}
	else if(TMonth == "feb" || TMonth == "february"|| TMonth == "02" || TMonth == "2"){
		return FEBRUARY;
	}
	else if(TMonth == "mar" || TMonth == "march" || TMonth == "03" || TMonth == "3"){
		return MARCH;
	}
	else if(TMonth == "apr" || TMonth == "april" || TMonth == "04" || TMonth == "4"){
		return APRIL;
	}
	else if( TMonth == "may" ||  TMonth == "may" || TMonth == "05" || TMonth == "5"){
		return MAY;
	}
	else if (TMonth == "jun" || TMonth == "june"|| TMonth == "06" || TMonth == "6"){
		return JUNE;
	}
	else if (TMonth == "jul" || TMonth == "july" || TMonth =="07" || TMonth =="7" ){
		return JULY;
	}
	else if (TMonth == "aug" || TMonth == "august" || TMonth == "08" || TMonth == "8"){
		return AUGUST;
	}
	else if (TMonth == "sep" || TMonth == "september" || TMonth == "09" || TMonth == "9"){
		return SEPTEMBER;
	}
	else if (TMonth == "oct" ||  TMonth == "october" || TMonth =="10"){
		return OCTOBER;
	}
	else if (TMonth == "nov" || TMonth == "november" || TMonth == "11"){
		return NOVEMBER;
	}
	else if (TMonth == "dec" || TMonth == "december" || TMonth == "12"){
		return DECEMBER;
	}
	else{
		return MONTHNOTASSIGNED;
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

		if(!isAbleToGetEventDate(buffer,date, month)){
			return INVALID_TIMED_DATE_MONTH_MESSAGE;
		}
		else{
			_endingDate = date;
			_endingMonth = month;
			_endingTime=getEventTime(buffer);
			return callToLogic(UPDATEENDINGTIME);
		}

	}
	else if (updateType == "start"){
		int integer=-1;
		int &date= integer;
		MonthType notAssigned = MONTHNOTASSIGNED;
		MonthType &month= notAssigned;

		if(!isAbleToGetEventDate(buffer,date, month)){
			return INVALID_TIMED_DATE_MONTH_MESSAGE;
		}
		else{
			_startingDate=date;
			_startingMonth = month;
			_startingTime = getEventTime(buffer);
			return callToLogic(UPDATESTARTINGTIME);
		}

	}
	else{
		return INVALID_TIMED_DATE_MONTH_MESSAGE;
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
	CommandType commandT = DISPLAY;

	if(command == "displaydone"){
		commandT = DISPLAYDONE;
	}
	else if (command == "displaytoday"){
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

string Parser::printHelp(){
	return callToLogic(HELP);
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
	//cout<<numberList<<endl;

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
	if(numberList.size()!=0){		
		_taskNumberList.push_back(stoi(numberList));
	}
}

//All attributes are initialized with their respective NOTASSIGNED value. Assume 24:00 as time not assigned, "" as task not assigned, 0 as date not assigned.
Parser::Parser(void)
{
	_taskName = TASKNAMENOTASSIGNED;
	_startingTime = TIMENOTASSIGNED; 
	_endingTime = TIMENOTASSIGNED;
	_startingDate = DATENOTEASSIGNED;
	_endingDate = DATENOTEASSIGNED;
	_startingMonth = MONTHNOTASSIGNED;
	_endingMonth = MONTHNOTASSIGNED;
	_taskNumberList.clear();
}

Parser::~Parser(void)
{
}


//Convert month from enum monthType to integer months: january - 1 , ect.
int Parser::convertMonthTypeToInteger(MonthType monthType){

	switch(monthType){

	case JANUARY:
		return  JAN;

	case FEBRUARY:
		return FEB;

	case MARCH:
		return MAR;

	case APRIL:
		return APR;

	case MAY:
		return INTEGERMAY;

	case JUNE:
		return JUN;

	case JULY:
		return JUL;

	case AUGUST:
		return AUG;

	case SEPTEMBER:
		return SEP;

	case OCTOBER:
		return OCT;

	case NOVEMBER:
		return NOV;

	case DECEMBER:
		return DEC;

	case MONTHNOTASSIGNED:
		return NOASSIGNEDMONTH;

	default:
		return NOASSIGNEDMONTH;
	}
}

logic::CommandType Parser::changeToLogicCommandType(CommandType command){
	switch (command){
		
	case ADDEVENTWITHDEADLINE:
		return logic::ADDEVENTWITHDEADLINE;

	case ADDFLOATINGEVENT:
		return logic::ADDFLOATINGEVENT;

	case ADDTIMEDEVENT:
		return logic::ADDTIMEDEVENT;

	case UPDATENAME:
		return logic::UPDATENAME;

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

	default:
		return logic::HELP;
	}
}

//Reset the value of all private attributes.
void Parser :: resetAttributesValue(){
	_taskName = TASKNAMENOTASSIGNED;
	_startingTime = TIMENOTASSIGNED;
	_endingTime = TIMENOTASSIGNED;
	_startingDate = DATENOTEASSIGNED;
	_endingDate = DATENOTEASSIGNED;
	_startingMonth = MONTHNOTASSIGNED;
	_endingMonth = MONTHNOTASSIGNED;
	_taskNumberList.clear();
}

bool Parser::isTimeAnInteger(string time){
	for (int i = time.size()-1; i>=0; i--){
		if(!isdigit(time[i])){
			return false;
		}
	}
	return true;
}

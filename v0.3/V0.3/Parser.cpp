#include "Parser.h"
#include <string>

static const std::string EMPTYSTRING = "";
static const std::string TIMENOTASSIGNED = "2400";
static const std::string TASKNAMENOTASSIGNED = "";
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

const static std::string STRING_ADD = "add";
const static std::string STRING_DELETE = "delete";
const static std::string STRING_UPDATE ="update" ;
const static std::string STRING_UNDO = "undo";
const static std::string STRING_DONE = "done";
const static std::string STRING_DISPLAY = "display";
const static std::string STRING_HELP = "help";
const static std::string STRING_EXIT = "exit";
const static std::string STRING_CLEAR = "clear";
const static std::string STRING_DISPLAYDONE = "displaydone";
const static std::string STRING_DISPLAYTODAY = "displaytoday";
const static std::string STRING_SEARCH = "search";
const static std::string STRING_CHANGEDIRECTORY = "changedirectory";
const static std::string STRING_REPEAT = "repeat";
const static std::string STRING_REPEATDONE = "repeatdone";

std::string Parser::repeat(string toDoList, string command){
	CommandType commandT;
	string TString;

	if(command == STRING_REPEAT){
		commandT = REPEAT;
	}
	else if (command == STRING_REPEATDONE){
		commandT = REPEATDONE;
	}
	
	int TIndex = firstIndextThatIsASpace(toDoList);
	
	if(isValidIndex(TIndex)){
		TString = toDoList.substr(0, TIndex);
		
	}
	else{
		return INVALID_INPUT;
	}
	
	if(isStringAnInteger(TString)){
		_taskNumberList.push_back(changeFromStringToInteger(TString));
	}
	else{
		return INVALID_INPUT;
	}
	
	toDoList = toDoList.substr(TIndex + 1);

	if(!isEmpty(toDoList)){
		_taskName = toDoList;
		cout << _taskName;
		return finalVerificationAndCallToLogic(commandT);
	}
	else{
		return INVALID_INPUT;
	}

}
		
std::string Parser::changeDirectory(std::string directory){
	_taskName = directory;
	return finalVerificationAndCallToLogic(CHANGEDIRECTORY);
}

std::string Parser::getEventTitle(std::string &buffer){
	int TIndex;

    std::string taskName;
	TIndex = buffer.find("from:");

	if(isValidIndex(TIndex)){
		taskName = buffer.substr(0, TIndex - 1);
		buffer = buffer.substr(TIndex + 4);
		return taskName;
	}
	else{
		TIndex=buffer.find("by:");
	}

	if(isValidIndex(TIndex)){
		taskName = buffer.substr(0, TIndex - 1);
		buffer = buffer.substr(TIndex + 2);
		buffer = buffer.substr(firstIndexThatIsNotASpace(buffer));
		return taskName;
	}
	
	return buffer;

}

string Parser::addTimedEvent(string toDoList){
	std:: string buffer =toDoList;
	int date = 0;
	MonthType month = MONTHNOTASSIGNED;

	_taskName=getEventTitle(buffer);

	if(buffer.size()==1){
		return INVALID_TIMED_DATE_MONTH_MESSAGE;
	}
	else{
		buffer = buffer.substr(1);
		
		if(isEmpty(buffer)){
			return INVALID_TIMED_DATE_MONTH_MESSAGE;
		}
		else{
			buffer=buffer.substr(firstIndexThatIsNotASpace(buffer));
		}
	}

	if(!isAbleToGetEventDateAndMonth(buffer,date, month)){
		return INVALID_TIMED_DATE_MONTH_MESSAGE;
	}
	else{
		_startingDate = date; 
		_startingMonth = month; 
		_startingTime = getEventTime(buffer);
		int Index = buffer.find_first_of("to:");

		if(isValidIndex(Index)){
			buffer =buffer.substr(Index + 2);
			if(buffer.size()== 1){
				return INVALID_INPUT;
			}
			else{
				buffer = buffer.substr(1);
			}
		}
		else{
			return INVALID_INPUT;
		}
	}

	if(buffer.size()==1){
		return INVALID_TIMED_DATE_MONTH_MESSAGE;
	}
	else{
		buffer = buffer.substr(1);
		
		if(isEmpty(buffer)){
			return INVALID_TIMED_DATE_MONTH_MESSAGE;
		}
		else{
			buffer=buffer.substr(firstIndexThatIsNotASpace(buffer));
		}
	}

	if(!isAbleToGetEventDateAndMonth(buffer,date, month)){
		return INVALID_TIMED_DATE_MONTH_MESSAGE;
	}
	else{
		_endingDate = date;
		_endingMonth = month;
		_endingTime = getEventTime(buffer);
		return finalVerificationAndCallToLogic(ADDTIMEDEVENT);
	}
}

std::string Parser::addEventWithDeadline(std::string toDoList){
	std::string buffer =toDoList;
	_taskName=getEventTitle(buffer);
	int date= 0;
	MonthType month= MONTHNOTASSIGNED;

	if(buffer.size()==1){
		return INVALID_TIMED_DATE_MONTH_MESSAGE;
	}
	else{
		buffer = buffer.substr(1);
		if(isEmpty(buffer)){
			return INVALID_TIMED_DATE_MONTH_MESSAGE;
		}
		else{
			buffer=buffer.substr(firstIndexThatIsNotASpace(buffer));
		}
	}

	if(!isAbleToGetEventDateAndMonth(buffer,date, month)){
		return INVALID_TIMED_DATE_MONTH_MESSAGE;
	}
	else{
		_endingDate = date;
		_endingMonth = month;
		_endingTime = getEventTime(buffer);
		return finalVerificationAndCallToLogic(ADDEVENTWITHDEADLINE);
	}
}
std::string Parser::getEventTime(std::string &buffer){
	std::string time;
	int TIndex = firstIndexThatIsNotASpace(buffer);

	buffer=buffer.substr(TIndex);
	TIndex = firstIndextThatIsASpace(buffer);
	if(isValidIndex(TIndex)){
		time = buffer.substr(0, TIndex);
		buffer = buffer.substr(TIndex);
	}
	else if(!isEmpty(buffer)){
		time = buffer;
	}
	return time;
}

std::string Parser::addFloatingEvent(std::string toDoList){
	std::string buffer = toDoList;
	_taskName=getEventTitle(buffer);
	return finalVerificationAndCallToLogic(ADDFLOATINGEVENT);
}

bool Parser::isTaskWithDeadline(std::string toDoList){
	bool isTaskWithDeadline = false;
	int TIndex = toDoList.find("by:");

	if(TIndex != string::npos){
		isTaskWithDeadline = true;
	}

	return isTaskWithDeadline;
}
bool Parser::isTimedTask(std::string toDoList){
	bool isTimedTask = false;
	int TIndex = toDoList.find("from:");

	if(TIndex != std::string::npos){
		isTimedTask = true;
	}

	return isTimedTask;
}

bool Parser::isValidIndex(int TIndex){
	if(TIndex!=std::string::npos && TIndex >=0){
		return true;
	}
	else{
		return false;
	}
}




bool Parser::isAbleToGetEventDateAndMonth(string &buffer,int &date,MonthType &month){
	std::string TDate;
	std::string TMonth;
	int TIndex = firstIndextThatIsASpace(buffer);
	if(isValidIndex(TIndex)){
		TDate = buffer.substr(0, TIndex);
	}
	else{
		return false;
	}
	
	if(!isStringAnInteger(TDate)){
			return false;			
		}
	else{
		date = changeFromStringToInteger(TDate);
	}

	buffer = buffer.substr(TIndex+1);

	TIndex = firstIndexThatIsNotASpace(buffer);
	int EIndex;
	if(isValidIndex(TIndex)){
		buffer = buffer.substr(TIndex);
		 EIndex = firstIndextThatIsASpace(buffer);
		if(isValidIndex(EIndex)){
			TMonth = buffer.substr(0, EIndex);
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}

	month = determineMonthType(TMonth);
	
	buffer = buffer.substr(EIndex);
	TIndex = firstIndexThatIsNotASpace(buffer);

	if(isValidIndex(TIndex)){
		buffer = buffer.substr(TIndex);
	}
	else{
		return false;
	}
	return true;

}

//assume no spaces within the time input

MonthType Parser :: determineMonthType(std::string TMonth){

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

std::string Parser::updateEvent(std::string toDoList){
	std::string buffer=toDoList;
	std::string command;
	int upDateEventNumber = getUpdateEventNumber(buffer);
	_taskNumberList.push_back(upDateEventNumber);
	buffer = buffer.substr(firstIndexThatIsNotASpace(buffer));
	int index = firstIndextThatIsASpace(buffer);
	std::string updateType = buffer.substr(0, index);
	buffer = buffer. substr(index + 1 );

	if(updateType =="name"){
		_taskName=buffer;
		return finalVerificationAndCallToLogic(UPDATENAME);
	}
	else if( updateType == "clear"){
		buffer = buffer.substr(firstIndexThatIsNotASpace(buffer));
		std::string clearType = buffer.substr(0,firstIndextThatIsASpace(buffer));
		if(clearType == "end"){
			return finalVerificationAndCallToLogic(CLEAREND);
		}
		else if(clearType == "start"){
			return finalVerificationAndCallToLogic(CLEARSTART);
		}
		else{
			return INVALID_INPUT;
		}
	}
	else if( updateType == "end"){
		int date= 0;
		MonthType month= MONTHNOTASSIGNED;

		if(!isAbleToGetEventDateAndMonth(buffer,date, month)){
			return INVALID_TIMED_DATE_MONTH_MESSAGE;
		}
		else{
			_endingDate = date;
			_endingMonth = month;
			_endingTime=getEventTime(buffer);
			return finalVerificationAndCallToLogic(UPDATEENDINGTIME);
		}

	}
	else if (updateType == "start"){
		int date= 0;
		MonthType month= MONTHNOTASSIGNED;

		if(!isAbleToGetEventDateAndMonth(buffer,date, month)){
			return INVALID_TIMED_DATE_MONTH_MESSAGE;
		}
		else{
			_startingDate=date;
			_startingMonth = month;
			_startingTime = getEventTime(buffer);
			return finalVerificationAndCallToLogic(UPDATESTARTINGTIME);
		}

	}
	
	else{
		return INVALID_TIMED_DATE_MONTH_MESSAGE;
	}
}

int Parser :: getUpdateEventNumber(std::string &buffer){
	int index;
	std::string TString;
	buffer = buffer.substr(firstIndexThatIsNotASpace(buffer));
	TString=buffer.substr(0, firstIndextThatIsASpace(buffer));

	//check whether its a number 
	int eventNumber=changeFromStringToInteger(TString);
	index = buffer.find_first_of(".");
	buffer=buffer.substr(index+1);
	return eventNumber;
}




bool Parser::getNumberList(std::string numberList){
	numberList = numberList.substr(firstIndexThatIsNotASpace(numberList));
	int TIndex= firstIndextThatIsASpace(numberList);
	std::string TString;
	int eventNumber;

	while(TIndex!=string::npos){
		TString=numberList.substr(0,TIndex);
		if(!isStringAnInteger(TString)){
			return false;
		}
		else{
			eventNumber = changeFromStringToInteger(TString);
			_taskNumberList.push_back(eventNumber);
			numberList=numberList.substr(TIndex+1);
			numberList = numberList.substr(firstIndexThatIsNotASpace(numberList));
			TIndex=firstIndextThatIsASpace(numberList);
		}
	}

	if(numberList.size()!=0){		
		if(!isStringAnInteger(numberList)){
			return false;
		}
		else{
			_taskNumberList.push_back(changeFromStringToInteger(numberList));
		}
	}
	return true;
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
		
	case CHANGEDIRECTORY:
		return logic::CHANGEDIRECTORY;

	case CLEAREND:
		return logic::CLEAREND;

	case CLEARSTART:
		return logic::CLEARSTART;

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
		
	case REPEAT:
		return logic::REPEAT;
		
	case REPEATDONE:
		return logic::REPEATDONE;

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

bool Parser::isStringAnInteger(string str){
	for (int i = str.size()-1; i>=0; i--){
		if(!isdigit(str[i])){
			return false;
		}
	}
	return true;
}

int Parser::changeFromStringToInteger(std::string str){
	return stoi(str);
}


//Pass all the informations of the user input to logic to execute the command.
string Parser::finalVerificationAndCallToLogic(CommandType command){

	int integerStartingMonth=convertMonthTypeToInteger(_startingMonth);
	int integerEndingMonth = convertMonthTypeToInteger(_endingMonth);
	bool isTimeInteger = (isStringAnInteger(_startingTime) && isStringAnInteger(_endingTime));
	int integerStartingTime;
	int integerEndingTime;

	if(isTimeInteger){
		integerStartingTime = changeFromStringToInteger(_startingTime);
		integerEndingTime = changeFromStringToInteger(_endingTime);
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
		if(_verificationDateTimeMonth.isDateMonthTimeValid(_endingDate, integerEndingMonth, integerEndingTime)){ 
				feedback = _logic.executeCommand(_command , _taskName, _startingDate, integerStartingMonth,  integerStartingTime,_endingDate, integerEndingMonth, integerEndingTime, _taskNumberList);
				resetAttributesValue();
				return feedback;
		}
		else{
			return INVALID_TIMED_DATE_MONTH_MESSAGE;
		}

	case UPDATESTARTINGTIME:
		if(_verificationDateTimeMonth.isDateMonthTimeValid(_startingDate, integerStartingMonth, integerStartingTime)){ 
				 feedback = _logic.executeCommand(_command , _taskName, _startingDate, integerStartingMonth,  integerStartingTime,_endingDate, integerEndingMonth, integerEndingTime, _taskNumberList);
				resetAttributesValue();
				return feedback;
		}
		else{
			return INVALID_TIMED_DATE_MONTH_MESSAGE;
		}

	case ADDTIMEDEVENT:
		if(_verificationDateTimeMonth.isEndingLaterThanStarting(integerStartingTime, integerStartingMonth, _startingDate, integerEndingTime, integerEndingMonth, _endingDate)){
			feedback = _logic.executeCommand(_command , _taskName, _startingDate, integerStartingMonth,  integerStartingTime,_endingDate, integerEndingMonth, integerEndingTime, _taskNumberList);
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
		
	case CLEAREND:
		
	case CHANGEDIRECTORY:

	case CLEARSTART:

	case DISPLAY:

	case DISPLAYTODAY:
		
	case DISPLAYDONE:
		
	case REPEAT:
		
	case REPEATDONE:

	case MARKASDONE:
		feedback = _logic.executeCommand(_command , _taskName, _startingDate, integerStartingMonth,  integerStartingTime,_endingDate, integerEndingMonth, integerEndingTime, _taskNumberList);
		resetAttributesValue();
		return feedback;

	default:
		resetAttributesValue();
		return INVALID_INPUT;
	}
}

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

bool Parser::isEmpty(string str){
	if(str.empty()){
		return true;
	}
	else{
		for(int i = str.size()-1; i >=0; i--){
			if(str[i] !=' '){
				return false;
			}
		}
	}
	return true;
}

int Parser::firstIndexThatIsNotASpace(std::string str){
	return str.find_first_not_of(" ");
}

int Parser::firstIndextThatIsASpace(std::string str){
	return str.find_first_of(" ");
}


std::string Parser::clearEvent(){
	return finalVerificationAndCallToLogic(CLEAR);
}


std::string Parser::markAsDone(std::string numberList){
	if(!getNumberList(numberList)){
		return INVALID_INPUT;
	}
	else{
		return finalVerificationAndCallToLogic(MARKASDONE);
	}
}

std::string Parser::deleteEvent(std::string numberList){
	if(!getNumberList(numberList)){
		return INVALID_INPUT;
	}
	else{
		return finalVerificationAndCallToLogic(DELETE);
	}
}

std::string Parser::searchEvent(std::string part){
	_taskName=part;
	return finalVerificationAndCallToLogic(SEARCH);
}

std::string Parser::unDo(){
	return finalVerificationAndCallToLogic(UNDO);
}

std::string Parser::help(){
	return finalVerificationAndCallToLogic(HELP);
}


std::string Parser::displayEvent(std::string command){
	CommandType commandT;

	if(command == "displaydone"){
		commandT = DISPLAYDONE;
	}
	else if (command == "displaytoday"){
		commandT = DISPLAYTODAY;
	}
	else if (command == "display"){
		commandT = DISPLAY;
	}
	
	return finalVerificationAndCallToLogic(commandT);
}

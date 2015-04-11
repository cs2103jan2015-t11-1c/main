//@author A0115253R

#include "Parser.h"
#include <string>
#include <assert.h>

static const int MONTH_NOT_ASSIGNED = 13; 
static const int INVALID_EVENT_NUMBER = 0;
static const int DATE_NOT_ASSIGNED = 0;
static const int JAN = 1;
static const int FEB = 2;
static const int MAR = 3;
static const int APR = 4;
static const int INTEGER_MAY = 5;
static const int JUN = 6;
static const int JUL = 7;
static const int AUG = 8;
static const int SEP = 9;
static const int OCT = 10;
static const int NOV = 11;
static const int DEC = 12;
const static std::string INVALID_INPUT_MESSAGE = "Invalid user input.\n\n";
const static std::string INVALID_TIME_DATE_MONTH_MESSAGE ="Please check your user input time, date and month.\n\n";
static const std::string EMPTY_STRING = "";
static const std::string TIME_NOT_ASSIGNED = "2400";
static const std::string TASK_NAME_NOT_ASSIGNED = "";
const static std::string STRING_END = "end";
const static std::string STRING_START = "start";
const static std::string STRING_NAME = "name";
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
const static std::string STRING_DISPLAYTOMORROW = "displaytomorrow";
const static std::string STRING_DISPLAYALL = "displayall";
const static std::string STRING_SEARCH = "search";
const static std::string STRING_CHANGEDIRECTORY = "changedirectory";
const static std::string STRING_REPEAT = "repeat";
const static std::string STRING_REPEATDONE = "repeatdone";
const static std::string STRING_DELETERECUR = "deleterecur";
const static std::string STRING_UPDATERECUR = "updaterecur";

//All attributes are initialized with their respective NOTASSIGNED value. Assume 24:00 as time not assigned, "" as task not assigned, 0 as date not assigned.
Parser::Parser(void){
	_taskName = TASK_NAME_NOT_ASSIGNED;
	_startingTime = TIME_NOT_ASSIGNED; 
	_endingTime = TIME_NOT_ASSIGNED;
	_startingDate = DATE_NOT_ASSIGNED;
	_endingDate = DATE_NOT_ASSIGNED;
	_startingMonth = MONTHNOTASSIGNED;
	_endingMonth = MONTHNOTASSIGNED;
	_taskNumberList.clear();
}

Parser::~Parser(void){
}

std::string Parser::clearEvent() {
	return VerifyAllAttributesAndCallLogic(CLEAR);
}


std::string Parser::markAsDone(std::string numberList) {
	if (isAbleToGetNumberList(numberList)) {
		return VerifyAllAttributesAndCallLogic(MARKASDONE);
	} else {
		return INVALID_INPUT_MESSAGE;
	}
}

std::string Parser::deleteEvent(std::string command, ::string numberList) {
	if (isAbleToGetNumberList(numberList)) {
		if (command == STRING_DELETE) {
			return VerifyAllAttributesAndCallLogic(DELETE);
		} else if (command == STRING_DELETERECUR) {
			return VerifyAllAttributesAndCallLogic(DELETERECUR);
		}
	} else {
		return INVALID_INPUT_MESSAGE;
	}
}

std::string Parser::searchEvent(std::string partToSearch) {
	_taskName = partToSearch;
	return VerifyAllAttributesAndCallLogic(SEARCH);
}

std::string Parser::unDo() {
	return VerifyAllAttributesAndCallLogic(UNDO);
}

std::string Parser::help() {
	return VerifyAllAttributesAndCallLogic(HELP);
}

std::string Parser::displayEvent(std::string command) {
	CommandType commandT;

	if (command == STRING_DISPLAYDONE) {
		commandT = DISPLAYDONE;
	} else if (command == STRING_DISPLAYTODAY) {
		commandT = DISPLAYTODAY;
	} else if (command == STRING_DISPLAY) {
		commandT = DISPLAY;
	} else if (command == STRING_DISPLAYALL) {
		commandT = DISPLAYALL;
	} else if (command == STRING_DISPLAYTOMORROW) {
		commandT = DISPLAYTOMORROW;
	}
	
	return VerifyAllAttributesAndCallLogic(commandT);
}

std::string Parser::repeat(std::string toDoList, std::string command) {
	CommandType CommandTypeCommand;
	std::string strTaskNumber;
	int integerTaskNumber;

	if (command == STRING_REPEAT) {
		CommandTypeCommand = REPEAT;
	} else if (command == STRING_REPEATDONE) {
		CommandTypeCommand = REPEATDONE;
	} else {
		return INVALID_INPUT_MESSAGE;
	}
	
	int TIndex = getIndexOfFirstWhiteSpace(toDoList);
	
	if (isValidIndex(TIndex)) {
		strTaskNumber = toDoList.substr(0, TIndex);		
	} else {
		return INVALID_INPUT_MESSAGE;
	}
	
	if (isStringAnInteger(strTaskNumber)) {
		integerTaskNumber = convertStringToInteger(strTaskNumber);
		_taskNumberList.push_back(integerTaskNumber);
	} else {
		return INVALID_INPUT_MESSAGE;
	}
	
	toDoList = toDoList.substr(TIndex + 1);

	if (!isEmpty(toDoList)) {
		int IndexTwo = getIndexOfFirstNonWhiteSpace(toDoList);
		replaceStringWithItsSubstring(toDoList, IndexTwo);
		_taskName = toDoList;
		return VerifyAllAttributesAndCallLogic(CommandTypeCommand);
	} else {
		return INVALID_INPUT_MESSAGE;
	}

	return INVALID_INPUT_MESSAGE;
}
		
std::string Parser::changeDirectory(std::string directory) {
	_taskName = directory;
	return VerifyAllAttributesAndCallLogic(CHANGEDIRECTORY);
}

std::string Parser::addEvent(std::string toDoList){
	
	if (isTimedTask(toDoList)) {
		return addTimedEvent(toDoList);
	} else if (isTaskWithDeadline(toDoList)) {
		return addEventWithDeadline(toDoList);
	} else {
		return addFloatingEvent(toDoList);
	}

}

std::string Parser::updateName(std::string command) {
	if (command == STRING_UPDATE) {
		return VerifyAllAttributesAndCallLogic(UPDATENAME);
	} else if (command == STRING_UPDATERECUR ) {
		return  VerifyAllAttributesAndCallLogic(UPDATERECURNAME);
	}
}

//This method is to update the starting/ending time to none, i.e. clear the starting/ ending time of existing event.
std::string Parser:: updateClear(std::string clearType, std::string command) {
	try {
		if (clearType == STRING_END && command == STRING_UPDATE) {
				return VerifyAllAttributesAndCallLogic(CLEAREND);
			} else if (clearType == STRING_END && command == STRING_UPDATERECUR) {
				return VerifyAllAttributesAndCallLogic(CLEARRECUREND);
			} else if (clearType == STRING_START && command == STRING_UPDATE) {
				return VerifyAllAttributesAndCallLogic(CLEARSTART);
			} else if (clearType == STRING_START && command == STRING_UPDATERECUR) {
				return VerifyAllAttributesAndCallLogic(CLEARRECURSTART);
			} else {
				throw INVALID_INPUT_MESSAGE;
			}
		} catch (std::string &exceptionMesssage) {
				return exceptionMesssage;
	}
}

//This method is to get details for updating end time of an existing event.
std::string Parser::updateEndingTime(std::string buffer, std::string command) {
		int date = 0;
		MonthType month = MONTHNOTASSIGNED;

		if (!isAbleToGetEventDateAndMonth(buffer,date, month)) {
			return  INVALID_TIME_DATE_MONTH_MESSAGE;
		} else {
			_endingDate = date;
			_endingMonth = month;
			_endingTime = getEventTime(buffer);

			if (command == STRING_UPDATE) {
				return VerifyAllAttributesAndCallLogic(UPDATEENDINGTIME);
			} else if (command == STRING_UPDATERECUR) {
				return VerifyAllAttributesAndCallLogic(UPDATERECURENDINGTIME);
			}

		}
}

//This method is get details for update the starting time of an existing event.
std::string Parser::updateStart(std::string buffer, std::string command) {
	int date= 0;
	MonthType month= MONTHNOTASSIGNED;

	if (!isAbleToGetEventDateAndMonth(buffer,date, month)) {
		return  INVALID_TIME_DATE_MONTH_MESSAGE;
	} else {
		_startingDate=date;
		_startingMonth = month;
		_startingTime = getEventTime(buffer);
		if (command == STRING_UPDATE) {
			return VerifyAllAttributesAndCallLogic(UPDATESTARTINGTIME);
		} else if (command == STRING_UPDATERECUR) {
			return VerifyAllAttributesAndCallLogic(UPDATESTARTINGTIME);
		}
	}
}

//This method is to gathers all update cases and call the respective update functions.
std::string Parser::updateEvent(std::string command, std::string toDoList) {
	std::string buffer;
	int TIndex;
	int taskNumber;
	buffer = toDoList;
	taskNumber = getUpdatetaskNumber(buffer);
	_taskNumberList.push_back(taskNumber);
	TIndex = getIndexOfFirstNonWhiteSpace(buffer);
	replaceStringWithItsSubstring(buffer, TIndex);
	TIndex = getIndexOfFirstWhiteSpace(buffer);
	std::string updateType = buffer.substr(0, TIndex);
	replaceStringWithItsSubstring(buffer, TIndex + 1);
    
	if (updateType == STRING_NAME) {
		_taskName=buffer;
		return updateName(command);
	} else if ( updateType == STRING_CLEAR) {
		TIndex = getIndexOfFirstNonWhiteSpace(buffer);
		replaceStringWithItsSubstring(buffer, TIndex);
		std::string clearType = buffer.substr(0,getIndexOfFirstWhiteSpace(buffer));
		return updateClear(clearType, command);

	} else if (updateType == STRING_END) {
		return updateEndingTime(buffer, command);
	} else if (updateType == STRING_START) {
		return updateStart(buffer, command);
	} else {
		return  INVALID_INPUT_MESSAGE;
	}
}

//This Method checks whether a task is a task with deadline.
bool Parser::isTaskWithDeadline(std::string toDoList){
	bool isATaskWithDeadline;
	int TIndex = toDoList.find("by:");

	if (TIndex != std::string::npos) {
		isATaskWithDeadline = true;
	} else {
		isATaskWithDeadline = false;
	}

	return isATaskWithDeadline;
}

//This method checks whether a task is timed task with starting and ending time.
bool Parser::isTimedTask(std::string toDoList) {
	bool isTimedTask;
	int TIndex = toDoList.find("from:");

	if (isValidIndex(TIndex)) {
		isTimedTask = true;
	} else {
		isTimedTask = false;
	}

	return isTimedTask;
}

//This method checks whether an index is valid.
bool Parser::isValidIndex(int TIndex) {
	if (TIndex != std::string::npos && TIndex >= 0) {
		return true;
	} else {
		return false;
	}
}

//This method checks whether date and month can be separated from the user input and at the same time, separate date and month.
bool Parser::isAbleToGetEventDateAndMonth(std::string &buffer,int &date,MonthType &month) {
	std::string dateString;
	std::string monthString;
	int TIndex = getIndexOfFirstWhiteSpace(buffer);

	if (isValidIndex(TIndex)) {
		dateString = buffer.substr(0, TIndex);
	} else {
		return false;
	}
	
	if (!isStringAnInteger(dateString)) {
			return false;			
	} else {
		date = convertStringToInteger(dateString);
	}

	replaceStringWithItsSubstring(buffer, TIndex + 1);
	TIndex = getIndexOfFirstNonWhiteSpace(buffer);
	
	int EIndex;

	if (isValidIndex(TIndex)) {
		replaceStringWithItsSubstring(buffer, TIndex);
		EIndex = getIndexOfFirstWhiteSpace(buffer);

		if (isValidIndex(EIndex)) {
			monthString = buffer.substr(0, EIndex);
		} else {
			return false;
		}

	} else {
		return false;
	}

	month = determineMonthType(monthString);
	replaceStringWithItsSubstring(buffer, EIndex);
	TIndex = getIndexOfFirstNonWhiteSpace(buffer);

	if (isValidIndex(TIndex)) {
		replaceStringWithItsSubstring(buffer, TIndex);
	} else {
		return false;
	}

	return true;
}

//This method assigns a corresponding enum MonthType to user input month which is a string.
MonthType Parser :: determineMonthType(std::string monthString) {

	monthString = _verificationDateTimeMonth.lowercaseMonth(monthString);

	for (int i = monthString.size() - 1; i >= 0; i--) {
		assert( !(isupper(monthString[i])) );
	}

	if (monthString == "jan" ||  monthString == "january" || monthString == "01" || monthString == "1" ) {
		return JANUARY;
	} else if (monthString == "feb" || monthString == "february"|| monthString == "02" || monthString == "2") {
		return FEBRUARY;
	} else if (monthString == "mar" || monthString == "march" || monthString == "03" || monthString == "3") {
		return MARCH;
	} else if (monthString == "apr" || monthString == "april" || monthString == "04" || monthString == "4") {
		return APRIL;
	} else if ( monthString == "may" ||  monthString == "may" || monthString == "05" || monthString == "5") {
		return MAY;
	} else if (monthString == "jun" || monthString == "june"|| monthString == "06" || monthString == "6") {
		return JUNE;
	} else if (monthString == "jul" || monthString == "july" || monthString =="07" || monthString =="7" ) {
		return JULY;
	} else if (monthString == "aug" || monthString == "august" || monthString == "08" || monthString == "8") {
		return AUGUST;
	} else if (monthString == "sep" || monthString == "september" || monthString == "09" || monthString == "9") {
		return SEPTEMBER;
	} else if (monthString == "oct" ||  monthString == "october" || monthString =="10") {
		return OCTOBER;
	} else if (monthString == "nov" || monthString == "november" || monthString == "11") {
		return NOVEMBER;
	} else if (monthString == "dec" || monthString == "december" || monthString == "12") {
		return DECEMBER;
	} else {
		return MONTHNOTASSIGNED;
	}
}

void Parser::replaceStringWithItsSubstring(std::string &buffer, int TIndex) {
	buffer = buffer.substr(TIndex);
}

//This method get the number of the event to be updated from the user input.
int Parser :: getUpdatetaskNumber(std::string &buffer) {
	int indexOne;
	int indexTwo;
	std::string taskNumberString;
	int taskNumberInteger;
	indexOne = getIndexOfFirstNonWhiteSpace(buffer);
	replaceStringWithItsSubstring(buffer, indexOne);
	taskNumberString = buffer.substr(0, getIndexOfFirstWhiteSpace(buffer));

	if (isStringAnInteger(taskNumberString)) {
		taskNumberInteger = convertStringToInteger(taskNumberString);
		indexTwo = buffer.find_first_of(".");
		replaceStringWithItsSubstring(buffer, indexTwo + 1);
		return taskNumberInteger;
	} else {
		return INVALID_EVENT_NUMBER;
	}
}

//This method check whether the task numbers inputted by the user is valid, and store the task numbers into a list.
bool Parser::isAbleToGetNumberList(std::string numberList) {
	std::string taskNumberString;
	int taskNumberInteger;
	numberList = numberList.substr(getIndexOfFirstNonWhiteSpace(numberList));
	int TIndex = getIndexOfFirstWhiteSpace(numberList);

	while (isValidIndex(TIndex)) {
		taskNumberString = numberList.substr(0,TIndex);
		 
		if (isStringAnInteger(taskNumberString)) {
			taskNumberInteger = convertStringToInteger(taskNumberString);
			_taskNumberList.push_back(taskNumberInteger);
			replaceStringWithItsSubstring(numberList, TIndex);
			int EIndex = getIndexOfFirstNonWhiteSpace(numberList);

			if (isValidIndex(EIndex) && !isEmpty(numberList)) {
				replaceStringWithItsSubstring(numberList, EIndex);
			    TIndex = getIndexOfFirstWhiteSpace(numberList);
			}
			else{
				break;
			}

		} else {
			return false;			
		}
	}

	if (!isEmpty(numberList)) {		

		if (isStringAnInteger(numberList)) {
			taskNumberString = numberList;
			taskNumberInteger = convertStringToInteger(numberList);
			_taskNumberList.push_back(taskNumberInteger);
		} else {
			return false;
		}

	}
	return true;
}

int Parser::convertMonthTypeToInteger(MonthType monthType) {

	switch(monthType) {

	case JANUARY:
		return  JAN;

	case FEBRUARY:
		return FEB;

	case MARCH:
		return MAR;

	case APRIL:
		return APR;

	case MAY:
		return INTEGER_MAY;

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
		return MONTH_NOT_ASSIGNED;

	default:
		return MONTH_NOT_ASSIGNED;
	}
}

logic::CommandType Parser::changeToLogicCommandType(CommandType command) {
	switch (command) {
		
	case CHANGEDIRECTORY:
		return logic::CHANGEDIRECTORY;

	case CLEAREND:
		return logic::CLEAREND;

	case CLEARRECUREND:
		return logic::CLEARRECUREND;

	case CLEARSTART:
		return logic::CLEARSTART;

	case CLEARRECURSTART:
		return logic::CLEARRECURSTART;

	case ADDEVENTWITHDEADLINE:
		return logic::ADDEVENTWITHDEADLINE;

	case ADDFLOATINGEVENT:
		return logic::ADDFLOATINGEVENT;

	case ADDTIMEDEVENT:
		return logic::ADDTIMEDEVENT;

	case UPDATENAME:
		return logic::UPDATENAME;

	case UPDATERECURNAME:
		return logic::UPDATERECURNAME;

	case UPDATEENDINGTIME:
		return logic::UPDATEENDINGTIME;

	case UPDATERECURENDINGTIME:
		return logic::UPDATERECURENDINGTIME;

	case UPDATESTARTINGTIME:
		return logic::UPDATESTARTINGTIME;

	case UPDATERECURSTARTINGTIME:
		return logic::UPDATERECURSTARTINGTIME;
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

	case DISPLAYALL:
		return logic::DISPLAYALL;

	case DISPLAYTOMORROW:
		return logic::DISPLAYTOMORROW;

	case DELETERECUR:
		return logic::DELETERECUR;

	default:
		return logic::HELP;
	}
}

//Reset the value of all private attributes.
void Parser :: resetAttributesValue(){
	_taskName = TASK_NAME_NOT_ASSIGNED;
	_startingTime = TIME_NOT_ASSIGNED;
	_endingTime = TIME_NOT_ASSIGNED;
	_startingDate = DATE_NOT_ASSIGNED;
	_endingDate = DATE_NOT_ASSIGNED;
	_startingMonth = MONTHNOTASSIGNED;
	_endingMonth = MONTHNOTASSIGNED;
	_taskNumberList.clear();
}

//This method checks whether the string can be converted to an integer.
bool Parser::isStringAnInteger(std::string str) {

	for (int i = str.size()-1; i >= 0; i--) {

		if (!isdigit(str[i])) {
			return false;
		}

	}

	return true;
}

int Parser::convertStringToInteger(std::string str){
	return stoi(str);
}

//This method checks whether a string is an empty string or blank string
bool Parser::isEmpty(std::string str) {
	if (str.empty()) {
		return true;
	} else {

		for (int i = str.size()-1; i >= 0; i--) {
			if (str[i] != ' ') {
				return false;
			}
		}

	}
	return true;
}

int Parser::getIndexOfFirstNonWhiteSpace(std::string str) {
	return str.find_first_not_of(" ");
}

int Parser::getIndexOfFirstWhiteSpace(std::string str) {
	return str.find_first_of(" ");
}

//This method separates the task name from the entire string of user input.
std::string Parser::getTaskName(std::string &buffer) {
	int TIndex;
    std::string taskName;
	TIndex = buffer.find("from:");

	if (isValidIndex(TIndex)) {
		taskName = buffer.substr(0, TIndex - 1);
		buffer = buffer.substr(TIndex + 4);
		return taskName;
	} else {
		TIndex = buffer.find("by:");
	}

	if (isValidIndex(TIndex)) {
		taskName = buffer.substr(0, TIndex - 1);
		buffer = buffer.substr(TIndex + 2);
		TIndex = getIndexOfFirstNonWhiteSpace(buffer);
		buffer = buffer.substr(TIndex);
		return taskName;
	} else {
		taskName = buffer;
		return taskName;
	}
}

//This method assigns the corresponding values to private attributes.
void Parser:: assignDateTimeMonthAttributes(std::string startOrEnd, std::string &buffer, int date, MonthType month) {
	if (startOrEnd == STRING_START) {
		_startingDate = date; 
		_startingMonth = month; 
		_startingTime = getEventTime(buffer);
	} else if (startOrEnd == STRING_END) {
		_endingDate = date;
		_endingMonth = month;
		_endingTime = getEventTime(buffer);
	} else {
		return;
	}
}

//This method gets all the details of timed events from user input.
std::string Parser::addTimedEvent(std::string toDoList){
	std:: string buffer = toDoList;
	int date = DATE_NOT_ASSIGNED;
	MonthType month = MONTHNOTASSIGNED;
	_taskName = getTaskName(buffer);

	if (buffer.size() == 1) {
		return  INVALID_TIME_DATE_MONTH_MESSAGE;
	} else {
		replaceStringWithItsSubstring(buffer, 1);

		if (isEmpty(buffer)) {
			return  INVALID_TIME_DATE_MONTH_MESSAGE;
		} else {
			replaceStringWithItsSubstring(buffer, getIndexOfFirstNonWhiteSpace(buffer));
		}
	}

	if (isAbleToGetEventDateAndMonth(buffer, date, month)) {
		assignDateTimeMonthAttributes(STRING_START, buffer, date, month);
		int Index = buffer.find_first_of("to:");

		if (isValidIndex(Index)) {
			replaceStringWithItsSubstring(buffer, Index + 2);

			if (buffer.size() == 1) {
				return INVALID_INPUT_MESSAGE;
			} else {
				replaceStringWithItsSubstring(buffer, 1);
			}

		} else {
			return INVALID_INPUT_MESSAGE;
		}

	} else {
			return  INVALID_TIME_DATE_MONTH_MESSAGE;
	}

	if (buffer.size() == 1) {
		return  INVALID_TIME_DATE_MONTH_MESSAGE;
	} else {
		replaceStringWithItsSubstring(buffer, 1);
		
		if (isEmpty(buffer)) {
			return  INVALID_TIME_DATE_MONTH_MESSAGE;
		} else {
			replaceStringWithItsSubstring(buffer, getIndexOfFirstNonWhiteSpace(buffer));
		}
	}

	if (isAbleToGetEventDateAndMonth(buffer,date, month)) {
		assignDateTimeMonthAttributes(STRING_END, buffer, date, month);
		return VerifyAllAttributesAndCallLogic(ADDTIMEDEVENT);
	} else {
		return  INVALID_TIME_DATE_MONTH_MESSAGE;
	}
}

//This method gets all the details of a dealine event from the user input.
std::string Parser::addEventWithDeadline(std::string toDoList) {
	std::string buffer = toDoList;
	_taskName = getTaskName(buffer);
	int date= DATE_NOT_ASSIGNED;
	MonthType month= MONTHNOTASSIGNED;

	if (buffer.size() == 1) {
		return  INVALID_TIME_DATE_MONTH_MESSAGE;
	}	else{
		replaceStringWithItsSubstring(buffer, 1);

		if (isEmpty(buffer)) {
			return  INVALID_TIME_DATE_MONTH_MESSAGE;
		} else {
			replaceStringWithItsSubstring(buffer,getIndexOfFirstNonWhiteSpace(buffer));
		}
	}

	if (isAbleToGetEventDateAndMonth(buffer,date, month)) {
		assignDateTimeMonthAttributes(STRING_END, buffer, date, month);
		return VerifyAllAttributesAndCallLogic(ADDEVENTWITHDEADLINE);
	} else {
		return  INVALID_TIME_DATE_MONTH_MESSAGE;
	}
}

//This method gets the time of event from the user input.
std::string Parser::getEventTime(std::string &buffer) {
	std::string time;
	int TIndex = getIndexOfFirstNonWhiteSpace(buffer);
	replaceStringWithItsSubstring(buffer, TIndex);
	TIndex = getIndexOfFirstWhiteSpace(buffer);

	if (isValidIndex(TIndex)) {
		time = buffer.substr(0, TIndex);
		replaceStringWithItsSubstring(buffer, TIndex);
	} else if (!isEmpty(buffer)) {
		time = buffer;
	}

	return time;
}

std::string Parser::addFloatingEvent(std::string toDoList) {
	std::string buffer = toDoList;
	_taskName=getTaskName(buffer);
	return VerifyAllAttributesAndCallLogic(ADDFLOATINGEVENT);
}

//This method final verifies the validity of all the details of the event and pass the values to logic to execute.
std::string Parser::VerifyAllAttributesAndCallLogic(CommandType command) {

	int integerStartingMonth = convertMonthTypeToInteger(_startingMonth);
	int integerEndingMonth = convertMonthTypeToInteger(_endingMonth);
	bool isTimeInteger = isStringAnInteger(_startingTime) && isStringAnInteger(_endingTime);
	int integerStartingTime;
	int integerEndingTime;

	if(isTimeInteger) {
		integerStartingTime = convertStringToInteger(_startingTime);
		integerEndingTime = convertStringToInteger(_endingTime);
	} else {
		return  INVALID_TIME_DATE_MONTH_MESSAGE;
	}
	
	logic::CommandType _command;
	_command = changeToLogicCommandType(command);
	std::string feedback = EMPTY_STRING;

	switch (command) {

	case ADDTIMEDEVENT:

		if (_verificationDateTimeMonth.isEndingLaterThanStarting(integerStartingTime, integerStartingMonth, _startingDate, integerEndingTime, integerEndingMonth, _endingDate)) {
			feedback = _logic.executeCommand(_command , _taskName, _startingDate, integerStartingMonth,  integerStartingTime,_endingDate, integerEndingMonth, integerEndingTime, _taskNumberList);
			
			assert( feedback != EMPTY_STRING );

			resetAttributesValue();
			return feedback;
		} else {
			return  INVALID_TIME_DATE_MONTH_MESSAGE;
		}

	case DELETE:

	case DELETERECUR:

	case UPDATERECURNAME:

	case CLEARRECUREND:

	case CLEARRECURSTART:

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

	case DISPLAYTOMORROW:

	case DISPLAYALL:
		
	case REPEAT:
		
	case REPEATDONE:

	case MARKASDONE:
		feedback = _logic.executeCommand(_command , _taskName, _startingDate, integerStartingMonth,  integerStartingTime,_endingDate, integerEndingMonth, integerEndingTime, _taskNumberList);
		
		assert( feedback != EMPTY_STRING );

		resetAttributesValue();
		return feedback;

	case UPDATEENDINGTIME:

	case UPDATERECURENDINGTIME:

	case ADDEVENTWITHDEADLINE:
		if (_verificationDateTimeMonth.isDateMonthTimeValid(_endingDate, integerEndingMonth, integerEndingTime)) { 
			feedback = _logic.executeCommand(_command , _taskName, _startingDate, integerStartingMonth,  integerStartingTime,_endingDate, integerEndingMonth, integerEndingTime, _taskNumberList);
			
			assert( feedback != EMPTY_STRING );

			resetAttributesValue();
			return feedback;
		} else {
			return  INVALID_TIME_DATE_MONTH_MESSAGE;
		}

	case UPDATERECURSTARTINGTIME:

	case UPDATESTARTINGTIME:
		if (_verificationDateTimeMonth.isDateMonthTimeValid(_startingDate, integerStartingMonth, integerStartingTime)) { 
			feedback = _logic.executeCommand(_command , _taskName, _startingDate, integerStartingMonth,  integerStartingTime,_endingDate, integerEndingMonth, integerEndingTime, _taskNumberList);
			
			assert( feedback != EMPTY_STRING );

			resetAttributesValue();
			return feedback;
		} else {
			return  INVALID_TIME_DATE_MONTH_MESSAGE;
		}

	default:
		resetAttributesValue();
		return INVALID_INPUT_MESSAGE;
	}
}

//This funtion is for unit test purpose. (Assign values to the private attributes)
void Parser::setAttributes(std::string taskName, std::string startingTime, std::string endingTime, int startingDate, int endingDate, MonthType startingMonth, MonthType endingMonth, std::list<int> taskNumberList) {
	_taskName = taskName;
	_startingTime = startingTime;
	_endingTime = endingTime;
	_startingDate = startingDate;
	_endingDate = endingDate;
	_startingMonth = startingMonth;
	_endingMonth = endingMonth;
	_taskNumberList = taskNumberList;
}
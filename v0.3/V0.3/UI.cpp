#include "UI.h"
#include <string>
#include <iostream>
#include <ctype.h>
#include "Parser.h"
using namespace std;

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
static const  string WELCOME_MESSAGE = "================================================\nWelcome to Minik!What would you like to do today?\n================================================\n";
static const string EMPTY_STRING = "";

UI::UI(){
	_commandWord=EMPTY_STRING;
	_toDoList=EMPTY_STRING;
	
}

UI::~UI(void){}

void UI::showWelcomeMessage(){
	cout << WELCOME_MESSAGE <<endl;
}

bool UI:: readCommandAndVerifyCommand(){
	bool isValid=true;
	cin >> _commandWord;

	if(_commandWord.empty()){
		isValid = false;
	}
	else
	{
		_commandWord = _verificationCommand.lowercaseCommandWord(_commandWord);
		isValid = _verificationCommand.isValidCommandWord(_commandWord);
	}

	return isValid;
}

UI::CommandType UI::determineCommandType() {
	if (_commandWord == STRING_ADD){
		return ADD;
	}
	else if (_commandWord == STRING_DISPLAY) {
		return DISPLAY;
	}
	else if (_commandWord == STRING_DELETE) {
		return DELETE;
	}
	else if (_commandWord == STRING_UPDATE) {
		return UPDATE;
	}
	else if (_commandWord == STRING_EXIT) {
		return EXIT;
	}
	else if (_commandWord == STRING_DONE){
		return DONE;
	}
	else if (_commandWord == STRING_DISPLAYDONE){
		return DISPLAYDONE;
	}
	else if (_commandWord == STRING_DISPLAYTODAY){
		return DISPLAYTODAY;
	}
	else if(_commandWord == STRING_UNDO){
		return UNDO;
	}
	else if (_commandWord == STRING_CLEAR){
		return CLEAR;
	}
	else if (_commandWord == STRING_SEARCH){
		return SEARCH;
	}
	else if(_commandWord == STRING_CHANGEDIRECTORY){
		return CHANGEDIRECTORY;
	}
	else if(_commandWord == STRING_REPEAT){
		return REPEAT;
	}
	else if(_commandWord == STRING_REPEATDONE){
		return REPEATDONE;
	}
	else{
		return HELP;
	}
}


bool UI::isEmpty(string str){
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

bool UI::getToDoListAndCheckEmpty(){
	getline(cin, _toDoList);
	if(isEmpty(_toDoList)){
		return true;
	}
	else{
		return false;
	}
}

void UI:: getTheToDoListWithIndexZeroNotEmpty(){

	int TIndex = _toDoList.find_first_not_of(" ");
	_toDoList = _toDoList.substr(TIndex);
}

string UI::callToParser(){
	CommandType typeOfCommand = determineCommandType();

	switch (typeOfCommand)
	{
		case ADD:
			if(getToDoListAndCheckEmpty()){
				return INVALID_INPUT;
			}
			else{
				getTheToDoListWithIndexZeroNotEmpty();
				return _Parser.addEvent(_toDoList);			
			}
		
		case DISPLAY:
			if(getToDoListAndCheckEmpty()){
				return _Parser.displayEvent(STRING_DISPLAY);
			}
			else{
				return INVALID_INPUT;
			}
		
		case DELETE:
			if(getToDoListAndCheckEmpty()){
				return INVALID_INPUT;
			}
			else{
				getTheToDoListWithIndexZeroNotEmpty();
				return _Parser.deleteEvent(_toDoList);	
			}
		
		case UPDATE:
			if(getToDoListAndCheckEmpty()){
				return INVALID_INPUT;
			}
			else{
				getTheToDoListWithIndexZeroNotEmpty();
				return _Parser.updateEvent(_toDoList);		
			}
		
		case DONE:
			if(getToDoListAndCheckEmpty()){
				return INVALID_INPUT;
			}
			else{
				getTheToDoListWithIndexZeroNotEmpty();
				return _Parser.markAsDone(_toDoList);
			}
			
		case DISPLAYDONE:
			if(getToDoListAndCheckEmpty()){
				return _Parser.displayEvent(STRING_DISPLAYDONE);
			}
			else{
				return INVALID_INPUT;
			}
						
		case DISPLAYTODAY:
			if(getToDoListAndCheckEmpty()){
				return _Parser.displayEvent(STRING_DISPLAYTODAY);
			}
			else{
				return INVALID_INPUT;
			}

		case EXIT:
			if(getToDoListAndCheckEmpty()){
				exit(0);
			}
			else{
				return INVALID_INPUT;
			}
			
		case UNDO:
			if(getToDoListAndCheckEmpty()){
				return _Parser.unDo();
			}
			else{
				return INVALID_INPUT;
			}

		case CLEAR:
			if(getToDoListAndCheckEmpty()){
				return _Parser.clearEvent();
			}
			else{
				return INVALID_INPUT;
			}			

		case SEARCH:
			if(getToDoListAndCheckEmpty()){
				return INVALID_INPUT;
			}
			else{
			getTheToDoListWithIndexZeroNotEmpty();
				return _Parser.searchEvent(_toDoList);
			}

		case CHANGEDIRECTORY:
			if(!getToDoListAndCheckEmpty()){
				getTheToDoListWithIndexZeroNotEmpty();
				return _Parser.changeDirectory(_toDoList);
			}
			else{
				return INVALID_INPUT;
			}
		case HELP:
			if(getToDoListAndCheckEmpty()){
				return _Parser.help();
			}
			else{
				return false;
			}

		case REPEAT:
			if(getToDoListAndCheckEmpty()){
				return INVALID_INPUT;
			}
			else{
				getTheToDoListWithIndexZeroNotEmpty();
				return _Parser.repeat(_toDoList, STRING_REPEAT);
			}
			
		case REPEATDONE:
			if(getToDoListAndCheckEmpty()){
				return INVALID_INPUT;
			}
			else{
				getTheToDoListWithIndexZeroNotEmpty();
				return _Parser.repeat(_toDoList, STRING_REPEATDONE);
			}

		default:
			return INVALID_INPUT;
			break;
			
		}
	
}



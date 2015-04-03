#include "UI.h"
#include <string>
#include <iostream>
#include <ctype.h>
#include "Parser.h"
using namespace std;

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
	if (_commandWord == "add"){
		return ADD;
	}
	else if (_commandWord == "display") {
		return DISPLAY;
	}
	else if (_commandWord == "delete") {
		return DELETE;
	}
	else if (_commandWord == "update") {
		return UPDATE;
	}
	else if (_commandWord == "exit") {
		return EXIT;
	}
	else if (_commandWord == "done"){
		return DONE;
	}
	else if (_commandWord == "displaydone"){
		return DISPLAYDONE;
	}
	else if (_commandWord == "displaytoday"){
		return DISPLAYTODAY;
	}
	else if(_commandWord == "undo"){
		return UNDO;
	}
	else if (_commandWord == "clear"){
		return CLEAR;
	}
	else if (_commandWord == "search"){
		return SEARCH;
	}
	else if(_commandWord =="changedirectory"){
		return CHANGEDIRECTORY;
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
				return _Parser.displayEvent("display");
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
				return _Parser.displayEvent("displaydone");
			}
			else{
				return INVALID_INPUT;
			}
						
		case DISPLAYTODAY:
			if(getToDoListAndCheckEmpty()){
				return _Parser.displayEvent("displaytoday");
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

		default:
			return INVALID_INPUT;
			break;
			
		}
	
}



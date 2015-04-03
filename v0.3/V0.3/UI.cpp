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

bool UI:: readCommand(){
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

void UI::showWelcomeMessage(){
	cout << WELCOME_MESSAGE <<endl;
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

string UI::callToParser(){
	CommandType typeOfCommand = determineCommandType();

	switch (typeOfCommand)
	{
		case ADD:
			getline(cin, _toDoList);
			if(isEmpty(_toDoList)){
				return INVALID_INPUT;
			}
			else{
				_toDoList = _toDoList.substr(1);
				return _Parser.addEvent(_toDoList);			
			}
		
		case DISPLAY:
			getline(cin, _toDoList);
			if(isEmpty(_toDoList)){
				return _Parser.displayEvent("display");
			}
			else{
				return INVALID_INPUT;
			}
		
		case DELETE:
			getline(cin, _toDoList);
			if(isEmpty(_toDoList)){
				return INVALID_INPUT;
			}
			else{
				_toDoList = _toDoList.substr(1);
				return _Parser.deleteEvent(_toDoList);	
			}
		
		case UPDATE:
			getline(cin, _toDoList);
			if(isEmpty(_toDoList)){
				return INVALID_INPUT;
			}
			else{
				_toDoList = _toDoList.substr(1);
				return _Parser.updateEvent(_toDoList);		
			}
		
		case DONE:
			getline(cin, _toDoList);
			if(isEmpty(_toDoList)){
				return INVALID_INPUT;
			}
			else{
				_toDoList = _toDoList.substr(1);
				return _Parser.markAsDone(_toDoList);
			}
			
		case DISPLAYDONE:
			getline(cin, _toDoList);
			if(isEmpty(_toDoList)){
				//cout << "uouo";
				return _Parser.displayEvent("displaydone");
			}
			else{
				return INVALID_INPUT;
			}
						
		case DISPLAYTODAY:
			getline(cin, _toDoList);
			if(isEmpty(_toDoList)){
				return _Parser.displayEvent("displaytoday");
			}
			else{
				return INVALID_INPUT;
			}

		case EXIT:
			getline(cin, _toDoList);
			if(isEmpty(_toDoList)){
				exit(0);
			}
			else{
				return INVALID_INPUT;
			}
			
		case UNDO:
			getline(cin, _toDoList);
			if(isEmpty(_toDoList)){
				return _Parser.unDo();
			}
			else{
				return INVALID_INPUT;
			}

		case CLEAR:
			getline(cin, _toDoList);
			if(isEmpty(_toDoList)){
				return _Parser.clearEvent();
			}
			else{
				return INVALID_INPUT;
			}			

		case SEARCH:
			getline(cin, _toDoList);
			if(isEmpty(_toDoList)){
				return INVALID_INPUT;
			}
			else{
				_toDoList = _toDoList.substr(1);
				return _Parser.searchEvent(_toDoList);
			}

		case CHANGEDIRECTORY:
			getline(cin, _toDoList);
			if(!isEmpty(_toDoList)){
				return _Parser.changeDirectory(_toDoList);
			}
			else{
				return INVALID_INPUT;
			}


		default:
			return INVALID_INPUT;
			break;
			
		}
	
}

UI::~UI(void){}


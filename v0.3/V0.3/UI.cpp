#include "UI.h"
#include <string>
#include <iostream>
#include <ctype.h>
#include "Parser.h"
using namespace std;

static const string INVALID_INPUT_MESSAGE = "Sorry, wrong user input.";
static const  string WELCOME_MESSAGE = "================================================\nWelcome to Minik!What would you like to do today?\n================================================\n";
UI::UI(){
	_commandWord="";
	_toDoList="";
	
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
	else if (_commandWord == "displayDone"){
		return DISPLAYDONE;
	}
	else if (_commandWord == "displayToday"){
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
	else if(_commandWord == "help"){
		return HELP;
	}
	else{ 
		return HELP;
	}
}

void UI::showWelcomeMessage(){
	cout << WELCOME_MESSAGE <<endl;
}

string UI::callToParser(){
	CommandType typeOfCommand = determineCommandType();

	switch (typeOfCommand)
	{
		case ADD:
			getline(cin, _toDoList);
			_toDoList = _toDoList.substr(1);
			return _Parser.addEvent(_toDoList);			
		
		case DISPLAY:
			return _Parser.displayEvent("display");
		
		case DELETE:
			getline(cin, _toDoList);
			_toDoList = _toDoList.substr(1);
			return _Parser.deleteEvent(_toDoList);			
		
		case UPDATE:
			getline(cin, _toDoList);
			_toDoList = _toDoList.substr(1);
			return _Parser.updateEvent(_toDoList);			
		
		case DONE:
			getline(cin, _toDoList);
			_toDoList = _toDoList.substr(1);
			return _Parser.markAsDone(_toDoList);
			
		case DISPLAYDONE:
			return _Parser.displayEvent("displayDone");
						
		case DISPLAYTODAY:
			return _Parser.displayEvent("displayToday");

		case HELP:
			return _Parser.printHelp();

		case EXIT:
			exit(0);
			
		case UNDO:
			return _Parser.unDo();

		case CLEAR:
			return _Parser.clearEvent();

		case SEARCH:
			getline(cin, _toDoList);
			_toDoList = _toDoList.substr(1);
			return _Parser.searchEvent(_toDoList);

		default:
			return INVALID_INPUT_MESSAGE;
			break;
			
		}
	
}

UI::~UI(void){}

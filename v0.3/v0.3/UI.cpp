#include "UI.h"
#include <string>
#include <iostream>
#include <ctype.h>
#include "Parser.h"
using namespace std;

static const string INVALID_INPUT_MESSAGE = "Sorry, wrong user input.";
static const  string WELCOME_MESSAGE = "Welcome to Minik!";

UI::UI(){
	_commandWord="";
	_toDoList="";
}

bool UI:: readCommand(){
	bool isEmpty=true;
	cin >> _commandWord;
	if(!_commandWord.empty()){
		isEmpty=false;
	}

	return isEmpty;
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
	
}

void UI::showWelcomeMessage(){
	cout << WELCOME_MESSAGE <<endl;
}

string UI::callToParser(){
	CommandType commandType = determineCommandType();
	int index;

	switch (commandType)
	{
		case ADD:
			getline(cin, _toDoList);
			_toDoList = _toDoList.substr(1);
			_Parser.addEvent(_toDoList);			
		
		case DISPLAY:
			_Parser.displayEvent("display");
		
		case DELETE:
			getline(cin, _toDoList);
			_toDoList = _toDoList.substr(1);
			_Parser.deleteEvent(_toDoList);			
		
		case UPDATE:
			getline(cin, _toDoList);
			_toDoList = _toDoList.substr(1);
			_Parser.updateEvent(_toDoList);			
		
		case DONE:
			getline(cin, _toDoList);
			_toDoList = _toDoList.substr(1);
			_Parser.markAsDone(_toDoList);
			
		case DISPLAYDONE:
			_Parser.displayEvent("displayDone");
						
		case DISPLAYTODAY:
			_Parser.displayEvent("displayToday");

		case EXIT:
			exit(0);
			
		case UNDO:
			_Parser.unDo();

		case CLEAR:
			_Parser.clearEvent();

		case SEARCH:
			getline(cin, _toDoList);
			_toDoList = _toDoList.substr(1);
			_Parser.searchEvent(_toDoList);

		default:
			cout<<INVALID_INPUT_MESSAGE;
			break;
			
		}
	
}

UI::~UI(void){}


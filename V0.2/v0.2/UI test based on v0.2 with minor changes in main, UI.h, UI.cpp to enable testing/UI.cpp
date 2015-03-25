#include "UI.h"
#include <string>
#include <iostream>
#include <ctype.h>
#include "logic.h"
using namespace std;

static const string INVALID_DELETION_MESSAGE = "Sorry, wrong user input. Please key in delete, a space and the index of the task\neg: delete 234\n If you do not know the index, key in display.\n";
static const string INVALID_UPDATE_MESSAGE = "Sorry, wrong user input. Please key in the command update, a space and the index of the task\neg: update 234\nIf you do not know the index, kewy in display.\n"; 
static const  string WELCOME_MESSAGE = "Welcome to Minik!";
static const  string INVALID_ADD_MESSAGE ="Sorry, wrong user input. To do list cannot be empty. Please key in add, a space and your to do list.\n";
static const  string INVALID_DISPLAY_MESSAGE = "Sorry, wrong user input. Please only key in the word display.\n";
static const  string INVALID_INPUT_MESSAGE = "Sorry, wrong user input.\n";
static const string INVALID_DONE_MESSAGE = "Sorry, wrong user input. Please key in the command done, a space and the index of the task\neg: done 234\nIf you do not know the index, kewy in display.\n"; 
static const string INVALID_PENDING_MESSAGE = "Sorry, wrong user input. Please key in the command pending, a space and the index of the task\neg: pending 234\nIf you do not know the index, kewy in display.\n"; 

//UI initialize a single user input.
UI::UI(){
	_commandWord="";
	_toDoList="";
	
}

 
bool UI:: readCommand(string &command){
	bool isEmpty=true;
	cin >> _commandWord;
	if(!_commandWord.empty()){
		isEmpty=false;
	}
	command = _commandWord;
	return isEmpty;
}
UI::CommandType UI::determineCommandType(string commandWord) {
	if (commandWord == "add"){
		return ADD;
	}
	else if (commandWord == "display") {
		return DISPLAY;
	}
	else if (commandWord == "delete") {
		return DELETE;
	}
	else if (commandWord == "update") {
		return UPDATE;
	}
	else if (commandWord == "exit") {
		return EXIT;
	}
	else if (commandWord == "done"){
		return DONE;
	}
	else if (commandWord == "pending"){
		return PENDING;
	}

	else if (commandWord == "displayDone"){
		return DISPLAYDONE;
	}
	else if (commandWord == "displayPending"){
		return DISPLAYPENDING;
	}
	
}
string UI::showWelcomeMessage(){
	cout << WELCOME_MESSAGE <<endl;
	return WELCOME_MESSAGE;
}


//Check whether the toDoList is merely a number
bool UI::isNumber() {
	 for(int i=0;i<_toDoList.size();i++){
		 if(!isdigit(_toDoList[i])){
			 return false;
		 }
	 }
	 return true;
 }
 
//Primary check on the validity of user input.
bool UI::validityOfUserInput(){
	string commandWord =_commandWord;
	CommandType commandType = determineCommandType(commandWord);
	bool isValid = false;
	
	switch (commandType)
	{
		case ADD:
			getline(cin, _toDoList);
			if(_toDoList!=""){
				isValid=true;
				_toDoList=_toDoList.substr(1);
			}
			else{
			cout << INVALID_ADD_MESSAGE;
			}
			return isValid;
		
		case DISPLAY:
			_toDoList="";
			isValid= true;
			return isValid;
		
		case DELETE:
			cin >> _toDoList;
			if(isNumber()){
				isValid= true;
			}
			else{
				cout << INVALID_DELETION_MESSAGE;
			}
				
			return isValid;
		
		case UPDATE:
			getline (cin,_toDoList);
			if(_toDoList!=""){
				isValid=true;
				_toDoList=_toDoList.substr(1);
			}
			else{
			cout << INVALID_ADD_MESSAGE;
			}
			return isValid;
		
		case DONE:
			cin >> _toDoList;
			if(isNumber()){
				isValid= true;
			}
			else{
				cout << INVALID_DONE_MESSAGE;
			}
				
			return isValid;
			
		case PENDING:
			cin >> _toDoList;
			if(isNumber()){
				isValid= true;
			}
			else{
				cout << INVALID_PENDING_MESSAGE;
			}
			return isValid;
			
		case DISPLAYDONE:
			_toDoList="";
			isValid= true;
			return isValid;
			
		case DISPLAYPENDING:
			_toDoList="";
			isValid= true;
			return isValid;
			
		case EXIT:
			exit(0);
			
		default:
			cout<<INVALID_INPUT_MESSAGE;
			break;
			
		}
	}

// Call logic to proceed on
string UI::callToLogic(){
	_logic.setCommand(_commandWord, _toDoList);
	string feedback = _logic.executeCommand();
	return feedback;		
}

UI::~UI(void){}


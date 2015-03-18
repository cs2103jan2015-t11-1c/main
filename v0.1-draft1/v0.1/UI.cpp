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
	else if (_commandWord == "pending"){
		return PENDING;
	}

	else if (_commandWord == "displayDone"){
		return DISPLAYDONE;
	}
	else if (_commandWord == "displayPending"){
		return DISPLAYPENDING;
	}
	
}
void UI::showWelcomeMessage(){
	cout << WELCOME_MESSAGE <<endl;
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
	
	CommandType commandType = determineCommandType();
	bool isValid = false;
<<<<<<< HEAD
	
	switch (commandType)
	{
		case ADD:
			getline(cin, _toDoList);
			if(_toDoList!=""){
				isValid=true;
			}
			else{
=======
	if (commandWord == "add"||commandWord =="delete"||commandWord == "update"){
		if(_line.size()!=commandWord.size()){
			int startingPositionOfToDoList = endPositionOfCommandWord+1;
			_toDoList=_line.substr(startingPositionOfToDoList);
			isValid=true;
		    string toDoList = _toDoList;
		}

		else{
>>>>>>> b0ea122f573296d8a751dfbd91fa841d6b040c27
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
			getline(cin, _toDoList);
			if(!_toDoList.empty()){
				isValid= true;
			}
			else{
				cout << INVALID_UPDATE_MESSAGE;
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
<<<<<<< HEAD
=======
	
	else if(commandWord == "display"){
		_toDoList="";
		string toDoList = _toDoList;
		isValid= true;
	}

	else if(commandWord=="exit"){
		isValid =true;
	}

	else{
		cout<<INVALID_INPUT_MESSAGE;
	}

	return isValid;
}

UI::~UI(void){}

>>>>>>> b0ea122f573296d8a751dfbd91fa841d6b040c27

// Call logic to proceed on
string UI::callToLogic(){
	_logic.setCommand(_commandWord, _toDoList);
	string feedback = _logic.executeCommand();
	return feedback;		
}

UI::~UI(void){}


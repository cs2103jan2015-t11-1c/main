#include "UI.h"
#include <string>
#include <iostream>
#include <ctype.h>
#include "logic.h"
using namespace std;

static const string INVALID_DELETION_MESSAGE = "Sorry, wrong user input. Please key in delete, a space and the index of the task\neg: delete 234\n If you do not know the index, key in display.";
static const string INVALID_UPDATE_MESSAGE = "Sorry, wrong user input. Please key in the command update, a space and the index of the task\neg: update 234\nIf you do not know the index, kewy in display."; 
static const  string WELCOME_MESSAGE = "Welcome to Minik!";
static const  string INVALID_ADD_MESSAGE ="Sorry, wrong user input. To do list cannot be empty. Please key in add, a space and your to do list.";
static const  string INVALID_DISPLAY_MESSAGE = "Sorry, wrong user input. Please only key in the word display.";
static const  string INVALID_INPUT_MESSAGE = "Sorry, wrong user input.";

//UI initialize a single user input.
UI::UI(){
	_commandWord="";
	_toDoList="";
	_line="";
	

}

bool UI:: readCommand(){
	bool isEmpty=true;
	getline(cin, _line);
	if(!_line.empty()){
		isEmpty=false;
	}
	return isEmpty;
}

void UI::showWelcomeMessage(){
	cout << WELCOME_MESSAGE <<endl;
}


//Check whether the toDoList is merely a number
 bool isNumber(string toDoList) {
	 for(unsigned int i=0;i < toDoList.size();i++){
		 if(!isdigit(toDoList[i])){
			 return false;
		 }
	 }
	 return true;
 }

//Primary check on the validity of user input.
bool UI::validityOfUserInput(){
	int endPositionOfCommandWord = _line.find_first_of(" ");
	_commandWord = _line.substr(0, endPositionOfCommandWord);
	string commandWord = _commandWord;
	bool isValid = false;

	if (commandWord == "add"){
		if(_line.size()!=commandWord.size()){
			int startingPositionOfToDoList = endPositionOfCommandWord+1;
			_toDoList=_line.substr(startingPositionOfToDoList);
			isValid=true;
		string toDoList = _toDoList;
		}

		else{
			cout << INVALID_ADD_MESSAGE;
		}
	}
	
	else if(commandWord == "display"){
		_toDoList="";
		string toDoList = _toDoList;
		isValid= true;
	}

	else if(commandWord=="update"||"delete"||"exit"){
		isValid =true;
	}
	else if(commandWord!="update"||"delete"||"exit"||"add"||"display"){
		cout << INVALID_INPUT_MESSAGE <<endl;
	}
	
	return isValid;
}

UI::~UI(void){}


// Call logic to proceed on
string UI::callToLogic(){
	_logic.setCommand(_commandWord, _toDoList);
	string feedback = _logic.executeCommand();
	return feedback;		
}

/*
//need to figure out with logic:P
 bool UI::isCompletedAction(string & line){
	 bool isCompleted = false;
	 if(logic.done()){
		 isCompleted = true;
	 }

	 return isCompleted;
 }
*/



/*if (commandWord == "delete"){
		if(!isNumber(toDoList)){
			cout << INVALID_DELETION_MESSAGE;
		}
		else{
			isValid = true;
		}
	}

	else if (commandWord == "update"){
		if(!isNumber(toDoList)){
			cout << INVALID_UPDATE_MESSAGE;
		}
		else{
			isValid = true;
		}
	}

	else
	*/

/*
//determineCommandWordnToDoList() separates the command word and whatever words following the command word.
void UI::determineCommandWordnToDoList(){
	int endPositionOfCommandWord = _line.find_first_of(" ");
	_commandWord = _line.substr(0, endPositionOfCommandWord);

	if(_commandWord.size()==_line.size()){
		_toDoList="";
	}
	else{
		int startingPositionOfToDoList = endPositionOfCommandWord+1;
		_toDoList=_line.substr(startingPositionOfToDoList);
	}
}
*/
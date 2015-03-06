#include "UI.h"
#include <string>
#include <iostream>
#include <ctype.h>

static const std::string INVALID_DELETION_MESSAGE = "Sorry, wrong user input. Please key in delete, a space and the index of the task \n eg: delete 234 \n If you do not know the index, key in display\n";
static const std::string INVALID_UPDATE_MESSAGE = "Sorry, wrong user input. Please key in the command update, a space and the index of the task \n eg: update 234 \nIf you do not know the index, kewy in display\n"; 
static const std:: string WELCOME_MESSAGE = "Welcome to Minik!\n";
static const std:: string INVALID_ADD_MESSAGE ="To do list cannot be empty. Please key in add followed by your to do list.\n";
static const std:: string INVALID_DISPLAY_MESSAGE = "Please only key in the word display\n";

//UI initialize a single user input.
UI::UI(void){
	_commandWord="";
	_toDoList="";
	_line="";
}

void UI:: readCommand(){
	std::string line;
	getline(std::cin, line);
	_line = line;
}

void showWelcomeMessage(){
	std::cerr << WELCOME_MESSAGE <<std::endl;
}

//determineCommandWordnToDoList() separates the command word and whatever words folling the command word.
void UI::determineCommandWordnToDoList(){
	int endPositionOfCommandWord = _line.find_first_of(" ");
	_commandWord = _line.substr(0, endPositionOfCommandWord);
	int startingPositionOfToDoList = endPositionOfCommandWord+1;
	_toDoList=_line.substr(startingPositionOfToDoList);
}

//Check whether the toDoList is merely a number
 bool isNumber(std::string toDoList) {
	 for(int i=0;i<toDoList.size();i++){
		 if(!isdigit(toDoList[i])){
			 return false;
		 }
	 }
	 return true;
 }

//Primary check on the validity of user input.
bool UI::validityOfUserInput(){
	std::string commandWord = _commandWord;
	std::string toDoList = _toDoList;
	bool isValid = false;
	if (commandWord == "delete"){
		if(!isNumber(toDoList)){
			std::cerr << INVALID_DELETION_MESSAGE;
		}
		else{
			isValid = true;
		}
	}

	else if (commandWord == "update"){
		if(!isNumber(toDoList)){
			std::cerr << INVALID_UPDATE_MESSAGE;
		}
		else{
			isValid = true;
		}
	}

	else if (commandWord == "add"){
		if(toDoList !=""){
			isValid = true;
		}
		else{
			std::cerr << INVALID_ADD_MESSAGE;
		}
	}
	
	else if(commandWord == "display"){
		if(toDoList == ""){
			isValid = true;
		}
		else{
			std::cerr << INVALID_DISPLAY_MESSAGE;
		}
	}

	return isValid;
}

UI::~UI(void){}

// Call logic to proceed on
void UI::callToLogic(){
	Logic logic(_commandWord, _toDoList);//??????
	return;
}

//need to figure out with logic:P
 bool UI::isCompletedAction(std::string & line){
	 bool isCompleted = false;
	 if(logic.done()){
		 isCompleted = true;
	 }

	 return isCompleted;
 }



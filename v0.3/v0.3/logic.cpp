#include "logic.h"
#include <assert.h>
#include <iostream>
const static string EXIT_MESSAGE = "Thank you for using Minik:)";
const static string EXCEPTION_INVALID_INDEX = "ERROR: Invalid task number. Please enter a valid task number.";

logic::logic(){
	_storage = Storage();
}

logic::logic(string commandWord, string toDoList){
	//_storage = Storage();
	_commandWord = commandWord;
	_toDoList = toDoList;
}

logic::~logic(){
}

void logic:: setCommand (string commandWord, string toDoList){
	_commandWord = commandWord;
	_toDoList = toDoList;
}




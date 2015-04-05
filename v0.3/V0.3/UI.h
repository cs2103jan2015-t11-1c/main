//#pragma once

#ifndef UI_H
#define UI_H
#include <cstring>
#include <string>
#include <iostream>
#include "Parser.h"
#include "VerificationCommand.h"

class UI{
    private:
		string _commandWord;
		string _toDoList;
		Parser _Parser;
		VerificationCommand _verificationCommand;
		
    public:
		enum CommandType {ADD, DELETE, DISPLAY, UPDATE, EXIT, DONE, DISPLAYDONE, DISPLAYTODAY, CHANGEDIRECTORY, SEARCH, UNDO, HELP, CLEAR, REPEAT, REPEATDONE};
		UI(void);
		~UI(void);
	    CommandType determineCommandType();
		
		string callToParser();
		bool isEmpty(string );
		bool getToDoListAndCheckEmpty();
		bool readCommandAndVerifyCommand();
		void getTheToDoListWithIndexZeroNotEmpty();
		string showWelcomeMessage();
		void setValueForAttributes(string, string);
		string getToDoList();
};
		
#endif

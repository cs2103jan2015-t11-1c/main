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
		
		enum CommandType {ADD, DELETE, DISPLAY, UPDATE, EXIT, DONE, DISPLAYDONE, DISPLAYTODAY, CHANGEDIRECTORY, SEARCH, UNDO, CLEAR, HELP};
		UI(void);
		~UI(void);
	    CommandType determineCommandType();
		void showWelcomeMessage();
	    bool readCommand();
		string callToParser();
		bool isEmpty(string );
};
		
#endif

//@author A0115253R
#pragma once

#ifndef UI_H
#define UI_H
#include <cstring>
#include <string>
#include "Parser.h"
#include "VerificationCommand.h"
#include <ctype.h>
#include <assert.h>
#include <iostream>

class UI {

    private:
		std::string _commandWord;
		std::string _toDoList;
		Parser _Parser;
		VerificationCommand _verificationCommand;
		
    public:
		UI(void);
		~UI(void);
		enum CommandType {ADD, DELETE, DISPLAY, UPDATE, EXIT, DONE, DISPLAYDONE, DISPLAYTODAY, UPDATERECUR, DELETERECUR, DISPLAYALL, DISPLAYTOMORROW, CHANGEDIRECTORY, SEARCH, UNDO, HELP, CLEAR, REPEAT, REPEATDONE};
	    CommandType determineCommandType();
		std::string callToParser();
		bool isEmpty(std::string );
		bool getToDoListAndCheckEmpty();
		bool readCommandAndVerifyCommand();
		void getTheToDoListWithIndexZeroNotEmpty();
		std::string showWelcomeMessage();
		void setValueForAttributes(std::string, std::string);
		std::string getToDoList();
};
		
#endif

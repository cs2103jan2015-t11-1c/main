//#pragma once

#ifndef UI_H
#define UI_H
#include <cstring>
#include <string>
#include <iostream>
#include "Parser.h"

class UI{
    private:
		string _commandWord;
		string _toDoList;
		Parser _Parser;
		
    public:
		enum CommandType {ADD, DELETE, DISPLAY, UPDATE, EXIT, DONE, DISPLAYDONE, DISPLAYTODAY, SEARCH, UNDO, CLEAR, HELP};
		UI(void);
		~UI(void);
	    CommandType determineCommandType();
		void showWelcomeMessage();
	    bool readCommand();
		string callToParser();
};
		
#endif

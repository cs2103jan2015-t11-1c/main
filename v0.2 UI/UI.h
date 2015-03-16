//#pragma once

#ifndef UI_H
#define UI_H
#include"Event.h"
#include "logic.h"
#include <cstring>
#include <string>
#include <iostream>

class UI{
    private:
		std::string _commandWord;
		std::string _toDoList;
		logic _logic;
	
    public:
		enum CommandType {ADD, DELETE, DISPLAY, UPDATE, EXIT, DONE, PENDING, DISPLAYDONE,DISPLAYPENDING};
		UI(void);
		~UI(void);
	    bool isNumber();
	    CommandType determineCommandType();
		void showWelcomeMessage();
	    bool readCommand();
		bool validityOfUserInput();
		string callToLogic();
};
		
#endif

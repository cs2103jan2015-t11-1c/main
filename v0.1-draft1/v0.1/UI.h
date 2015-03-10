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
		std::string _line;
		logic _logic;
	
    public:
		UI(void);
		~UI(void);
		std::string getCommandWord();
		std::string getToDoList();
		void showWelcomeMessage();
	    bool readCommand();
		bool validityOfUserInput();
		string callToLogic();
};
	  
	    bool isNumber(std::string);
		
#endif

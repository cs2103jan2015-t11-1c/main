//#pragma once

#ifndef UI_H
#define UI_H

//#include "Logic.h"
#include <cstring>
#include <string>
#include <string.h>
#include <iostream>
//#include "LOGIC.h"
class UI{
    private:
		std::string _commandWord;
		std::string _toDoList;
		std::string _line;
	

    public:
		UI(void);
		~UI(void);
		std::string getCommandWord();
		std::string getToDoList();
		void showWelcomeMessage();
	    void readCommand();
	    bool isCompletedAction(std::string & line);
	    void determineCommandWordnToDoList();
		bool validityOfUserInput();
		void callToLogic();//??? should be after checking the validity, but how to link:((
};
	  
	    bool isNumber(std::string);

#endif

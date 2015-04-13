//@author A0115253R
#include "UI\UI.h"
#include <assert.h>
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <assert.h>

const static std::string INVALID_COMMAND_MESSAGE ="Sorry, invalid command.\n\n";

int main() {

	system("mode 100,50");   //Set mode to ensure window does not exceed buffer size
    SMALL_RECT WinRect = {0, 0, 100, 50};   //New dimensions for window in 8x12 pixel chars
    SMALL_RECT* WinSize = &WinRect;			//Before integration testing, these 4 lines must be removed.
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize); 
	
//@author A0115253R
	std::string message;
	UI Minik;
	std::string welcomeMessage = Minik.showWelcomeMessage();

	assert( welcomeMessage =="================================================\nWelcome to Minik!What would you like to do today?\n================================================\n\n");

	std::cout << welcomeMessage;

	std::cout << "Command: ";

	while (1) {

		if (Minik.readCommandAndVerifyCommand()) {
			message = Minik.callToParser();

			assert( message != "" );

			std::cout << message;
		} else {
			std::string invalidToDoList;
			getline(std::cin, invalidToDoList);
			std::cout << INVALID_COMMAND_MESSAGE;
		}
		
		std::cout << "Command: ";
	}

    return 0;	
}

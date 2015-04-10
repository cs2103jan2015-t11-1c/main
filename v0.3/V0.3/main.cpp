
#include "UI.h"
#include <assert.h>
#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <assert.h>
using namespace std;

const static string INVALID_COMMAND_MESSAGE ="Sorry, invalid command.\n\n";

int main() {
	system("mode 100,50");   //Set mode to ensure window does not exceed buffer size
    SMALL_RECT WinRect = {0, 0, 100, 50};   //New dimensions for window in 8x12 pixel chars
    SMALL_RECT* WinSize = &WinRect;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize); 
	
	std::string message;
	UI Minik;
	std::string welcomeMessage = Minik.showWelcomeMessage();

	assert( welcomeMessage =="================================================\nWelcome to Minik!What would you like to do today?\n================================================\n\n");

	cout << welcomeMessage;

	cout << "Command: ";

	while (1) {
		if (Minik.readCommandAndVerifyCommand()) {
			message = Minik.callToParser();

			assert( message != "" );

			cout << message;
		} else {
			std::string invalidToDoList;
			getline(cin, invalidToDoList);
			cout << INVALID_COMMAND_MESSAGE;
		}
		
		cout << "Command: ";
	}

    return 0;	
}

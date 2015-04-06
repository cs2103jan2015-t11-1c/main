//#include "logic.h"
#include "UI.h"
#include <assert.h>
#include <iostream>
#include <Windows.h>
using namespace std;
#include <cstdlib>
const static string INVALID_COMMAND_MESSAGE ="Sorry, invalid command.\n\n";

int main() {
	string message;
	UI Minik;
	cout << Minik.showWelcomeMessage();
	cout << "Command: ";
	while(1)
	{
		if (Minik.readCommandAndVerifyCommand()) {
			message = Minik.callToParser();
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

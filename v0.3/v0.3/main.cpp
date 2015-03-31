//#include "logic.h"
#include "UI.h"
#include <assert.h>
#include <iostream>
#include <Windows.h>
using namespace std;
#include <cstdlib>
const static string INVALID_COMMAND_MESSAGE ="Sorry, invalid command.\n";

int main(){
	const int bufferSize = MAX_PATH;
    char oldDir[bufferSize];
	GetCurrentDirectory(bufferSize, oldDir);
	std::cout << "Current directory: " << oldDir << '\n';
	std::cout << "Enter any number to start Minic, enter 0 to change directory\n";
	int i;
	std::cin >> i;
	if (i == 0){
	const char* newDir;
	char newdir[100];
	cin >> newdir;
	newDir = newdir;
	SetCurrentDirectory(newDir);
	std::cout << "Set current directory to " << newDir << '\n';
	}

	string msg;
	UI mnk;
	//std::cout <<"main" <<std::endl;
	mnk.showWelcomeMessage();

	while(1)
	{
	if(mnk.readCommand()){
		msg = mnk.callToParser();
		cout << msg;
	}
	else{
		cout << INVALID_COMMAND_MESSAGE;
	}
	{

	}
	}
	system("pause");
    return 0;	
}

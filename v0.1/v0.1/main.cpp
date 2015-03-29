#include "logic.h"
#include "UI.h"
#include "Storage.h"
#include <iostream>
using namespace std;
#include <cstdlib>

#include "easyloggingpp-9.80\src\easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(){
	UI mnk;
	LOG(INFO) << "My first info log using default logger";
	mnk.showWelcomeMessage();

	while(1)
	{
	mnk.readCommand();
	if(!mnk.validityOfUserInput()){
		cout << "invalid\n";
	}
	else{
		cout << mnk.callToLogic();
	}
	}
	 return 0;
	system("pause");	
}

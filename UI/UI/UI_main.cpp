#include "UI.h"
#include <iostream>
#include "LOGIC.h"


int main(){
	UI mnk;
	mnk=UI();
	mnk.showWelcomeMessage();
	mnk.readCommand();
	mnk.determineCommandWordnToDoList();
	if(!mnk.validityOfUserInput()){
		return 0;
	}
	else{
		mnk.callToLogic();// still not sure leh...how to pass to logic
	}

	std::string line;
	if(mnk.isCompletedAction(line)){
		 std::cerr << line << " is completed.\n";
	 }
	 else{
		 std::cerr << "ERROR! " << line << " is not completed.\n";
	 }

	 return 0;
}
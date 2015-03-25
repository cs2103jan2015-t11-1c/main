#include "logic.h"
#include "UI.h"
#include "Storage.h"
#include <iostream>
using namespace std;
#include <cstdlib>

int main(){
	UI mnk;
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

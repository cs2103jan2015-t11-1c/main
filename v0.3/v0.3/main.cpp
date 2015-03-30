//#include "logic.h"
#include "UI.h"
#include <assert.h>
#include <iostream>
using namespace std;
#include <cstdlib>
const static string INVALID_COMMAND_MESSAGE ="Sorry, invalid command.\n";

int main(){
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

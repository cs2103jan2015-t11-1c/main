#include "logic.h"
#include "UI.h"
#include "Storage.h"
#include <assert.h>
#include <iostream>
using namespace std;
#include <cstdlib>

/*void analyze_string( string * string);*/

int main(){
	string msg;
	UI mnk;
	mnk.showWelcomeMessage();

	while(1)
	{
	mnk.readCommand();
	if(mnk.validityOfUserInput()){
		msg = mnk.callToLogic();
		cout << msg;
	}
	/*analyze_string(msg);*/
	}
	 return 0;
	system("pause");	
}
/*
//Test output string to see wether it is NULL or empty.
void analyze_string(string *string){
	assert( string !=NULL);
	assert ( *string != '\0');
}
*/
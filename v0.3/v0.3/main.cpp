//#include "logic.h"
#include "UI.h"
#include <assert.h>
#include <iostream>
using namespace std;
#include <cstdlib>


int main(){
	string msg;
	UI mnk;
	//std::cout <<"main" <<std::endl;
	mnk.showWelcomeMessage();

	while(1)
	{
	mnk.readCommand(); 
	msg = mnk.callToParser();
	cout << msg;
	}
	system("pause");
    return 0;	
}

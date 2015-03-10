
#include "cmdDisplay.h"
#include <list>
#include <iostream>
using namespace std;

//function to display all tasks under the event list
void CmdDisplay::cmdDisplay(){
	list<Event> eventList;
	int i = 1;
	list<Event>::iterator iter;
	for(iter = eventList.begin(); iter != eventList.end(); ++iter){
		cout << i << "." << *iter << endl;
		i++;
	}
	
}

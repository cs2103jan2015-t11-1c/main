#include "cmdDelete.h";
#include "Eventlist.h"
#include <list>
using namespace std;

//function to delete a task
void CmdDelete::cmdDelete(int taskNumber){
	bool isDeleted;
	list<Event> eventList;
	list<Event>::iterator iter = eventList.begin();
	advance(iter,taskNumber-1);
	eventList.erase(iter);
	isDeleted = true;
}

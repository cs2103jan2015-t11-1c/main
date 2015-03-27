#include "cmdClear.h"


cmdClear::cmdClear(void)
{
}


cmdClear::~cmdClear(void)
{
}

//this function clears all events in the storage
string cmdClear::executeClear(){
	_storage.clearActiveEvent();
	_storage.clearDoneEvent();
	string _feedback = "all tasks cleared";
}

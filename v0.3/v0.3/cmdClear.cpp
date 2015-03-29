#include "cmdClear.h"


cmdClear::cmdClear(void)
{
}


cmdClear::~cmdClear(void)
{
}

//this function clears all events in the storage
std::string cmdClear::executeClear(){
	_storage.clearActiveEvent();
	_storage.clearDoneEvent();
	std::string _feedback = "all tasks cleared";
	return _feedback;
}

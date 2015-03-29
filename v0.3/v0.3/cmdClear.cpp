#include "cmdClear.h"


cmdClear::cmdClear(void)
{
}


cmdClear::~cmdClear(void)
{
}

//this function clears all events in the storage
std::string cmdClear::executeClear(Storage& _storage){
	_storage.clearLocalDrive();
	std::string _feedback = "all tasks cleared\n";
	return _feedback;
}

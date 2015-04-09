#include "cmdClear.h"
const static std::string CLEAR_MESSAGE = "all tasks cleared\n\n";

cmdClear::cmdClear(void){
}

cmdClear::~cmdClear(void){
}

//this function clears all events in the storage
std::string cmdClear::executeClear(Storage& _storage){
	_storage.clearActiveEvent();
	_storage.clearDoneEvent();
	_storage.synchronizeDrive();
	return CLEAR_MESSAGE;
}

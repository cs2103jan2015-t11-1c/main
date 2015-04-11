//@author A0114301E
#include "cmdClear.h"
#include "storage.h"
const static std::string CLEAR_MESSAGE = "all tasks cleared\n\n";
const static std::string LOG_CLEAR = "executed clear";

cmdClear::cmdClear(void){
}

cmdClear::~cmdClear(void){
}

//this function clears all events in the storage
std::string cmdClear::executeClear(Storage& _storage){
	_storage.clearActiveEvent();
	_storage.clearDoneEvent();
	_storage.synchronizeDrive();
	Storage storage;
	storage.writeToLogfile("Info",LOG_CLEAR);
	return CLEAR_MESSAGE;
}
;
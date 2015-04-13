//@author A0114301E
#include "cmdClear.h"
#include "Storage\Storage.h"
const static std::string CLEAR_MESSAGE = "all tasks cleared\n\n";
const static std::string LOG_CLEAR = "executed clear";
const static std::string INFO = "Info";

CmdClear::CmdClear(void) {
}

CmdClear::~CmdClear(void) {
}

//this function clears all events in the storage
std::string CmdClear::executeClear(Storage& _storage) {
	_storage.clearActiveEvent();
	_storage.clearDoneEvent();
	_storage.synchronizeDrive();
	
	//logging
	Storage storage;
	storage.writeToLogfile(INFO,LOG_CLEAR);
	return CLEAR_MESSAGE;
};
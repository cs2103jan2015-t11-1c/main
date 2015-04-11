//@author A0115429H
#include "cmdChangeDirectory.h"
const static std::string MESSAGE_CHANGE_DIRECTORY = "Directory is changed to: ";
const static std::string TWO_LINES = "\n\n";

cmdChangeDirectory::cmdChangeDirectory(void){
}

cmdChangeDirectory::~cmdChangeDirectory(void){
}

//Change directory for the local file
std::string cmdChangeDirectory::executecmdChangeDirectory(Storage& _storage){
	std::string directory = _taskName;
	const char * newDirectory = directory.c_str();
	_storage.changeCurrentDirectory(newDirectory);

	_feedback = getFeedback(directory);
	return _feedback;
}

std::string cmdChangeDirectory::getFeedback(std::string directory){
	std::string feedback;
	feedback = MESSAGE_CHANGE_DIRECTORY + directory + TWO_LINES;
	return feedback;
}
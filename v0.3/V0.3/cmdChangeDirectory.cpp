#include "cmdChangeDirectory.h"


cmdChangeDirectory::cmdChangeDirectory(void){
}


cmdChangeDirectory::~cmdChangeDirectory(void){
}

//change directory for the local file
std::string cmdChangeDirectory::executecmdChangeDirectory(Storage& _storage){
	std::string directory = _taskName;
	const char * newDirectory = directory.c_str();
	_storage.changeCurrentDirectory(newDirectory);

	_feedback = getFeedback(directory);
	return _feedback;
}

std::string cmdChangeDirectory::getFeedback(std::string directory){
	std::string feedback;
	feedback = "Directory is changed to: " + directory + "\n\n";
	return feedback;
}
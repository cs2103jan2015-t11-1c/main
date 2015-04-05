#include "cmdChangeDirectory.h"


cmdChangeDirectory::cmdChangeDirectory(void){
}


cmdChangeDirectory::~cmdChangeDirectory(void){
}

std::string cmdChangeDirectory::executecmdChangeDirectory(Storage& _storage){
	std::string directory = _taskName;
	std::cout << " testing" << _taskName << std::endl;
	const char * newDirectory = directory.c_str();
	_storage.changeCurrentDirectory(newDirectory);

	std::string feedback;
	feedback = getFeedback(directory);

	return feedback;
}

std::string cmdChangeDirectory::getFeedback(std::string directory){
	std::string feedback;
	feedback = "Directory is changed to: " + directory + "\n\n";
	return feedback;
}
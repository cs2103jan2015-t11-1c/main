#include "VerificationCommand.h"
#include <cstring>
#include <string>
#include <ctype.h>
using namespace std;

VerificationCommand::VerificationCommand(void)
{
}

VerificationCommand::~VerificationCommand(void)
{
}

string VerificationCommand::lowercaseCommandWord(string commandWord){
	int n = commandWord.size();
	for( int i = 0; i < n; i++){
		if(commandWord[i] <='Z' && commandWord[i] >= 'A'){
			commandWord[i] = commandWord[i] - ('Z'-'z');
		}
	}
  return commandWord;
}

bool VerificationCommand::isValidCommandWord(string commandWord){
	bool isValidCommandWord = false;
	if(commandWord == "add" || commandWord == "delete" || commandWord == "update" || commandWord =="undo" || commandWord =="done" || commandWord == "display" || commandWord =="help" || commandWord =="exit" || commandWord == "clear" || commandWord == "displaydone" || commandWord =="displaytoday"|| commandWord == "search" || commandWord == "changedirectory"){
		isValidCommandWord = true;
	}
	return isValidCommandWord;
}




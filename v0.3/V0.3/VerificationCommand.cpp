//@author A0115253R

#include "VerificationCommand.h"

const static std::string STRING_ADD = "add";
const static std::string STRING_DELETE = "delete";
const static std::string STRING_UPDATE ="update" ;
const static std::string STRING_UNDO = "undo";
const static std::string STRING_DONE = "done";
const static std::string STRING_DISPLAY = "display";
const static std::string STRING_HELP = "help";
const static std::string STRING_EXIT = "exit";
const static std::string STRING_CLEAR = "clear";
const static std::string STRING_DISPLAYDONE = "displaydone";
const static std::string STRING_DISPLAYTODAY = "displaytoday";
const static std::string STRING_DISPLAYTOMORROW = "displaytomorrow";
const static std::string STRING_DISPLAYALL = "displayall";
const static std::string STRING_SEARCH = "search";
const static std::string STRING_CHANGEDIRECTORY = "changedirectory";
const static std::string STRING_REPEAT = "repeat";
const static std::string STRING_REPEATDONE = "repeatdone";
const static std::string STRING_UPDATERECUR = "updaterecur";
const static std::string STRING_DELETERECUR = "deleterecur";

VerificationCommand::VerificationCommand(void) {
}

VerificationCommand::~VerificationCommand(void) {
}

//This method converts uppercase letter in command to lower case letter.
std::string VerificationCommand::lowercaseCommandWord(std::string commandWord) {
	int n = commandWord.size();

	for ( int i = 0; i < n; i++) {
		if (commandWord[i] <= 'Z' && commandWord[i] >= 'A') {
			commandWord[i] = commandWord[i] - ('Z' - 'z');
		}
	}

  return commandWord;
}

//This method checks the validity of user command.
bool VerificationCommand::isValidCommandWord(std::string commandWord) {
	bool isValidCommandWord;
	
	if (commandWord == STRING_ADD || commandWord == STRING_DELETE || commandWord == STRING_UPDATE || commandWord == STRING_UNDO || commandWord == STRING_DONE || commandWord == STRING_DISPLAY  || commandWord == STRING_HELP|| commandWord ==STRING_EXIT || commandWord == STRING_CLEAR|| commandWord == STRING_DELETERECUR || commandWord == STRING_UPDATERECUR ||commandWord == STRING_DISPLAYDONE  || commandWord ==  STRING_DISPLAYTODAY || commandWord == STRING_SEARCH || commandWord == STRING_CHANGEDIRECTORY || commandWord == STRING_REPEAT || commandWord == STRING_REPEATDONE || commandWord == STRING_DISPLAYTOMORROW || commandWord == STRING_DISPLAYALL) {
		isValidCommandWord = true;
	} else {
		isValidCommandWord = false;
	}

	return isValidCommandWord;
}

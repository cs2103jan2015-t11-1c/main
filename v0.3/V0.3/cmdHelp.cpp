//@author A0114301E
#include "cmdHelp.h"
#include <sstream>

const static std::string HELP_ADD = "[1] add <task name> by: date month time\ne.g. add submit report by: 2 mar 1211\n\n";
const static std::string HELP_DELETE = "[2] delete <task number(s)>\ne.g. delete 1   delete 1 2 3\n\n";
const static std::string HELP_DISPLAY = "[3] display undone/done tasks: display/displaydone\ndisplay today's tasks: displaytoday\n\n";
const static std::string HELP_UPDATE = "[4] update <task number> .name new name\ne.g update 1 .name collect homework\n\n";
const static std::string HELP_UPDATE_START = "[5] update <task number> .start new start time\ne.g. update 1 .start 1 Mar 1211\n\n";
const static std::string HELP_UPDATE_CLEAR_START = "[6] update <task number> .clear start\ne.g. update 2 .start 2 march 1211\n\n";
const static std::string HELP_UPDATE_CLEAR_END = "[7] update <task number> .clear end\ne.g. update 2 .end 2 02 1211\n\n";
const static std::string HELP_UPDATE_END = "[8] update <task number> .start new end time\ne.g. update 1 .end 1 mar 1211\n\n";
const static std::string HELP_MARKASDONE = "[9] mark task(s) as done\ne.g. done 1   done 1 2 3\n\n";
const static std::string HELP_UNDO = "[10] undo last action(up to last two actions): undo\n\n";
const static std::string HELP_SEARCH = "[11] search <key words>\ne.g. search homework\n\n";
const static std::string HELP_RECURRING = "[12] repeat <task number> <frequency> <number of repetitions>\ne.g. repeat 1 weekly 13 except 8   repeat 2 monthly 2\n     repeat 3 every mon/Monday/monday\n\n";
const static std::string LINE = "================================================\n";
const static std::string LOG_HELP = "executed help";

cmdHelp::cmdHelp(void){
}

cmdHelp::~cmdHelp(void){
}

//display help for all functions 
std::string cmdHelp::helpMessage(){
	Storage storage;
	storage.writeToLogfile("Info",LOG_HELP);
	return LINE+ HELP_ADD + HELP_DELETE + HELP_DISPLAY + HELP_UPDATE + HELP_UPDATE_START  
		   + HELP_UPDATE_CLEAR_START + HELP_UPDATE_CLEAR_END + HELP_UPDATE_END + HELP_MARKASDONE + HELP_UNDO 
		   + HELP_SEARCH + HELP_RECURRING + LINE;
}
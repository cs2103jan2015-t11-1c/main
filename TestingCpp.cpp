//This TestBuddy program can be used to manipulate text in a file.
//The filename can be given by the user.
//Assume the forms of editing can only be: add lines to the file; 
//display the current content in the file;
//delete a certain line; delete all the content and exit.
//sort the lines in alphabetical order;
//search for certain word in the file

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "TextBuddy.h"

using namespace std;

const string MESSAGE_START = "Welcome to TextBuddy. %s is ready for use";
const string MESSAGE_EMPTY = "%s is empty";
const string MESSAGE_ADDED = "added to %s: \"%s\"";
const string MESSAGE_DELETED = "deleted from %s: \"%s\"";
const string MESSAGE_CLEARED = "all content deleted from %s";
const string MESSAGE_INVALID_FORMAT = "invalid command format";
const string MESSAGE_SORTED = "all content in %s are sorted alphabetically";
const string MESSAGE_NOTFOUND = "word not found in %s";

const int INITIAL_LINENUMBER = 1;
char buffer[500];
vector<string> store;
vector<string> rightLines;

int main(int argc, char* argv[]){
	string fileName;
	//Check the number of parameters
	//Tell the user to enter fileName if the command is entered incorrectly
	if(argc < 2) {
		cerr << "Usage: " << argv[0] << "fileName" << endl;
		return 1;
	}

	fileName = argv[1];
	TextBuddy::displayWelcomeMessage(fileName);

	string userCommand;
	cout << "command: " <<endl;
	while(getline(cin, userCommand)){
		TextBuddy::exercuteUserCommand(fileName, userCommand);
		cout << "command: " <<endl;
	}

	return 0;
}

string TextBuddy::displayWelcomeMessage(string fileName) {
	sprintf_s(buffer, MESSAGE_START.c_str(), fileName.c_str());
	return buffer;
}

//This method is to determine the command type so that the userCommand is ready for further processing
TextBuddy::CommandType TextBuddy::determineCommandType(string command) {
	if (command == "add"){
		return ADD_LINE;
	}
	else if (command == "display") {
		return DISPLAY_ALL;
	}
	else if (command == "delete") {
		return DELETE_LINE;
	}
	else if (command == "clear") {
		return CLEAR_ALL;
	}
	else if (command == "sort"){
		return SORT;
	}
	else if (command == "search"){
		return SEARCH;
	}
	else if (command == "exit") {
		return EXIT;
	}
	else
		return INVALID;
}

//This method takes in user command and then process it accordingly
string TextBuddy::exercuteUserCommand(string fileName, string userCommand) {
	CommandType CommandType;
	string content;
	
	CommandType = determineCommandType(getCommandType(userCommand));
	content = getContent(userCommand);
	
	switch (CommandType)
	{
		case ADD_LINE:
			return addContent(fileName, content);
		
		case DISPLAY_ALL:
			return displayAll(fileName);
		
		case DELETE_LINE:
			return deleteContent(fileName, content);
		
		case CLEAR_ALL:
			return clearAll(fileName);

		case SORT:
			return sortAlphabetical(fileName);

		case SEARCH:
			return searchWord(fileName, content);
		
		case EXIT:
			exit(0);
		
		case INVALID:
			sprintf_s(buffer, MESSAGE_INVALID_FORMAT.c_str());
		    return buffer;
		
		default:
			break;
	}
	
}

string TextBuddy::getCommandType(string userCommand){
	int TEnd;
	TEnd = userCommand.find_first_of(" ");
	
	return userCommand.substr(0, TEnd);
}

string TextBuddy::getContent(string userCommand){
	int TStart;
	TStart = userCommand.find_first_of(" ")+1;

	return userCommand.substr(TStart);
}

//This method is to add in new information to the file and then tell the user that the content is added
string TextBuddy::addContent(string fileName, string content){
	ofstream file;
	file.open(fileName, ios::app);
	file << content <<endl;
	file.close();
    
	sprintf_s(buffer, MESSAGE_ADDED.c_str(), fileName.c_str(), content.c_str());
	return buffer;
}

//This method is to show all the information in the file and empty if nothing is inside the file
string TextBuddy::displayAll(string fileName){
	ifstream file;
	file.open(fileName);

	string line;
	int lineNumber = INITIAL_LINENUMBER;
	
	while(getline(file, line)){
		cout << lineNumber << ". " << line << endl;
		lineNumber++;
	}

	if(lineNumber == INITIAL_LINENUMBER){
		sprintf_s(buffer, MESSAGE_EMPTY.c_str(), fileName.c_str());
		return buffer;
	}

	file.close();

	return"";
}

//This method is to delete a certain information that provided by the user and then tell user that it is deleted
string TextBuddy::deleteContent(string fileName, string content){
	int lineNumber = stoi(content);
	
	ifstream originalFile;
	originalFile.open(fileName);
	
	ofstream modifiedFile;
	modifiedFile.open("TFile.txt");
	
	string TLine;
	string deletedLine;
	int TCount = 1;
	
	while(getline(originalFile, TLine)){
		if (TCount == lineNumber){
			deletedLine = TLine;
		}
		else{
			modifiedFile << TLine << endl;
		}
		TCount++;
	}
	
	originalFile.close();
	modifiedFile.close();
	
	remove(fileName.c_str());
	rename("TFile.txt", fileName.c_str());
	
	sprintf_s(buffer, MESSAGE_DELETED.c_str(), fileName.c_str(), deletedLine.c_str());
    return buffer;
}

//This method is to clear all the information in the file
string TextBuddy::clearAll(string fileName){
	ifstream file;
	file.open("TFile.txt");
	file.close();
	
	remove(fileName.c_str());
	rename("TFile.txt", fileName.c_str());
	
	sprintf_s(buffer, MESSAGE_CLEARED.c_str(), fileName.c_str());
    return buffer;
}

//This method is to sort the content alphabetically
//First change file to vector and then back to file
string TextBuddy::sortAlphabetical(string fileName){
	TextBuddy::storeFileinVector(fileName);
	
	stable_sort(store.begin(), store.end());

	TextBuddy::writeToFile(fileName);

	sprintf_s(buffer, MESSAGE_SORTED.c_str(), fileName.c_str());
	return buffer;
}

//This method is to store the content of file in a vector
void TextBuddy::storeFileinVector(string fileName){
	ifstream file;
	string Tline;

	file.open(fileName);

	while (getline(file, Tline)) {
		store.push_back(Tline);
	}

	file.close();
	return;
}

// This method is to convert strings in vector back to file
void TextBuddy::writeToFile(string filename) {
	ofstream file;

	file.open(filename);
	file.close();
	
	for (vector<string>::iterator Tcount = store.begin(); Tcount != store.end(); Tcount++) {
		file.open(filename, ios::app);
		file << *Tcount << endl;
		file.close();
	}

	return;
}

//This method is to search the word in the file
//If found, the lines containing the word will be printed out
//If not found, a message showing not found will be printed out
string TextBuddy::searchWord(string fileName, string word){
	TextBuddy::storeFileinVector(fileName);

	bool isFound = TextBuddy::getRightLines(store, word);

	if(isFound){
		TextBuddy::printRightLines(rightLines);
	}else {
		sprintf_s(buffer, MESSAGE_NOTFOUND.c_str(), fileName.c_str());
		return buffer;
	}

	return"";
}

//This method is to check what are the lines contain the word if any
bool TextBuddy::getRightLines(vector<string> store, string word){
	bool isFound = false;
	int Tindex;

	for (Tindex = 0; Tindex < store.size(); Tindex++){
		if(isContainingWord(store[Tindex], word)){
			isFound = true;
			rightLines.push_back(store[Tindex]);
		}
	}

	return isFound;
}

//This method is to check whether a certain line contains the word
bool TextBuddy::isContainingWord(string line, string word){
	bool isContaining = false;

	if(line.find(word) != string::npos){
		isContaining = true;
	}

	return isContaining;
}

//This method is to print out the lines contain the word
void TextBuddy::printRightLines(vector<string> rightLines){
	int Tindex;

	for(Tindex = 0; Tindex < rightLines.size(); Tindex++){
		cout << "word found in: " << rightLines[Tindex] << endl;
	}

	return;
}
//By Ren Xiaokai A0116455
//The following solution allows user to define a file to store the text to be added
//Each text is added immediately after a user action that make modification to the file

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <vector>

char buffer[1000];
const std::string WELCOME_MESSAGE = "Welcome to TextBuddy. %s is ready for use";
const std::string MESSAGE_ADDED = "added to %s: \"%s\"";
const std::string MESSAGE_DELETED = "deleted from %s: \"%s\"";
const std::string MESSAGE_CLEARED = "all content deleted from %s";
const std::string MESSAGE_EMPTY = "%s is empty";

void displayText(std::string fileName);
void displayMessage(std::string message);
void writeFile(std::string message, std::string fileName);
void addText(std::string fileName);
void deleteText(std::string fileName);
void clearText(std::string fileName);

int main(int argc, char* argv[])
{
	std::string fileName=argv[1];
	
	sprintf_s(buffer, WELCOME_MESSAGE.c_str(), fileName.c_str());
	displayMessage(buffer);
	
	std::string currentCommand;
	std::cout << "command: " << std::endl;
	std::cin >> currentCommand;
	
	while (currentCommand != "exit"){
		if (currentCommand == "add"){
			addText(fileName);
		}
		else if (currentCommand == "display"){
			displayText(fileName);
		}
		else if (currentCommand == "delete"){
			deleteText(fileName);
		} 
		else if (currentCommand == "clear"){
			clearText(fileName);
		}
		else if (currentCommand != "exit"){
		std::cout << "invalid command" << std::endl;
		}

		std::cout << "command: " << std::endl;
		std::cin >> currentCommand;
		}
	
	return 0;	
}
void addText(std::string fileName){
	std::string firstWord;
	std::string remainingWords;
	std::string wholePhrase;
	std::cin >> firstWord;
	std::getline(std::cin, remainingWords);
	wholePhrase = firstWord + remainingWords;
	sprintf_s(buffer, MESSAGE_ADDED.c_str(), fileName.c_str(), wholePhrase.c_str());
	displayMessage(buffer);
	writeFile(wholePhrase, fileName);

}

void clearText(std::string fileName){
	std::ofstream ofsFile;
	ofsFile.open(fileName);
	ofsFile.close();

	sprintf_s(buffer, MESSAGE_CLEARED.c_str(), fileName.c_str());
	displayMessage(buffer);

}

void deleteText(std::string fileName){
	int index;
	std::cin >> index;
	std::vector<std::string> textInFile;
	std::string currentLine;
	std::string deletedLine;
	std::ifstream ifsFile;
	std::ofstream ofsFile;

	ifsFile.open(fileName);
	while (std::getline(ifsFile, currentLine)){
		textInFile.push_back(currentLine);
	}

	ifsFile.close();
	ofsFile.open(fileName);

	for (unsigned int i = 0; i < textInFile.size(); i++){
		if (i == index - 1){
			deletedLine = textInFile[i];
		}
		else {
			ofsFile << textInFile[i] << std::endl;
		}
	}
	ofsFile.close();

	sprintf_s(buffer, MESSAGE_DELETED.c_str(), fileName.c_str(), deletedLine.c_str());
	displayMessage(buffer);

}

void displayText(std::string fileName){
	std::ifstream textFile;
	std::string currentLine;

	textFile.open(fileName);
	int i;
	for (i = 1; std::getline(textFile, currentLine); i++){
		std::cout << i << "." <<currentLine <<std::endl;
	}

	if (i == 1 ){
		sprintf_s(buffer, MESSAGE_EMPTY.c_str(), fileName.c_str());
		displayMessage(buffer);
		return;
	}
	textFile.close();

}

void displayMessage(std::string message) {
	std::cout << message << std::endl;
		
}

void writeFile(std::string message, std::string fileName){
	std::ofstream destination;

	destination.open(fileName, std::ofstream::app);
	destination << message << std::endl;
	destination.close();

}



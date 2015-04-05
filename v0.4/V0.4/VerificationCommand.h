#pragma once
#include <string>
using namespace std;

class VerificationCommand
{
public:
	VerificationCommand(void);
	~VerificationCommand(void);
	string lowercaseCommandWord(string);
	bool isValidCommandWord(string);
};


//@author A0115253R

#pragma once
#ifndef VERIFICATIONCOMMAD_H
#define VERIFICATIONCOMMAND_H
#include <string>
#include <cstring>
#include <ctype.h>
#include <assert.h>

class VerificationCommand
{
public:
	VerificationCommand(void);
	~VerificationCommand(void);
	std::string lowercaseCommandWord(std::string);
	bool isValidCommandWord(std::string);
};

#endif


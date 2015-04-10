#include "stdafx.h"
#include "CppUnitTest.h"
#include "VerificationCommand.h"
#include "VerificationDateTimeMonth.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
const static std::string STRING_SEARCH = "search";
const static std::string STRING_CHANGEDIRECTORY = "changedirectory";
const static std::string STRING_REPEAT = "repeat";
const static std::string STRING_REPEATDONE = "repeatdone";
namespace UnitTest1
{
	TEST_CLASS(VerificationCommandTest)
	{
	public:

		//test if command input is valid
		//partition into valid cases and invalid cases
		TEST_METHOD(isValidCommandWord)
		{
			VerificationCommand verifyCommand;
			bool expectedOne = true;
			bool actualOne = verifyCommand.isValidCommandWord(STRING_ADD);
			Assert::AreEqual(expectedOne, actualOne);
			bool expectedTwo = true;
			bool actualTwo = verifyCommand.isValidCommandWord(STRING_CHANGEDIRECTORY);
			Assert::AreEqual(expectedTwo, actualTwo);
			bool expectedThree = true;
			bool actualThree = verifyCommand.isValidCommandWord(STRING_CLEAR);
			Assert::AreEqual(expectedThree, actualThree);
			bool expectedFour = true;
			bool actualFour = verifyCommand.isValidCommandWord(STRING_DELETE);
			Assert::AreEqual(expectedFour, actualFour);
			bool expectedFive = true;
			bool actualFive = verifyCommand.isValidCommandWord(STRING_DISPLAY);
			Assert::AreEqual(expectedFive, actualFive);
			bool expectedSix = true;
			bool actualSix = verifyCommand.isValidCommandWord(STRING_DISPLAYDONE);
			Assert::AreEqual(expectedSix, actualSix);
			bool expectedSeven = true;
			bool actualSeven  = verifyCommand.isValidCommandWord(STRING_DONE);
			Assert::AreEqual(expectedSeven , actualSeven );
			bool expectedEight = true;
			bool actualEight = verifyCommand.isValidCommandWord(STRING_EXIT);
			Assert::AreEqual(expectedEight, actualEight);
			bool expectedNine = true;
			bool actualNine  = verifyCommand.isValidCommandWord(STRING_HELP);
			Assert::AreEqual(expectedNine , actualNine );
			bool expectedTen = true;
			bool actualTen = verifyCommand.isValidCommandWord(STRING_REPEAT);
			Assert::AreEqual(expectedTen, actualTen);
			bool expectedEleven = true;
			bool actualEleven = verifyCommand.isValidCommandWord(STRING_REPEATDONE);
			Assert::AreEqual(expectedEleven, actualEleven);
			bool expectedTweleve = true;
			bool actualTweleve  = verifyCommand.isValidCommandWord(STRING_SEARCH);
			Assert::AreEqual(expectedTweleve, actualTweleve );
			bool expectedThirteen = true;
			bool actualThirteen = verifyCommand.isValidCommandWord(STRING_UNDO);
			Assert::AreEqual(expectedThirteen, actualThirteen);
			bool expectedFourteen = true;
			bool actualFourteen = verifyCommand.isValidCommandWord(STRING_UPDATE);
			Assert::AreEqual(expectedFourteen, actualFourteen);
			bool actualFalse = verifyCommand.isValidCommandWord("test");
			bool expectedFalse = false;
			Assert::AreEqual(expectedFalse, actualFalse);
		}

		//test converting upper case into lower case
		TEST_METHOD(lowerCaseCommandWord)
		{
			VerificationCommand verification;
			string actualOne = verification.lowercaseCommandWord("ADD");
			string expectedOne = "add";
			Assert::AreEqual(expectedOne,actualOne);
			string actualTwo = verification.lowercaseCommandWord("Delete");
			string expectedTwo = "delete";
			Assert::AreEqual(expectedTwo,actualTwo);
			string actualThree = verification.lowercaseCommandWord("clear");
			string expectedThree= "clear";
			Assert::AreEqual(expectedThree,actualThree);

		}

	};

TEST_CLASS(VerificationDateTimeMonthTest)
	{
	public:
		
		//test converting lower case for month to lower case
		TEST_METHOD(lowerCaseMonth)
		{
			VerificationDateTimeMonth verify;
			string actualOne = verify.lowercaseMonth("Jan");
			string expectedOne = "jan";
			Assert::AreEqual(actualOne, expectedOne);
			string actualTwo = verify.lowercaseMonth("FEB");
			string expectedTwo = "feb";
			Assert::AreEqual(actualTwo, expectedTwo);
			string actualThree = verify.lowercaseMonth("MArch");
			string expectedThree = "march";
			Assert::AreEqual(actualThree, expectedThree);
			string actualFour = verify.lowercaseMonth("april");
			string expectedFour = "april";
			Assert::AreEqual(actualFour, expectedFour);
			string actualFive = verify.lowercaseMonth("MaY");
			string expectedFive = "may";
			Assert::AreEqual(actualFive, expectedFive);
			string actualSix = verify.lowercaseMonth("juNe");
			string expectedSix = "june";
			Assert::AreEqual(actualSix, expectedSix);
			string actualSeven = verify.lowercaseMonth("jul");
			string expectedSeven = "jul";
			Assert::AreEqual(actualSeven, expectedSeven);
			string actualEight = verify.lowercaseMonth("AugUST");
			string expectedEight = "aug";
			Assert::AreEqual(actualEight, expectedEight);
			string actualNine = verify.lowercaseMonth("SEP");
			string expectedNine = "sep";
			Assert::AreEqual(actualNine, expectedNine);
			string actualTen = verify.lowercaseMonth("oct");
			string expectedTen = "oct";
			Assert::AreEqual(actualTen, expectedTen);
			string actualEleven = verify.lowercaseMonth("NOv");
			string expectedEleven = "nov";
			Assert::AreEqual(actualEleven, expectedEleven);
			string actualTweleve = verify.lowercaseMonth("Dec");
			string expectedTweleve = "Dec";
			Assert::AreEqual(actualTweleve, expectedTweleve);
		}

};
}

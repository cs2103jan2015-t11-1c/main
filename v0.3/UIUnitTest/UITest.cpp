//@author A0115253R

#include "stdafx.h"
#include "CppUnitTest.h"

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
std::string welcomemsg = "================================================\nWelcome to Minik!What would you like to do today?\n================================================\n\n";

namespace UIUnitTest
{		
	TEST_CLASS(UnitTestUI)
	{
	private:

		UI uiObject;

	public:
		
		TEST_METHOD(isEmpty)
		{
			std::string emptyString = "";
			std::string blankString = "  ";
			std::string nonEmptyString = "This string is not empty.";

			Assert::IsTrue (uiObject.UI::isEmpty(emptyString));
			Assert::IsTrue (uiObject.UI::isEmpty(blankString));
			Assert::IsFalse (uiObject.UI::isEmpty(nonEmptyString));
		}
		
		TEST_METHOD(showWelcomeMessage)
		{
			Assert::AreEqual(welcomemsg, uiObject.UI::showWelcomeMessage());
		}

		TEST_METHOD(getTheToDoListWithIndexZeroNotEmpty)
		{
			std::string indexZeroWhiteSpaceString = "   Index Zero to Two are white space for this string.";
			std::string expectedString = "Index Zero to Two are white space for this string.";
			uiObject.UI::setValueForAttributes(STRING_ADD, indexZeroWhiteSpaceString);
			uiObject.UI::getTheToDoListWithIndexZeroNotEmpty();
			Assert::AreEqual(expectedString, uiObject.UI::getToDoList());
		}

		TEST_METHOD(determineCommandType)
		{
			int actualCommand;
			int expectedCommand;
			std::string emptyString = "";

			expectedCommand = UI::ADD;
			uiObject.UI::setValueForAttributes(STRING_ADD, emptyString);
			actualCommand = uiObject.UI::determineCommandType();
			Assert::AreEqual(expectedCommand, actualCommand);

			expectedCommand = UI::DELETE;
			uiObject.UI::setValueForAttributes(STRING_DELETE, emptyString);
			actualCommand = uiObject.UI::determineCommandType();
			Assert::AreEqual(expectedCommand, actualCommand);

			expectedCommand = UI::UPDATE;
			uiObject.UI::setValueForAttributes(STRING_UPDATE, emptyString);
			actualCommand = uiObject.UI::determineCommandType();
			Assert::AreEqual(expectedCommand, actualCommand);

			expectedCommand = UI::DISPLAY;
			uiObject.UI::setValueForAttributes(STRING_DISPLAY, emptyString);
			actualCommand = uiObject.UI::determineCommandType();
			Assert::AreEqual(expectedCommand, actualCommand);

			expectedCommand = UI::CLEAR;
			uiObject.UI::setValueForAttributes(STRING_CLEAR, emptyString);
			actualCommand = uiObject.UI::determineCommandType();
			Assert::AreEqual(expectedCommand, actualCommand);

			expectedCommand = UI::EXIT;
			uiObject.UI::setValueForAttributes(STRING_EXIT, emptyString);
			actualCommand = uiObject.UI::determineCommandType();
			Assert::AreEqual(expectedCommand, actualCommand);

			expectedCommand = UI::DONE;
			uiObject.UI::setValueForAttributes(STRING_DONE, emptyString);
			actualCommand = uiObject.UI::determineCommandType();
			Assert::AreEqual(expectedCommand, actualCommand);

			expectedCommand = UI::DISPLAYDONE;
			uiObject.UI::setValueForAttributes(STRING_DISPLAYDONE, emptyString);
			actualCommand = uiObject.UI::determineCommandType();
			Assert::AreEqual(expectedCommand, actualCommand);

			expectedCommand = UI::DISPLAYTODAY;
			uiObject.UI::setValueForAttributes(STRING_DISPLAYTODAY, emptyString);
			actualCommand = uiObject.UI::determineCommandType();
			Assert::AreEqual(expectedCommand, actualCommand);

			expectedCommand = UI::UNDO;
			uiObject.UI::setValueForAttributes(STRING_UNDO, emptyString);
			actualCommand = uiObject.UI::determineCommandType();
			Assert::AreEqual(expectedCommand, actualCommand);

			expectedCommand = UI::SEARCH;
			uiObject.UI::setValueForAttributes(STRING_SEARCH, emptyString);
			actualCommand = uiObject.UI::determineCommandType();
			Assert::AreEqual(expectedCommand, actualCommand);

			expectedCommand = UI::CHANGEDIRECTORY;
			uiObject.UI::setValueForAttributes(STRING_CHANGEDIRECTORY, emptyString);
			actualCommand = uiObject.UI::determineCommandType();
			Assert::AreEqual(expectedCommand, actualCommand);

			expectedCommand = UI::REPEAT;
			uiObject.UI::setValueForAttributes(STRING_REPEAT, emptyString);
			actualCommand = uiObject.UI::determineCommandType();
			Assert::AreEqual(expectedCommand, actualCommand);

			expectedCommand = UI::REPEATDONE;
			uiObject.UI::setValueForAttributes(STRING_REPEATDONE, emptyString);
			actualCommand = uiObject.UI::determineCommandType();
			Assert::AreEqual(expectedCommand, actualCommand);

		}
	};
}

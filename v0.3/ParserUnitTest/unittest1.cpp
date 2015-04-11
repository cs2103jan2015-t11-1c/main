//@author A0115253R
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserUnitTest
{		
	TEST_CLASS(ParserUnitTest)
	{
	private:
		Parser parserObject;
	public:
		
		TEST_METHOD(isValidIndex)
		{
			string str = "No_White_Space_String.";
			int invalidIndex = str.find_first_of(" ");
			int validIndex = str.find_first_of("_");
			Assert::IsTrue (parserObject.isValidIndex(validIndex));
			Assert::IsFalse (parserObject.isValidIndex(invalidIndex));
		}

		TEST_METHOD(isStringAnInteger)
		{
			string integerString = "12345";
			string nonIntegerString = "abcd";
			Assert::IsTrue (parserObject.isStringAnInteger(integerString));
			Assert::IsFalse (parserObject.isStringAnInteger(nonIntegerString));
		}

		TEST_METHOD(isAbleToGetNumberList)
		{
			string validStringNumberList = "1  2   3      ";
			string invalidStringNumberList = "a b c";
			Assert::IsTrue (parserObject.isAbleToGetNumberList(validStringNumberList));
			Assert::IsFalse (parserObject.isAbleToGetNumberList(invalidStringNumberList));
		}

		TEST_METHOD(isTaskWithDeadline)
		{
			string taskWithDeadline = "finish report by: 22 03 2011";
			string floatingTask = "finish report";
			string timedTask = "meeting from: 02 03 1300 to: 02 03 1500 ";

			Assert::IsTrue (parserObject.isTaskWithDeadline(taskWithDeadline));
			Assert::IsFalse (parserObject.isTaskWithDeadline(floatingTask));
			Assert::IsFalse (parserObject.isTaskWithDeadline(timedTask));
		}

		TEST_METHOD(isTimedTask)
		{
			string taskWithDeadline = "finish report by: 22 03 2011";
			string floatingTask = "finish report";
			string timedTask = "meeting from: 02 03 1300 to: 02 03 1500 ";

			Assert::IsTrue (parserObject.isTimedTask(timedTask));
			Assert::IsFalse (parserObject.isTimedTask(floatingTask));
			Assert::IsFalse (parserObject.isTimedTask(taskWithDeadline));
		}

		TEST_METHOD(convertStringToInteger)
		{
			string str = "123";
			int expected = 123;
			int actual = parserObject.convertStringToInteger(str);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(isAbleToGetEventDateAndMonth)
		{
			int date;
			MonthType month;
			string validString = "02 03 0000";
			string invalidDateString = "second 03 0000";
			string lackOfDateOrMonth = "02 0000  ";
			Assert::IsTrue (parserObject.isAbleToGetEventDateAndMonth(validString, date, month));
			Assert::IsFalse (parserObject.isAbleToGetEventDateAndMonth(invalidDateString, date, month));
			Assert::IsFalse (parserObject.isAbleToGetEventDateAndMonth(lackOfDateOrMonth, date, month));
		}

		TEST_METHOD(VerifyAllAttributesAndCallLogic)
		{
			Parser::CommandType command = Parser::ADDEVENTWITHDEADLINE;
			string notAssignedTime = "2400";
			int notAssignedDate = 0;
			int invalidDate_Dec = 32;
			MonthType Month_Dec = DECEMBER;
			list<int> emptyList;
			string taskName = "meeting";
			string validTime = "2359";
			string invalidTime = "2400";
			int validDate_Dec = 31;
			string INVALID_MESSAGE = "Please check your user input time, date and month.\n\n";

			parserObject.setAttributes(taskName, notAssignedTime, validTime, notAssignedDate, invalidDate_Dec, MONTHNOTASSIGNED, DECEMBER, emptyList);
			Assert::AreEqual(INVALID_MESSAGE, parserObject.VerifyAllAttributesAndCallLogic(command));
		    
			parserObject.setAttributes(taskName, notAssignedTime, invalidTime, notAssignedDate, validDate_Dec, MONTHNOTASSIGNED, DECEMBER, emptyList);
			Assert::AreEqual(INVALID_MESSAGE, parserObject.VerifyAllAttributesAndCallLogic(command));

			parserObject.setAttributes(taskName, notAssignedTime, validTime, notAssignedDate, validDate_Dec, MONTHNOTASSIGNED, MONTHNOTASSIGNED, emptyList);
			Assert::AreEqual(INVALID_MESSAGE, parserObject.VerifyAllAttributesAndCallLogic(command));

			parserObject.setAttributes(taskName, notAssignedTime, validTime, notAssignedDate, validDate_Dec, MONTHNOTASSIGNED, DECEMBER, emptyList);
			Assert::AreNotEqual(INVALID_MESSAGE, parserObject.VerifyAllAttributesAndCallLogic(command));
		
		}
		TEST_METHOD(getIndexOfFirstNonWhiteSpace)
		{
			std::string emptyString = "";
			int indexEmptyString = emptyString.find_first_not_of(" ");
			Assert::AreEqual(indexEmptyString, parserObject.getIndexOfFirstNonWhiteSpace(emptyString));

			std::string stringOne = "CS meeting";
			int indexStringOne = stringOne.find_first_not_of(" ");
			Assert::AreEqual(indexStringOne, parserObject.getIndexOfFirstNonWhiteSpace(stringOne));

			std::string stringTwo = "  project due";
			int indexStringTwo = stringTwo.find_first_not_of(" ");
			Assert::AreEqual(indexStringTwo, parserObject.getIndexOfFirstNonWhiteSpace(stringTwo));
		}

		TEST_METHOD(getIndexOfFirstWhiteSpace)
		{
			std::string emptyString = "";
			int indexEmptyString = emptyString.find_first_of(" ");
			Assert::AreEqual(indexEmptyString, parserObject.getIndexOfFirstWhiteSpace(emptyString));

			std::string stringOne = "CS meeting";
			int indexStringOne = stringOne.find_first_of(" ");
			Assert::AreEqual(indexStringOne, parserObject.getIndexOfFirstWhiteSpace(stringOne));

			std::string stringTwo = "  project due";
			int indexStringTwo = stringTwo.find_first_of(" ");
			Assert::AreEqual(indexStringTwo, parserObject.getIndexOfFirstWhiteSpace(stringTwo));
		}


	};
}

/*
string validDateMonth_Jan = "31 01 0000";
			string invalidDate_Jan = "32 01 0000";
			string validDateMonth_Feb = "29 feburary 0000";
			string invalidDate_Feb = "30 02 0000";
			string validDateMonth_Mar = "31 Mar 0000";
			string invalidDate_Mar = "32 03 0000";
			string validDateMonth_Apr = "30 APRIL 0000";
			string invalidDate_Apr = " 31 04 0000";
			string validDateMonth_May = "31 may 0000";
			string invalidDate_May = "32 05 0000";
			string validDateMonth_Jun = "30 jun 0000";
			string invalidDate_Jun = "31 06 0000";
			string validDateMonth_Jul = "31 jUlY 0000";
			string invalidDate_Jul = "32 07 0000";
			string validDateMonth_Aug = "31 AUG 0000";
			string invalidDate_Aug = "32 08 0000";
			string validDateMonth_Sep ="30 sep 0000";

*/

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RepeatUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		cmdRepeat _repeat;
		TEST_METHOD(isWeekday)
		{
			std::string repeatCommand1 = "MONDAY";
			std::string repeatCommand2 = "Tuesday";
			std::string repeatCommand3 = "Wed";
			std::string repeatCommand4 = "Thud";
			bool isWeekday1 = _repeat.isWeekday(repeatCommand1);
			bool expected1 = true;
			Assert::AreEqual(expected1, isWeekday1);
			bool isWeekday2 = _repeat.isWeekday(repeatCommand2);
			bool expected2 = true;
			Assert::AreEqual(expected2, isWeekday2);
			bool isWeekday3 = _repeat.isWeekday(repeatCommand3);
			bool expected3 = true;
			Assert::AreEqual(expected3, isWeekday3);
			bool isWeekday4 = _repeat.isWeekday(repeatCommand4);
			bool expected4 = false;
			Assert::AreEqual(expected4, isWeekday4);
		}

		TEST_METHOD(isValidDate)
		{
			bool isValid1 = _repeat.isValidDate(29, 2, 2015);
			bool expected1 = false;
			Assert::AreEqual(expected1, isValid1);
			bool isValid2 = _repeat.isValidDate(29, 2, 2016);
			bool expected2 = true;
			Assert::AreEqual(expected2, isValid2);
			bool isValid3 = _repeat.isValidDate(30, 1, 2015);
			bool expected3 = true;
			Assert::AreEqual(expected3, isValid3);
		}
		
		TEST_METHOD(isExceptionDay)
		{
			bool isExceptionDay1 = _repeat.isExceptionDay(11, 4, 2015, 5);
			bool expected1 = true;
			Assert::AreEqual(expected1, isExceptionDay1);
			bool isExceptionDay2 = _repeat.isExceptionDay(11, 4, 2016, 5);
			bool expected2 = false;
			Assert::AreEqual( expected2, isExceptionDay2);
		}

		TEST_METHOD(determineWeekday)
		{
			std::string repeatCommand1 = "monday";
			int output1 = _repeat.determineWeekday(repeatCommand1);
			int expected1 = 0;
			Assert::AreEqual(expected1, output1);

		}
	};
}
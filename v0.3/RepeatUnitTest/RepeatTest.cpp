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
			Assert::AreEqual(isValid1, expected1);
			bool isValid2 = _repeat.isValidDate(29, 2, 2016);
			bool expected2 = true;
			Assert::AreEqual(isValid2, expected2);
			bool isValid3 = _repeat.isValidDate(30, 1, 2015);
			bool expected3 = true;
			Assert::AreEqual(isValid3, expected3);
		}

	};
}
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

		TEST_METHOD(isDefaultRepeatTimes)
		{
			int repeatTime1 = 0;
			bool isDefault1 = _repeat.isDefaultRepeatTimes(repeatTime1);
			bool expected1 = true;
			Assert::AreEqual(expected1, isDefault1);
			int repeatTime2 = 10;
			bool isDefault2 = _repeat.isDefaultRepeatTimes(repeatTime2);
			bool expected2 = false;
			Assert::AreEqual(expected2, isDefault2);
		}

		//Test for an invalid Feb date in a nonleap year
		//a valid Feb date in a leap year
		//and a normal valid date
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
			std::string repeatCommand2 = "tue";
			int output2 = _repeat.determineWeekday(repeatCommand2);
			int expected2 = 1;
			Assert::AreEqual(expected2, output2);
		}

		TEST_METHOD(getWeekdayToday)
		{
			findNextDate _findNextDate;
			int weekday1 = _repeat.getWeekdayToday(11, 4, 2015);
			int expected1 = 5;
			Assert::AreEqual(expected1, weekday1);
			int weekday2 = _repeat.getWeekdayToday(11, 4, 2016);
			int expected2 = 0;
			Assert::AreEqual(expected2, weekday2);
		}

		TEST_METHOD(changeWeekdayToInteger)
		{
			std::string string1 = "MONDAY";
			int weekday1 = _repeat.changeWeekdayToInteger(string1);
			int expected1 = 0;
			Assert::AreEqual(expected1, weekday1);
			std::string string2 = "Tuesday";
			int weekday2 = _repeat.changeWeekdayToInteger(string2);
			int expected2 = 1;
			Assert::AreEqual(expected2, weekday2);
			std::string string3 = "WED";
			int weekday3 = _repeat.changeWeekdayToInteger(string3);
			int expected3 = 2;
			Assert::AreEqual(expected3, weekday3);
			std::string string4 = "thur";
			int weekday4 = _repeat.changeWeekdayToInteger(string4);
			int expected4 = 3;
			Assert::AreEqual(expected4, weekday4);
			std::string string5 = "friday";
			int weekday5 = _repeat.changeWeekdayToInteger(string5);
			int expected5 = 4;
			Assert::AreEqual(expected5, weekday5);
			std::string string6 = "SAT";
			int weekday6 = _repeat.changeWeekdayToInteger(string6);
			int expected6 = 5;
			Assert::AreEqual(expected6, weekday6);	
			std::string string7 = "SunDay";
			int weekday7 = _repeat.changeWeekdayToInteger(string7);
			int expected7 = 6;
			Assert::AreEqual(expected7, weekday7);
		}

		TEST_METHOD(getExceptionTime)
		{
			std::string exception1 = "friday";
			int exceptionTime1 = _repeat.getExceptionTime(exception1);
			int expected1 = 4;
			Assert::AreEqual(expected1, exceptionTime1);
			std::string exception2 = "2";
			int exceptionTime2 = _repeat.getExceptionTime(exception2);
			int expected2 = 2;
			Assert::AreEqual(expected2, exceptionTime2);
		}

		TEST_METHOD(getNumberOfDays)
		{
			int year = 2015;
			int month1 = 1;
			int numberOfDays1 = _repeat.getNumberOfDays(month1, year);
			int expected1 = 31;
			Assert::AreEqual(expected1, numberOfDays1);
			int month2 = 2;
			int numberOfDays2 = _repeat.getNumberOfDays(month2, year);
			int expected2 = 28;
			Assert::AreEqual(expected2, numberOfDays2);
			int month3 = 4;
			int numberOfDays3 = _repeat.getNumberOfDays(month3, year);
			int expected3 = 30;
			Assert::AreEqual(expected3, numberOfDays3);
		}
	};
}
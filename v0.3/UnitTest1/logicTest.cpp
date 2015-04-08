//@author A0114301E
#include "stdafx.h"
#include "CppUnitTest.h"
#include "../V0.3/cmdAdd.h"
#include "../V0.3/Storage.h"
#include "../V0.3//Parser.h"
#include "../V0.3/Eventlist.h"
#include "../V0.3/cmdRepeatParser.h"
#include "../V0.3/cmdRepeat.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const static std::string HELP_ADD = "1.add <task name> by: date month time\ne.g. add submit report by: 2 mar 1211\n\n";
const static std::string HELP_DELETE = "2.delete <task number(s)>\ne.g. delete 1   delete 1 2 3\n\n";
const static std::string HELP_DISPLAY = "3.display undone/done tasks: display/displaydone\ndisplay today's tasks: displaytoday\n\n";
const static std::string HELP_UPDATE = "4.update <task number> .name new name\ne.g update 1 .name collect homework\n\n";
const static std::string HELP_UPDATE_START = "5.update <task number> .start new start time\ne.g. update 1 .start 1 Mar 1211\n\n";
const static std::string HELP_UPDATE_CLEAR_START = "6.update <task number> .clear start\ne.g. update 2 .start 2 march 1211\n\n";
const static std::string HELP_UPDATE_CLEAR_END = "7.update <task number> .clear end\ne.g. update 2 .end 2 02 1211\n\n";
const static std::string HELP_UPDATE_END = "8.update <task number> .start new end time\ne.g. update 1 .end 1 mar 1211\n\n";
const static std::string HELP_MARKASDONE = "9.mark task(s) as done\ne.g. done 1   done 1 2 3\n\n";
const static std::string HELP_UNDO = "10.undo last action(up to last two actions): undo\n\n";
const static std::string HELP_SEARCH = "11.search <key words>\ne.g. search homework\n\n";
const static std::string HELP_RECURRING = "12.repeat <task number> <frequency> <number of repetitions>\ne.g. repeat 1 weekly 13 except 8   repeat 2 monthly 2\n\n";
const static std::string LINE = "================================================\n";

namespace UnitTest1
{		
	//@author A0114301E
	TEST_CLASS(UnitTest1)
	{
	public:

		//test for adding a task with a deadline
		TEST_METHOD(addWithDeadline)
		{
			std::string _taskname = "task";
			int _endingDay = 1;
			int _endingMonth = 1;
			int _endingTime = 1123;
			Storage _storage;
			cmdAdd _add;
			logic logic;
			Event _newEvent(_taskname, _endingDay, _endingMonth,_endingTime);
			std::string output = _add.addEventWithDeadline(_storage);
			std::string expected = "\"[---------------------------] \" is added successfully.\n\n";
			Assert::AreEqual(expected, output);
		}

		//test for adding a floating task
		TEST_METHOD(addWithoutDeadline)
		{
			std::string _taskname = "task";
			int _endingDay = 0;
			int _endingMonth = 13;
			int _endingTime = 2400;
			Storage _storage;
			cmdAdd _add;
			logic logic;
			Event _newEvent(_taskname, _endingDay, _endingMonth,_endingTime);
			std::string output = _add.addEventWithoutDeadline(_storage);
			std::string expected = "\"[---------------------------] \" is added successfully.\n\n";;
			Assert::AreEqual(expected, output);
		}

		TEST_METHOD(addTimedEvent)
		{
			std::string _taskname = "task";
			int _endingDay = 0;
			int _endingMonth = 13;
			int _endingTime = 2400;
			int _startingDay = 0;
			int _startingMonth = 13;
			int _startingTime = 2400;
			Storage _storage;
			cmdAdd _add;
			logic logic;
			Event _newEvent(_taskname, _endingDay, _endingMonth,_endingTime);
			std::string output = _add.addTimedEvent(_storage);
			std::string expected = "\"[---------------------------] \" is added successfully.\n\n";;
			Assert::AreEqual(expected, output);
		}

	};

	//@author A0114301E
	//test change directory function
	TEST_CLASS(changeDirectoryTest)
	{
	public:
		
		TEST_METHOD(getFeedback)
		{
			cmdChangeDirectory changeDirectory;
			string directory = "desktop";
			std::string expected = "Directory is changed to: " + directory + "\n\n";
			std::string actual = changeDirectory.getFeedback(directory);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(executeChangeDdirectory)
		{
			cmdChangeDirectory changeDirectory;
			Storage storage;
			std::string expected = "Directory is changed to: \n\n";
			std::string actual = changeDirectory.executecmdChangeDirectory(storage);
			Assert::AreEqual(expected, actual);
		};
	};


	//@author A0114301E
	//test help function
	TEST_CLASS(helpTest)
	{
	public:
		
		TEST_METHOD(help)
		{
			cmdHelp help;
			std::string expected = LINE+ HELP_ADD + HELP_DELETE + HELP_UPDATE + HELP_UPDATE_START + HELP_UPDATE_END 
							   + HELP_UPDATE_CLEAR_START + HELP_UPDATE_CLEAR_END + HELP_MARKASDONE + HELP_UNDO 
							   + HELP_SEARCH + HELP_DISPLAY + HELP_RECURRING + LINE;
			std::string actual = help.helpMessage();
			Assert::AreEqual(expected, actual);
		};
	};

	//@author A0114301E
	//test clear function
	TEST_CLASS(clearTest)
	{
	public:
		
		TEST_METHOD(clear)
		{
			cmdClear clear;
			Storage _storage;
			Eventlist list;
			clear.executeClear(_storage);
			int expected = 0;
			int actual = list.getTotalNumberOfEvents();
			Assert::AreEqual(expected, actual);
		};
	};

	//@author A0114301E
	TEST_CLASS(deleteTest)
	{
	public:
		
		TEST_METHOD(executecmdDelete)
		{
			cmdClear clear;
			Storage _storage;
			Eventlist list;
			cmdDelete _delete;
			cmdAdd _add;
			int numberBeforeDelete = 1;
			_delete.executecmdDelete(_storage);
			int expected = numberBeforeDelete - 1;
			int actual = list.getTotalNumberOfEvents();
			Assert::AreEqual(expected, actual);
		}
	};

	//@author A0114301E
	TEST_CLASS(undoTest)
	{
	public:
		
		TEST_METHOD(printUndoMessage)
		{
			cmdUndo undo;
			string actual = undo.printUndoMessage();
			string expected = "Undo last action successfully\n\n";
			Assert::AreEqual(expected, actual);
		};
	};

	//@author A0114301E
	TEST_CLASS(updateTest)
	{
	public:
		
		TEST_METHOD(printFeedback)
		{
			cmdUpdate update;
			string tempt;
			Event eventToUpdate;
			string actual = update.printFeedback(tempt, eventToUpdate);
			string UPDATE_MESSAGE = "\" is updated to ";
			string expected = "\"" + UPDATE_MESSAGE + "\"" + eventToUpdate.displayEvent() +"\" \n\n";
			Assert::AreEqual(expected, actual);
		};
	};

	//@author A0114301E
	TEST_CLASS(repeatParserTest)
	{
	public:
		//test if index is valid
		//partition into two test cases: invalid(boundary case) and valid index
		TEST_METHOD(isValidIndex)
		{
			cmdRepeatParser repeatParser;
			bool actualValid = repeatParser.isValidIndex(9);
			bool expectedValid = true;
			Assert::AreEqual(expectedValid, actualValid);
			bool actualInvalid = repeatParser.isValidIndex(-1);
			bool expectedInvalid = false;
			Assert::AreEqual(expectedInvalid, actualInvalid);
		}

		//test  if repeat type is any of the following:weekly, monthly, daily
		//partition into valid case and invalid case
		TEST_METHOD(isDailyWeeklyMonthly)
		{
			cmdRepeatParser repeatParser;
			bool actualWeekly = repeatParser.isDailyWeeklyMonthly("weekly");
			bool expectedWeekly = true;
			Assert::AreEqual(expectedWeekly, actualWeekly);
			bool actualMonthly = repeatParser.isDailyWeeklyMonthly("monthly");
			bool expectedMonthly = true;
			Assert::AreEqual(expectedMonthly, actualMonthly);
			bool actualDaily = repeatParser.isDailyWeeklyMonthly("daily");
			bool expectedDaily = true;
			Assert::AreEqual(expectedDaily, actualDaily);
			bool actualYearly = repeatParser.isDailyWeeklyMonthly("yearly");
			bool expectedYearly = false;
			Assert::AreEqual(expectedYearly, actualYearly);
		}

		//test if the repeat comand is "every"
		//partion into valid and invalid case
		TEST_METHOD(isCertainDayofWeek)
		{
			cmdRepeatParser repeatParser;
			bool actualValid = repeatParser.isCertainDayOfAWeek("every");
			bool expectedValid = true;
			Assert::AreEqual(expectedValid, actualValid);
			bool actualInvalid = repeatParser.isCertainDayOfAWeek("for");
			bool expectedInvalid = false;
			Assert::AreEqual(expectedInvalid, actualInvalid);
		}

		//partition into valid and inalid cases
		TEST_METHOD(isStringAnInteger)
		{
			cmdRepeatParser repeatParser;
			bool actual = repeatParser.isStringAnInteger("5");
			bool expected = true;
			Assert::AreEqual(expected, actual);
			bool actualInvalid = repeatParser.isCertainDayOfAWeek("for");
			bool expectedInvalid = false;
			Assert::AreEqual(expectedInvalid, actualInvalid);
		}

		//test function converting upper case to lower case
		TEST_METHOD(lowercaseRepeatDetail)
		{
			cmdRepeatParser repeatParser;
			string actualOne = repeatParser.lowercaseRepeatDetail("WEEKLY");
			string expectedOne = "weekly";
			Assert::AreEqual(expectedOne, actualOne);
			string actualTwo = repeatParser.lowercaseRepeatDetail("Weekly");
			string expectedTwo = "weekly";
			Assert::AreEqual(expectedTwo, actualTwo);
		}
	};

	//@author A0114301E
	TEST_CLASS(cmdRepeatTest)
	{
	public:

		//test if a given input is a valid weekday
		//there are 7 valid cases in total
		TEST_METHOD(isWeekday)
		{
			cmdRepeat repeat;
			bool expectedOne = repeat.isWeekday("mon");
			bool actualOne = true;
			Assert::AreEqual(expectedOne, actualOne);
			bool expectedTwo = repeat.isWeekday("monday");
			bool actualTwo = true;
			Assert::AreEqual(expectedTwo, actualTwo);
			bool expectedThree = repeat.isWeekday("Mon");
			bool actualThree = true;
			Assert::AreEqual(expectedThree, actualThree);
			bool expectedTue = repeat.determineWeekday("tuesday");
			bool actualTue = true;
			Assert::AreEqual(expectedTue, actualTue);
			bool expectedWed = repeat.determineWeekday("wednesday");
			bool actualWed = true;
			Assert::AreEqual(expectedWed, actualWed);
			bool expectedThur= repeat.determineWeekday("thursday");
			bool actualThur = true;
			Assert::AreEqual(expectedThur, actualThur);
			bool expectedFri = repeat.determineWeekday("friday");
			bool actualFri = true;
			Assert::AreEqual(expectedFri, actualFri);
			bool expectedSat = repeat.determineWeekday("saturday");
			bool actualSat = true;
			Assert::AreEqual(expectedSat, actualSat);
			bool expectedSun = repeat.determineWeekday("sun");
			bool actualSun = true;
			Assert::AreEqual(expectedSun, actualSun);
		}

		TEST_METHOD(determineRepeatTimes)
		{
			cmdRepeat repeat;
			int expected = repeat.determineRepeatTimes(3);
			int actual = 3;
			Assert::AreEqual(expected, actual);
		}

		//there are 7 valid cases in total
		TEST_METHOD(determineWeekDay)
		{
			cmdRepeat repeat;
			int expectedMonday = repeat.determineWeekday("monday");
			int actualMonday = 0;
			Assert::AreEqual(expectedMonday, actualMonday);
			int expectedTue = repeat.determineWeekday("tuesday");
			int actualTue = 1;
			Assert::AreEqual(expectedTue, actualTue);
			int expectedWed = repeat.determineWeekday("wednesday");
			int actualWed = 2;
			Assert::AreEqual(expectedWed, actualWed);
			int expectedThur= repeat.determineWeekday("thursday");
			int actualThur = 3;
			Assert::AreEqual(expectedThur, actualThur);
			int expectedFri = repeat.determineWeekday("friday");
			int actualFri = 4;
			Assert::AreEqual(expectedFri, actualFri);
			int expectedSat = repeat.determineWeekday("saturday");
			int actualSat = 5;
			Assert::AreEqual(expectedSat, actualSat);
			int expectedSun = repeat.determineWeekday("sun");
			int actualSun = 6;
			Assert::AreEqual(expectedSun, actualSun);
		}

		//three are 7 valid cases in total
		TEST_METHOD(getExceptionTime)
		{
			cmdRepeat repeat;
			int expectedTue = repeat.getExceptionTime("tuesday");
			int actualTue = 1;
			Assert::AreEqual(expectedTue, actualTue);
			int expectedMon = repeat.getExceptionTime("mon");
			int actualMon = 0;
			Assert::AreEqual(expectedMon, actualMon);
			int expectedWed = repeat.getExceptionTime("wed");
			int actualWed = 2;
			Assert::AreEqual(expectedWed, actualWed);
			int expectedThur = repeat.getExceptionTime("thur");
			int actualThur = 3;
			Assert::AreEqual(expectedThur, actualThur);
			int expectedFri = repeat.getExceptionTime("FRI");
			int actualFri = 4;
			Assert::AreEqual(expectedFri, actualFri);
			int expectedSat = repeat.getExceptionTime("sat");
			int actualSat = 5;
			Assert::AreEqual(expectedSat, actualSat);
			int expectedSun = repeat.getExceptionTime("sun");
			int actualSun = 6;
			Assert::AreEqual(expectedSun, actualSun);
		}

		//test the function that returns the number of days in any month of 2015
		//there are 12 valid cases in total
			TEST_METHOD(getNumberOfDays)
		{
			cmdRepeat repeat;
			int expectedJan = repeat.getNumberOfDays(1,2015);
			int actualJan = 31;
			Assert::AreEqual(expectedJan, actualJan);
			int expectedFeb= repeat.getNumberOfDays(2,2015);
			int actualFeb = 28;
			Assert::AreEqual(expectedFeb, actualFeb);
			int expectedMar = repeat.getNumberOfDays(3,2015);
			int actualMar = 31;
			Assert::AreEqual(expectedMar, actualMar);
			int expectedApr = repeat.getNumberOfDays(4,2015);
			int actualApr = 30;
			Assert::AreEqual(expectedApr, actualApr);
			int expectedMay = repeat.getNumberOfDays(5,2015);
			int actualMay = 31;
			Assert::AreEqual(expectedMay, actualMay);
			int expectedJun = repeat.getNumberOfDays(6,2015);
			int actualJun = 30;
			Assert::AreEqual(expectedJun, actualJun);
			int expectedJul = repeat.getNumberOfDays(7,2015);
			int actualJul = 31;
			Assert::AreEqual(expectedJul, actualJul);
			int expectedAug = repeat.getNumberOfDays(8,2015);
			int actualAug = 31;
			Assert::AreEqual(expectedAug, actualAug);
			int expectedSep = repeat.getNumberOfDays(9,2015);
			int actualSep = 30;
			Assert::AreEqual(expectedSep, actualSep);
			int expectedOct = repeat.getNumberOfDays(10,2015);
			int actualOct = 31;
			Assert::AreEqual(expectedOct, actualOct);
			int expectedNov = repeat.getNumberOfDays(11,2015);
			int actualNov = 30;
			Assert::AreEqual(expectedNov, actualNov);
			int expectedDec = repeat.getNumberOfDays(12,2015);
			int actualDec = 31;
			Assert::AreEqual(expectedDec, actualDec);
		}
	};
}
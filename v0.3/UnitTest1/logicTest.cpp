#include "stdafx.h"
#include "CppUnitTest.h"
#include "../V0.3/cmdAdd.h"
#include "../V0.3/Storage.h"
#include "../V0.3//Parser.h"
#include "../V0.3/Eventlist.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
const static std::string HELP_ADD = "add <task name> by: date month time\ne.g. add submit report by: 2 mar 1211\n\n";
const static std::string HELP_DELETE = "delete <task number(s)>\ne.g. delete 1   delete 1 2 3\n\n";
const static std::string HELP_DISPLAY = "display undone/done tasks: display/displaydone\ndisplay today's tasks: displaytoday\n\n";
const static std::string HELP_UPDATE = "update <task number> .name new name\ne.g update 1 .name collect homework\n\n";
const static std::string HELP_UPDATE_START = "update <task number> .start new start time\ne.g. update 1 .start 1 Mar 1211\n\n";
const static std::string HELP_UPDATE_CLEAR_START = "update <task number> .clear start\ne.g. update 2 .start 2 march 1211\n\n";
const static std::string HELP_UPDATE_CLEAR_END = "update <task number> .clear end\ne.g. update 2 .end 2 02 1211\n\n";
const static std::string HELP_UPDATE_END = "update <task number> .start new end time\ne.g. update 1 .end 1 mar 1211\n\n";
const static std::string HELP_MARKASDONE = "mark task(s) as done\ne.g. done 1   done 1 2 3\n\n";
const static std::string HELP_UNDO = "undo last action(up to last two actions): undo\n\n";
const static std::string HELP_SEARCH = "search <key words>\ne.g. search homework\n\n";
const static std::string LINE = "================================================\n";

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(addWithDeadline)
		{
			std::string _taskname = "task";
			int _endingDay = 1;
			int _endingMonth = 4;
			int _endingTime = 900;
			Storage _storage;
			cmdAdd _add;
			logic logic;
			Event _newEvent(_taskname, _endingDay, _endingMonth,_endingTime);
			std::string output = _add.addEventWithDeadline(_storage);
			std::string expected = "[by 01 Apr 09:00            ] task";
			Assert::AreEqual(expected, output);
		}

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
			std::string expected = "\"" + _newEvent.displayEvent() + "\" is added successfully.\n\n";;
			Assert::AreEqual(expected, output);
		}

	};

	TEST_CLASS(helpTest)
	{
	public:
		
		TEST_METHOD(help)
		{
		cmdHelp help;
		std::string expected = LINE+ HELP_ADD + HELP_DELETE + HELP_UPDATE + HELP_UPDATE_START + HELP_UPDATE_END 
							   + HELP_UPDATE_CLEAR_START + HELP_UPDATE_CLEAR_END + HELP_MARKASDONE + HELP_UNDO 
							   + HELP_SEARCH + HELP_DISPLAY + LINE;
		std::string actual = help.helpMessage();
		Assert::AreEqual(expected, actual);
		};
	};

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
		};
	};

	TEST_CLASS(displayTest)
	{
	public:
		
		TEST_METHOD(boolIsEventToday)
		{
		cmdClear clear;
		Storage _storage;
		Eventlist list;
		cmdDisplay eventToday;
		int taskStartMonth = 4;
		int taskStartDay = 5;
		int taskEndMonth = 4;
		int taskEndDay = 5;
		bool _isEventToday = eventToday.isEventToday(taskStartMonth, taskStartDay, taskEndMonth, taskEndDay);
		bool expected = 1;
		bool actual = _isEventToday;
		Assert::AreEqual(expected, actual);
		};
	};

	TEST_CLASS(marAsDoneTest)
	{
	public:
		
		TEST_METHOD(markAsDone)
		{
		
		};
	};

	TEST_CLASS(searchTest)
	{
	public:
		
		TEST_METHOD(search)
		{
			
		
		};
	};

	TEST_CLASS(undoTest)
	{
	public:
		
		TEST_METHOD(undo)
		{
		cmdUndo _undo;
		Storage _storage;
		};
	};

	TEST_CLASS(updateTest)
	{
	public:
		
		TEST_METHOD(clearEndingTime)
		{
		std::string _taskname = "task";
		int _endingDay = 1;
		int _endingMonth = 4;
		int _endingTime = 900;
		Event event(_taskname, _endingDay, _endingMonth,_endingTime);
		cmdUpdate _update;
		Storage _storage;
		string taskName = "new task";
		Event newEvent(taskName, _endingDay, _endingMonth,_endingTime);
		string expected = _update.updateName(newEvent, 1, _storage);
		string actual = " updated to ";
		Assert::AreEqual(expected, actual);
		};
	};

	TEST_CLASS(logicTest)
	{
	public:
		
		TEST_METHOD(logic)
		{
			
			
		}

	};


}
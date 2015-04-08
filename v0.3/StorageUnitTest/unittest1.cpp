//@author A0116455H

#include "stdafx.h"
#include "CppUnitTest.h"
#include <assert.h>
#include "Storage.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StorageTest {
	TEST_CLASS(testEvent) {
	public:
		//All functions here are simple and straight forward
		TEST_METHOD(createEvent) {
			Event sampleEvent("FinishProject",13,04,2359);
			std::string expected[1] = {	"FinishProject" };
			sampleEvent.changeStartDay(01);
			sampleEvent.changeStartMonth(02);
			sampleEvent.changeStartTime(2222);
			sampleEvent.changeStartYear(2016);
			sampleEvent.changeEndYear(2017);
			int number[8] = { 13, 04, 2359, 01, 02, 2222, 2016 ,2017 };
			Assert::AreEqual(expected[0],sampleEvent.getTaskName());
			Assert::AreEqual(number[0],sampleEvent.getEndDate());
			Assert::AreEqual(number[1],sampleEvent.getEndMonth());
			Assert::AreEqual(number[2],sampleEvent.getEndTime());
			Assert::AreEqual(number[3],sampleEvent.getStartDate());
			Assert::AreEqual(number[4],sampleEvent.getStartMonth());
			Assert::AreEqual(number[5],sampleEvent.getStartTime());
			Assert::AreEqual(number[6],sampleEvent.getStartYear());
			Assert::AreEqual(number[7],sampleEvent.getEndYear());
			Assert::AreEqual(number[0],sampleEvent.getEndDate());
		}

		//6 different format of display events are tested.
		//Namely, floating task, deadline task, duration task
		//deadline task with non default year, duration task with non default end year
		//and duration task with non default start and end year.
		TEST_METHOD(displayEvent) {
			Event sampleEvent("FinishProject",13,04,2359);
			std:: string expected[6] = {	"[by 13 Apr 23:59            ] FinishProject", 
											"[by 13 Apr 23:59 Year: 2016                       ] FinishProject",
											"[21 Mar 23:59 - 13 Apr 23:59] FinishProject",
											"[21 Mar 23:59 - 13 Apr 23:59 Year: 2017           ] FinishProject",
											"[21 Mar 23:59 Year: 2016 - 13 Apr 23:59 Year: 2017] FinishProject",
											"[---------------------------] FinishProject",
										};
			Assert::AreEqual(expected[0],sampleEvent.displayEvent());
			sampleEvent.changeEndYear(2016);
			Assert::AreEqual(expected[1],sampleEvent.displayEvent());
			sampleEvent.changeEndYear(2015);
			sampleEvent.changeStartDay(21);
			sampleEvent.changeStartMonth(03);
			sampleEvent.changeStartTime(2359);
			Assert::AreEqual(expected[2],sampleEvent.displayEvent());
			sampleEvent.changeEndYear(2017);
			Assert::AreEqual(expected[3],sampleEvent.displayEvent());
			sampleEvent.changeStartYear(2016);
			Assert::AreEqual(expected[4],sampleEvent.displayEvent());
			Event sampleEvent1("FinishProject",-1,-1,-1);
			Assert::AreEqual(expected[5],sampleEvent1.displayEvent());
		}

		//Check all 3 format of saveEvent
		TEST_METHOD(saveEvent) {
			Event sampleEvent("FinishProject",13,-1,2359);
			std:: string expected[3] = {	"FinishProject Starting Info: Nil Ending Info: Nil ",
											"FinishProject Starting Info: Nil Ending Info: 13 04 2359 2015",
											"FinishProject Starting Info: 21 03 2359 2016 Ending Info: 13 04 2359 2017"
										};
			Assert::AreEqual(expected[0],sampleEvent.saveEvent());
			sampleEvent.changeEndMonth(4);
			Assert::AreEqual(expected[1],sampleEvent.saveEvent());
			sampleEvent.changeStartDay(21);
			sampleEvent.changeStartMonth(03);
			sampleEvent.changeStartTime(2359);
			sampleEvent.changeEndYear(2017);
			sampleEvent.changeStartYear(2016);
			Assert::AreEqual(expected[2],sampleEvent.saveEvent());
		}

		//Any of the day, month and time of the ending informatino must be valid
		//to return true.
		//Equivalent Partition for time { < 0}, {0 - 2359}, { > 2359}
		//Equivalent Partition for day { < 1}, {1 - 31}, { >31}
		//Equivalent Partition for month { < 1}, {1 - 12}, { > 12}
		TEST_METHOD(isValidDateMonthTime) {
			Event sampleEvent("FinishProject",13,04,2359);
			bool expected = true;
			Assert::AreEqual(expected, sampleEvent.isValidDateMonthTime());
			sampleEvent.changeEndTime(0);
			Assert::AreEqual(expected, sampleEvent.isValidDateMonthTime());
			sampleEvent.changeEndMonth(1);
			Assert::AreEqual(expected, sampleEvent.isValidDateMonthTime());
			sampleEvent.changeEndMonth(12);
			Assert::AreEqual(expected, sampleEvent.isValidDateMonthTime());
			sampleEvent.changeEndDay(1);
			Assert::AreEqual(expected, sampleEvent.isValidDateMonthTime());
			sampleEvent.changeEndDay(31);
			Assert::AreEqual(expected, sampleEvent.isValidDateMonthTime());
			
			expected = false;
			sampleEvent.changeEndTime(2400);
			Assert::AreEqual(expected, sampleEvent.isValidDateMonthTime());
			sampleEvent.changeEndTime(-1);
			Assert::AreEqual(expected, sampleEvent.isValidDateMonthTime());
			sampleEvent.changeEndTime(2100);
			sampleEvent.changeEndMonth(0);
			Assert::AreEqual(expected, sampleEvent.isValidDateMonthTime());
			sampleEvent.changeEndMonth(13);
			Assert::AreEqual(expected, sampleEvent.isValidDateMonthTime());
			sampleEvent.changeEndMonth(11);
			sampleEvent.changeEndDay(0);
			Assert::AreEqual(expected, sampleEvent.isValidDateMonthTime());
			sampleEvent.changeEndDay(32);
			Assert::AreEqual(expected, sampleEvent.isValidDateMonthTime());
		}

		//Any of the day, month and time of the starting informatino must be valid
		//to return true.
		//Equivalent Partition for time { < 0}, {0 - 2359}, { > 2359}
		//Equivalent Partition for day { < 1}, {1 - 31}, { >31}
		//Equivalent Partition for month { < 1}, {1 - 12}, { > 12}
		TEST_METHOD(isTimedEvent) {
			Event sampleEvent("FinishProject",13,04,2359);
			bool expected = false;
			Assert::AreEqual(expected, sampleEvent.isTimedTask());
			expected = true;
			sampleEvent.changeStartDay(1);
			sampleEvent.changeStartMonth(1);
			sampleEvent.changeStartTime(1);
			Assert::AreEqual(expected, sampleEvent.isTimedTask());
			sampleEvent.changeStartDay(31);
			Assert::AreEqual(expected, sampleEvent.isTimedTask());
			sampleEvent.changeStartMonth(1);
			Assert::AreEqual(expected, sampleEvent.isTimedTask());
			sampleEvent.changeStartMonth(12);
			Assert::AreEqual(expected, sampleEvent.isTimedTask());
			sampleEvent.changeStartTime(0);
			Assert::AreEqual(expected, sampleEvent.isTimedTask());
			sampleEvent.changeStartTime(2359);
			Assert::AreEqual(expected, sampleEvent.isTimedTask());

			expected = false;
			sampleEvent.changeStartDay(0);
			Assert::AreEqual(expected, sampleEvent.isTimedTask());
			sampleEvent.changeStartDay(32);
			Assert::AreEqual(expected, sampleEvent.isTimedTask());
			sampleEvent.changeStartDay(31);
			sampleEvent.changeStartMonth(0);
			Assert::AreEqual(expected, sampleEvent.isTimedTask());
			sampleEvent.changeStartMonth(13);
			Assert::AreEqual(expected, sampleEvent.isTimedTask());
			sampleEvent.changeStartMonth(12);
			sampleEvent.changeStartTime(-1);
			Assert::AreEqual(expected, sampleEvent.isTimedTask());
			sampleEvent.changeStartTime(2400);
			Assert::AreEqual(expected, sampleEvent.isTimedTask());
		}

		//2 different cases to consider {1 digit number}, {2 digit number},
		//all should return a 2 char string.
		TEST_METHOD(convertToTwoCharSting) {
			Event sampleEvent("FinishProject",01,04,0001);
			std::string output = sampleEvent.convertNumberToString(1);
			std::string expected = "01";
			Assert::AreEqual(output, expected);
		}

		//4 different cases to consider {1 digit number}, {2 digit number},
		//{3 digit number}, {4 digit number}
		//all should return a 4 char string.
		TEST_METHOD(convertToFourCharSting) {
			Event sampleEvent("FinishProject",01,04,0001);
			std::string output = sampleEvent.convertTimeToString(1);
			std::string expected = "0001";
			Assert::AreEqual(output, expected);
			output = sampleEvent.convertTimeToString(10);
			expected = "0010";
			Assert::AreEqual(output, expected);
			output = sampleEvent.convertTimeToString(100);
			expected = "0100";
			Assert::AreEqual(output, expected);
			output = sampleEvent.convertTimeToString(1000);
			expected = "1000";
			Assert::AreEqual(output, expected);
		}

		TEST_METHOD(getDeadLine) {
			Event sampleEvent("FinishProject",13,04,2359);
			std:: string expected[3] = {	"13 Apr 2359",
											"13 Apr 0000",
											"01 Apr 0000" };
			Assert::AreEqual(expected[0],sampleEvent.getDeadline());
			sampleEvent.changeEndTime(0);
			Assert::AreEqual(expected[1],sampleEvent.getDeadline());
			sampleEvent.changeEndDay(1);
			Assert::AreEqual(expected[2],sampleEvent.getDeadline());
		}

		//test 12 different month test.
		TEST_METHOD(convertToMonth) {
			Event sampleEvent("FinishProject",13,04,2359);
			int i = 1;
			std::string expected[12] = {	"Jan",
											"Feb",
											"Mar",
											"Apr",
											"May",
											"Jun",
											"Jul",
											"Aug",
											"Sep",
											"Oct",
											"Nov",
											"Dec" };
			for(i = 1; i <13 ; i++) {
				int index = i - 1;
				Assert::AreEqual(expected[index],sampleEvent.convertToMonth(i));
			}
		}
	};

	TEST_CLASS(testEventlist) {
	
	public:
		TEST_METHOD(addEvent) {
			Event sampleEvent("FinishProject",13,04,2359);
			Eventlist sampleEventList;
			sampleEventList.addEvent(sampleEvent);
			Event expectedEvent;
			expectedEvent = sampleEventList.getEvent(1);
			std:: string expected[1] = { "[by 13 Apr 23:59            ] FinishProject", };
			Assert::AreEqual(expected[0],expectedEvent.displayEvent());
		}

		TEST_METHOD(addMultipleEvent) {
			Event sampleEvent1("IncompleteProject",02,04,2359);
			Event sampleEvent2("FinishProject",13,04,2359);
			Eventlist sampleEventList;
			sampleEventList.addEvent(sampleEvent1);
			sampleEventList.addEvent(sampleEvent2);
			Assert::AreEqual(2,sampleEventList.getTotalNumberOfEvents());
		}

		TEST_METHOD(deleteEventFromEventlist) {
			Event sampleEvent1("IncompleteProject",02,04,2359);
			Event sampleEvent2("FinishProject",13,04,2359);
			Eventlist sampleEventList;
			sampleEventList.addEvent(sampleEvent1);
			sampleEventList.addEvent(sampleEvent2);
			Event expectedEvent;
			expectedEvent = sampleEventList.getEvent(2);
			std:: string expected[1] = { "[by 13 Apr 23:59            ] FinishProject" };
			Assert::AreEqual(expected[0],expectedEvent.displayEvent());
			sampleEventList.deleteEvent(1);
			expectedEvent = sampleEventList.getEvent(1);
			Assert::AreEqual(expected[0],expectedEvent.displayEvent());
		}

		TEST_METHOD(updateEventlist) {
			Event sampleEvent1("IncompleteProject",02,04,2359);
			Event sampleEvent2("FinishProject",13,04,2359);
			Eventlist sampleEventList;
			sampleEventList.addEvent(sampleEvent1);
			sampleEventList.updateEvent(1,sampleEvent2);
			Event expectedEvent;
			expectedEvent = sampleEventList.getEvent(1);
			std:: string expected[1] = { "[by 13 Apr 23:59            ] FinishProject" };
			Assert::AreEqual(expected[0],expectedEvent.displayEvent());
		}

		// floating task should rank first and other task depend on the ending info.
		TEST_METHOD(sortEventlist) {
			Event sampleEvent1("IncompleteProject",02,04,2359);
			Event sampleEvent2("FinishProject",13,04,2359);
			Event sampleEvent3("Floating Task",00,00,0001);
			Eventlist sampleEventList;
			sampleEventList.addEvent(sampleEvent2);
			sampleEventList.addEvent(sampleEvent1);
			sampleEventList.addEvent(sampleEvent3);
			Event expected = sampleEventList.getEvent(1);
			Assert::AreEqual(expected.displayEvent(),sampleEvent2.displayEvent());
			sampleEventList.sortEvent();
			expected = sampleEventList.getEvent(2);
			Assert::AreEqual(expected.displayEvent(),sampleEvent1.displayEvent());
			expected = sampleEventList.getEvent(1);
			Assert::AreEqual(expected.displayEvent(),sampleEvent3.displayEvent());
			
		}

		TEST_METHOD(getAllEvent) {
			Event sampleEvent1("IncompleteProject",02,04,2359);
			Event sampleEvent2("FinishProject",13,04,2359);
			Eventlist sampleEventList;
			sampleEventList.addEvent(sampleEvent1);
			sampleEventList.addEvent(sampleEvent2);
			std::list<Event> result = sampleEventList.returnAllEvent();
			Event expected = result.back();
			Assert::AreEqual(expected.displayEvent(),sampleEvent2.displayEvent());
			result.pop_back();
			expected = result.back();
			Assert::AreEqual(expected.displayEvent(),sampleEvent1.displayEvent());
			int numberOfEvent = result.size();
			Assert::AreEqual(1,numberOfEvent);
		}

		TEST_METHOD(copyNewList) {
			Event sampleEvent1("IncompleteProject",02,04,2359);
			Event sampleEvent2("FinishProject",13,04,2359);
			std::list<Event> result;
			result.push_back(sampleEvent1);
			result.push_back(sampleEvent2);
			Eventlist sampleEventList;
			sampleEventList.copyFromNewList(result);
			Event expected = sampleEventList.getEvent(2);
			Assert::AreEqual(expected.displayEvent(),sampleEvent2.displayEvent());
		}
	};

	TEST_CLASS(testStorage) {

	public:
		TEST_METHOD(addEvent) {
			Event sampleEvent("IncompleteProject",02,04,2359);
			Storage sampleStorage;
			sampleStorage.addEvent(sampleEvent);
			Event expected = sampleStorage.getEvent(1);
			Assert::AreEqual(expected.displayEvent(),sampleEvent.displayEvent());
		}

		TEST_METHOD(updateEvent) {
			Event sampleEvent1("IncompleteProject",02,04,2359);
			Event sampleEvent2("FinishProject",13,04,2359);
			Storage sampleStorage;
			sampleStorage.addEvent(sampleEvent1);
			sampleStorage.updateEvent(1,sampleEvent2);
			Event expected = sampleStorage.getEvent(1);
			Assert::AreEqual(expected.displayEvent(),sampleEvent2.displayEvent());
		}

		TEST_METHOD(markEventAsDone) {
			Event sampleEvent("IncompleteProject",02,04,2359);
			Storage sampleStorage;
			sampleStorage.addEvent(sampleEvent);
			std::list<int> index;
			index.push_back(1);
			sampleStorage.markEventAsDone(index);
			Event output = sampleStorage.getDoneEvent(1);
			Assert::AreEqual(sampleEvent.displayEvent(),output.displayEvent());
		}

		TEST_METHOD(deleteEvent) {
			Event sampleEvent1("IncompleteProject",02,04,2359);
			Event sampleEvent2("FinishProject",13,04,2359);
			Storage sampleStorage;
			sampleStorage.addEvent(sampleEvent1);
			sampleStorage.addEvent(sampleEvent2);
			std::list<int> index;
			index.push_back(1);
			sampleStorage.deleteEvent(index);
			Event output = sampleStorage.getEvent(1);
			Assert::AreEqual(sampleEvent2.displayEvent(),output.displayEvent());
		}

		//Test the 6 different saving and display format.
		//As format has been tested, one done case is sufficient.
		TEST_METHOD(readEventFromFile) {
			std:: string input[7] = {	"Incomplete tasks: FinishProject Starting Info: Nil Ending Info: Nil ",
										"Incomplete tasks: FinishProject Starting Info: Nil Ending Info: 13 04 2359 2015",
										"Incomplete tasks: FinishProject Starting Info: Nil Ending Info: 13 04 2359 2016",
										"Incomplete tasks: FinishProject Starting Info: 21 03 2359 2015 Ending Info: 13 04 2359 2015",
										"Incomplete tasks: FinishProject Starting Info: 21 03 2359 2015 Ending Info: 13 04 2359 2017",
										"Incomplete tasks: FinishProject Starting Info: 21 03 2359 2016 Ending Info: 13 04 2359 2017",
										"Done tasks: FinishProject Starting Info: Nil Ending Info: Nil "
										};
			std:: string expected[6] = {	"[---------------------------] FinishProject",
											"[by 13 Apr 23:59            ] FinishProject", 
											"[by 13 Apr 23:59 Year: 2016                       ] FinishProject",
											"[21 Mar 23:59 - 13 Apr 23:59] FinishProject",
											"[21 Mar 23:59 - 13 Apr 23:59 Year: 2017           ] FinishProject",
											"[21 Mar 23:59 Year: 2016 - 13 Apr 23:59 Year: 2017] FinishProject"
										};
			Storage sampleStorage;
			int i;
			for (i = 0; i < 6; i++) {
				sampleStorage.readEventsFromFile(input[i]);
				Event output = sampleStorage.getEvent(i+1);
				Assert::AreEqual(expected[i],output.displayEvent());
			}
			sampleStorage.readEventsFromFile(input[i]);
			Event output = sampleStorage.getDoneEvent(1);
			Assert::AreEqual(expected[0],output.displayEvent());
		}
	};
}
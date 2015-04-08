#include "stdafx.h"
#include "CppUnitTest.h"
#include <assert.h>
#include "Storage.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StorageTest
{
	TEST_CLASS(testEvent)
	{
	public:
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

		TEST_METHOD(displayEvent){
			Event sampleEvent("FinishProject",13,04,2359);
			std:: string expected[5] = {	"[by 13 Apr 23:59            ] FinishProject", 
											"[21 Mar 23:59 - 13 Apr 23:59] FinishProject",
											"[21 Mar 23:59 - 13 Apr 23:59 Year: 2017           ] FinishProject",
											"[21 Mar 23:59 Year: 2016 - 13 Apr 23:59 Year: 2017] FinishProject",
											"[---------------------------] FinishProject",
										};
			Assert::AreEqual(expected[0],sampleEvent.displayEvent());
			sampleEvent.changeStartDay(21);
			sampleEvent.changeStartMonth(03);
			sampleEvent.changeStartTime(2359);
			Assert::AreEqual(expected[1],sampleEvent.displayEvent());
			sampleEvent.changeEndYear(2017);
			Assert::AreEqual(expected[2],sampleEvent.displayEvent());
			sampleEvent.changeStartYear(2016);
			Assert::AreEqual(expected[3],sampleEvent.displayEvent());
			Event sampleEvent1("FinishProject",-1,-1,-1);
			Assert::AreEqual(expected[4],sampleEvent1.displayEvent());
		}
		TEST_METHOD(saveEvent){
			Event sampleEvent("FinishProject",13,04,2359);
			std:: string expected[2] = {	"FinishProject Starting Info: Nil Ending Info: 13 04 2359 2015",
											"FinishProject Starting Info: 21 03 2359 2016 Ending Info: 13 04 2359 2017",
										};
			Assert::AreEqual(expected[0],sampleEvent.saveEvent());
			sampleEvent.changeStartDay(21);
			sampleEvent.changeStartMonth(03);
			sampleEvent.changeStartTime(2359);
			sampleEvent.changeEndYear(2017);
			sampleEvent.changeStartYear(2016);
			Assert::AreEqual(expected[1],sampleEvent.saveEvent());

		}
		TEST_METHOD(isValidDateMonthTime)
		{	Event sampleEvent("FinishProject",13,04,2359);
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
		TEST_METHOD(getDeadLine)
		{	Event sampleEvent("FinishProject",13,04,2359);
			std:: string expected[3] = {	"13 04 2359",
											"13 04 0000",
											"01 04 0000"};
			Assert::AreEqual(expected[0],sampleEvent.getDeadline());
			sampleEvent.changeEndTime(0);
			Assert::AreEqual(expected[1],sampleEvent.getDeadline());
			sampleEvent.changeEndDay(1);
			Assert::AreEqual(expected[2],sampleEvent.getDeadline());
		}



	};

	TEST_CLASS(testEventlist){
	
	public:
		TEST_METHOD(addEvent){
			Event sampleEvent("FinishProject",13,04,2359);
			Eventlist sampleEventList;
			sampleEventList.addEvent(sampleEvent);
			Event expectedEvent;
			expectedEvent = sampleEventList.getEvent(1);
			std:: string expected[1] = { "[by 13 Apr 23:59            ] FinishProject", };
			Assert::AreEqual(expected[0],expectedEvent.displayEvent());
		}
		TEST_METHOD(addMultipleEvent){
			Event sampleEvent("FinishProject",13,04,2359);
			Eventlist sampleEventList;
			for (int i = 0; i<5 ; i) {
				sampleEventList.addEvent(sampleEvent);}
			Assert::AreEqual(5,sampleEventList.getTotalNumberOfEvents());
		}

		TEST_METHOD(deleteEventFromEventlist){
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

		TEST_METHOD(updateEventlist){
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

	};

	TEST_CLASS(testStorage)
	{
	public:
		TEST_METHOD(addEvent){
		Event sampleEvent1("IncompleteProject",02,04,2359);
		Storage sampleStorage;
		sampleStorage.addEvent(sampleEvent1);
		Event expected = sampleStorage.getEvent(1);
		Assert::AreEqual(expected.displayEvent(),sampleEvent1.displayEvent());
		}

		TEST_METHOD(updateEvent){
		Event sampleEvent1("IncompleteProject",02,04,2359);
		Event sampleEvent2("FinishProject",13,04,2359);
		Storage sampleStorage;
		sampleStorage.addEvent(sampleEvent1);
		sampleStorage.updateEvent(1,sampleEvent2);
		Event expected = sampleStorage.getEvent(1);
		Assert::AreEqual(expected.displayEvent(),sampleEvent2.displayEvent());

		}

	};
}
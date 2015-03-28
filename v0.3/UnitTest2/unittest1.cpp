#include "stdafx.h"
#include "CppUnitTest.h"
#include "Storage.h"
#include <assert.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StorageTest
{
	TEST_CLASS(testEvent)
	{
	public:
		
		TEST_METHOD(createEvent){
			Event sampleEvent("FinishProject",5,4,2359);

			std:: string expected[1] = { "FinishProject is due 5 4 2359" };

			Assert::AreEqual(expected[0],sampleEvent.readEvent());
			

		}
		TEST_METHOD(changeEndDate)
		{	Event sampleEvent("FinishProject",5,4,2359);
			sampleEvent.changeEndDay(6);
			sampleEvent.changeEndMonth(5);
			std:: string expected[1] = { "FinishProject is due 6 4 2359" };
			Assert::AreEqual(expected[0],sampleEvent.readEvent());
		}
		TEST_METHOD(changeEndTime)
		{	Event sampleEvent("FinishProject",5,4,2359);
			sampleEvent.changeEndTime(2300);
			std:: string expected[1] = { "FinishProject is due 5 4 2300" };
			Assert::AreEqual(expected[0],sampleEvent.readEvent());
		}



	};

	TEST_CLASS(testEventlist){
	
	public:
		TEST_METHOD(addEvent){
			Event sampleEvent("FinishProject",5,4,2359);
			Eventlist sampleEventList;
			sampleEventList.addEvent(sampleEvent);
			Event expectedEvent;
			expectedEvent = sampleEventList.getEvent(1);
			std:: string expected[1] = { "FinishProject is due 5 4 2359" };
			Assert::AreEqual(expected[0],expectedEvent.readEvent());
		}
		TEST_METHOD(addMultipleEvent){
			Event sampleEvent("FinishProject",5,4,2359);
			Eventlist sampleEventList;
			for (int i = 0; i<5 ; i++) {
				sampleEventList.addEvent(sampleEvent);}
			Assert::AreEqual(5,sampleEventList.getTotalNumberOfEvents());
		}

		TEST_METHOD(deleteEventFromEventlist){
			Event sampleEvent1("IncompleteProject",2,4,2359);
			Event sampleEvent2("FinishProject",5,4,2359);
			Eventlist sampleEventList;
			sampleEventList.addEvent(sampleEvent1);
			sampleEventList.addEvent(sampleEvent2);
			Event expectedEvent;
			expectedEvent = sampleEventList.getEvent(2);
			std:: string expected[1] = { "FinishProject is due 5 4 2359" };
			Assert::AreEqual(expected[0],expectedEvent.readEvent());
			sampleEventList.deleteEvent(1);
			expectedEvent = sampleEventList.getEvent(1);
			Assert::AreEqual(expected[0],expectedEvent.readEvent());
		}

		TEST_METHOD(updateEventlist){
			Event sampleEvent1("IncompleteProject",2,4,2359);
			Event sampleEvent2("FinishProject",2,4,2359);
			Eventlist sampleEventList;
			sampleEventList.addEvent(sampleEvent1);
			sampleEventList.updateEvent(1,sampleEvent2);
			Event expectedEvent;
			expectedEvent = sampleEventList.getEvent(1);
			std:: string expected[1] = { "FinishProject is due 5 4 2359" };
			Assert::AreEqual(expected[0],expectedEvent.readEvent());
		}

	};

	TEST_CLASS(testStorage)
	{
	public:
		TEST_METHOD(addEvent){
		Event sampleEvent1("IncompleteProject",2,4,2359);
		Storage sampleStorage;
		sampleStorage.addEvent(sampleEvent1);
		Event expected = sampleStorage.getEvent(1);
		Assert::AreEqual(expected,sampleEvent1);
		}

		TEST_METHOD(updateEvent){
		Event sampleEvent1("IncompleteProject",2,4,2359);
		Event sampleEvent2("FinishProject",5,4,2359);
		Storage sampleStorage;
		sampleStorage.addEvent(sampleEvent1);
		sampleStorage.updateEvent(1,sampleEvent2);
		Event expected = sampleStorage.getEvent(1);
		Assert::AreEqual(expected,sampleEvent2);

		}

	};
}
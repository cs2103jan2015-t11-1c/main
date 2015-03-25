#include "stdafx.h"
#include "CppUnitTest.h"
#include "string.h"
#include "UI.h"
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UIUnitTest
{		
	TEST_CLASS(UITest)
	{
	private:
		UI ui;
	public:
		//enum returns an integer. "add"-ADD is corresponding to 0.
		//check if 0 and the value returned is the same
		//check if 1 and the value returned is different.
		TEST_METHOD(determineTheCommandType)
		{
			
			int i = ui.UI::determineCommandType("add");
			Assert::AreEqual( 0, i); 
			int j = ui.UI:: determineCommandType("add");
			Assert:: AreNotEqual(1, i);
		}

		// boolean value true is expected with nonempty commandword;
		//boolean value false is expected with empty commandWord;
		TEST_METHOD(readCommand)
		{

			string emptyInput="";
			string nonemptyIput = "add";
			Assert::IsTrue(ui.UI::readCommand(nonemptyIput));
			Assert::IsFalse(ui.UI::readCommand(emptyInput));
			
		}

		TEST_METHOD(showWelcomeMessage)
		{
			string welcomemsg="Welcome to Minik!";
			Assert::AreEqual(welcomemsg, ui.UI::showWelcomeMessage());
		}
	};
}

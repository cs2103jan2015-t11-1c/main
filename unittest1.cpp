#include "stdafx.h"
#include "CppUnitTest.h"
#include <fstream>
#include "TextBuddy.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextBuddyTests
{		
	static	const string testString_1 = "somebody is sleeping";
	static	const string testString_2 = "he is hungry";
	static	const string testString_3 = "is fun";

	TEST_CLASS(sortTest)
	{
	public:
		
		TEST_METHOD(sortAlphaTest) {
			const string ExpOutput = "all content in atest.txt are sorted alphabetically";
			Assert::AreEqual(ExpOutput, TextBuddy::sortAlphabetically("atest.txt"));
		}
	};
	
	TEST_CLASS(searchTest) {
	public:
		TEST_METHOD(searchWordTest) {

			string target = "he";
			string result = TextBuddy::searchWord("atest.txt", target);
			string expected = "";
			Assert::AreEqual(expected, result);
			//word not found
			string target2 = "am";
			string result2 = TextBuddy::searchWord("atest.txt", target2);
			string expected2 = "word not found in atest.txt";
			Assert::AreEqual(expected2, result2);
		}
	};
}
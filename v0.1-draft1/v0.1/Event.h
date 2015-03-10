#pragma once

#include <string>
#include <iostream>

using namespace std;
class Event
{
private:


public:
	string _title;
	string _date;
	string _time;
	string _details;
	Event(void);
	Event(string newTitle, string newDate, string newTime);
	~Event(void);
	void changeTitle( string newTitle );
	void changeDate ( string newDate );
	void changeTime ( string newTime);
	void changeDetails (string newdetails);
	string readEvent();
};


#include "Storage.h"
#include <iostream>

int main (void)
{
	Storage testing;

	testing.addEvent("hi","2012","1123");
	testing.addEvent("2", "2013","1124");
	testing.addEvent("3", "2014","2015");
	testing.deleteEvent(2);
	Event temp=testing.getEvent(2);
	std:: cout <<temp.readEvent();
	int i;
	cin>>i;

	return 0;
}
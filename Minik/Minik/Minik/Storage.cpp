#include "Storage.h"


Storage::Storage(void)
{
}


Storage::~Storage(void)
{
}
void Storage::addEvent(Event newEvent)
{	_eventInStorage.addEvent(newEvent); 
}

void Storage::deleteEvent(int index)
{	_eventInStorage.deleteEvent(index);
}
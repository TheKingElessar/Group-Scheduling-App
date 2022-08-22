#include "EventTime.h"

using namespace std;

int EventTime::nextID = 0;

int EventTime::getID() const
{
    return _id;
}

Person *EventTime::getOwner()
{
    return _owner;
}

time_t EventTime::getTime() const
{
    return _time;
}

bool EventTime::getIsEnding() const
{
    return _isEnding;
}

EventTime::EventTime(Person *owner, time_t time, bool isEnding)
{
    _owner = owner;
    _time = time;
    _isEnding = isEnding;
    if (!isEnding)
    {
        _id = EventTime::nextID;
    }
    else
    {
        _id = EventTime::getNextID();
    }
}

int EventTime::getNextID()
{
    EventTime::nextID++;
    return EventTime::nextID - 1;
}

EventTime::EventTime() = default;
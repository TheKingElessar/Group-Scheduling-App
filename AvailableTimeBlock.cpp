#include "AvailableTimeBlock.h"
#include "EventTime.h"

#include <utility>

using namespace std;

const vector<Person *> &AvailableTimeBlock::getOwners() const
{
    return _owners;
}

// I feel like I should be returning a pointer here instead of a reference
// to the actual object but eh whatcha gonna do I don't have time to work
// on that :)
// That would also mean I could make these const I guess
EventTime &AvailableTimeBlock::getStartEvent()
{
    return *_startEvent;
}

EventTime &AvailableTimeBlock::getEndEvent()
{
    return *_endEvent;
}

AvailableTimeBlock::AvailableTimeBlock(vector<Person *> owners, EventTime *startEvent, EventTime *endEvent)
{
    _owners = std::move(owners);
    _startEvent = startEvent;
    _endEvent = endEvent;
}

int AvailableTimeBlock::getID()
{
    return this->getStartEvent().getID();
}

AvailableTimeBlock::AvailableTimeBlock() = default;
#ifndef CSCI261_AVAILABLETIMEBLOCK_H
#define CSCI261_AVAILABLETIMEBLOCK_H

using namespace std;

#include "vector"
#include <ctime>

class Person;

class EventTime;

/*
 * AvailableTimeBlock stores start and end times and the block's owner.
 */
class AvailableTimeBlock
{
private:
    vector<Person *> _owners;
    EventTime *_startEvent;
    EventTime *_endEvent;
public:
    AvailableTimeBlock();

    AvailableTimeBlock(vector<Person *> owners, EventTime *startEvent, EventTime *endEvent);

    const vector<Person *> &getOwners() const;

    EventTime &getStartEvent();

    EventTime &getEndEvent();

    int getID();
};


#endif //CSCI261_AVAILABLETIMEBLOCK_H

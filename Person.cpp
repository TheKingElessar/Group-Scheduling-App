#include "Person.h"

using namespace std;

const string &Person::getName() const
{
    return _name;
}

const vector<AvailableTimeBlock*> &Person::getTimeBlocks() const
{
    return _timeBlocks;
}

Person::Person(string name, vector<AvailableTimeBlock*> timeBlocks)
{
    _name = std::move(name);
    _timeBlocks = std::move(timeBlocks);
}

void Person::addTimeBlock(AvailableTimeBlock *timeBlock)
{
    _timeBlocks.push_back(timeBlock);
}

Person::Person() = default;

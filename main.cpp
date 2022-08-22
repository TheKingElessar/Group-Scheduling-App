/* CSCI 261 Final Project: Scheduling App
 *
 * Author: Nathan Panzer
 * Skip Days Used: 0
 * Skip Days Remaining: 5
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity): None
 *
 * Have you ever tried to organize a Dungeons and Dragons session with five other people?
 * Everybody has their own busy schedules, so it’s hard to find a time that works for everyone.
 * This program eases those pains by taking everyone’s schedules (in the form of available
 * time blocks) and automatically finding time blocks that the most people are available for.
 */

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "EventTime.h"
#include "Person.h"
#include "AvailableTimeBlock.h"
#include "Util.h"
#include <ctime>
#include <iomanip>

using namespace std;

int main()
{

    /*
     * Read file names from cin
     */

    vector<string> personStrings;
    cout << "Enter one name per line, corresponding to the correct files.\nWhen finished, press enter twice." << endl;
    while (true)
    {
        string input;
        getline(cin, input);
        while (cin.fail())
        {
            cin.clear();
            char errInput = cin.get();
            while (errInput != '\n')
            {
                errInput = cin.get();
            }
            getline(cin, input);
        }

        if (input.empty())
        {
            break;
        }

        personStrings.push_back(input);
    }

    /*
     * Parse files into Persons and AvailableTimeBlocks
     */
    vector<Person *> people;
    vector<AvailableTimeBlock> allTimeBlocks;
    for (const string &name : personStrings)
    {
        vector<AvailableTimeBlock *> personTimeBlocks;

        auto *newPersonPtr = new Person(name, personTimeBlocks);

        string filePath = "people/" + name + ".txt";
        ifstream nameFile(filePath);
        if (nameFile.fail())
        {
            cout << "File " << filePath << " could not be opened. Skipping." << endl;
            continue;
        }

        string discardName;
        getline(nameFile, discardName);

        int lineNum = 1;
        string readLine;
        while (getline(nameFile, readLine))
        {
            lineNum++;

            /*
             * Parse a line like: 12/08/21 08:00 10:30
             * into a vector of three strings.
             */
            vector<string> splitLine;
            while (readLine.find(' ') != string::npos)
            {
                int foundIndex = readLine.find(' ');
                string substring = readLine.substr(0, foundIndex);
                splitLine.push_back(substring);
                readLine.replace(0, foundIndex + 1, "");
            }
            splitLine.push_back(readLine);

            if (splitLine.size() != 3)
            {
                cout << filePath << ":" << lineNum
                     << " is formatted incorrectly. It should look like 12/08/21 08:00 10:30." << endl;
                continue;
            }


            /*
             * Parsing times from https://stackoverflow.com/questions/48800745/how-to-convert-date-string-to-time-t
             */
            string startTimeString = splitLine.at(0) + " " + splitLine.at(1);
            time_t tStart = stringToTime(startTimeString);

            string endTimeString = splitLine.at(0) + " " + splitLine.at(2);
            time_t tEnd = stringToTime(endTimeString);

            /*
             * Allocate memory to store the necessary objects contained in
             * AvailableTimeBlock, because apparently if you don't do that
             * they're just deleted/overwritten. Ah, Rosie, I love this language!
             *
             * Ignore the cries of the damned below.
             */

            /*
             * WHY
             * WHY MUST YOU TORMENT ME SO
             * WHY CAN'T THIS BE EASY, LIKE IN JAVA
             * WHY WHAT DOES THIS MEAAAAAAAAAAAAAAAAAAAAAAAAAAN
             */
            auto *startEventTimePtr = new EventTime(newPersonPtr, tStart, false);

            auto *endEventTimePtr = new EventTime(newPersonPtr, tEnd, true);

            vector<Person *> blockOwners;
            blockOwners.push_back(newPersonPtr);

            auto *newTimeBlockPtr = new AvailableTimeBlock(blockOwners, startEventTimePtr, endEventTimePtr);

            (*newPersonPtr).addTimeBlock(newTimeBlockPtr);
            allTimeBlocks.push_back(*newTimeBlockPtr);
        }

        people.push_back(newPersonPtr);
    }

    if (people.size() < 2)
    {
        cout << "You must enter two or more people!" << endl;
        return 0;
    }

    vector<AvailableTimeBlock *> validTimeBlocks;

    // Populate timeline with all events
    vector<EventTime *> timeline;
    for (AvailableTimeBlock &timeBlock : allTimeBlocks)
    {
        EventTime *startEvent = &timeBlock.getStartEvent();
        timeline.push_back(startEvent);
        EventTime *endEvent = &timeBlock.getEndEvent();
        timeline.push_back(endEvent);
    }

    /*
     * Selection sort timeline by event time
     */
    for (int p = 0; p < timeline.size() - 1; p++)
    {
        int earliestIndex = p;
        time_t earliestTime = timeline.at(p)->getTime();
        for (int j = p + 1; j < timeline.size(); j++)
        {
            if (timeline.at(j)->getTime() < earliestTime)
            {
                earliestIndex = j;
                earliestTime = timeline.at(earliestIndex)->getTime();
            }
        }

        if (earliestIndex == p) continue;

        int origIndex = p;
        EventTime *origTime = timeline.at(p);

        timeline.at(origIndex) = timeline.at(earliestIndex);
        timeline.at(earliestIndex) = origTime;
    }

    /*
     * Here's where the magic happens. Walk through the timeline,
     * keeping track of which people currently have a block active.
     * When everyone has a block active, store that block.
     */
    vector<Person *> addedPeople;
    EventTime *allStart = nullptr;
    vector<EventTime> passedEventTimes;
    for (EventTime *eventTime : timeline)
    {
        if (eventTime->getIsEnding())
        {
            if (allStart != nullptr)
            {
                if (vectorsContainSamePeople(people, addedPeople))
                {
                    auto *validBlock = new AvailableTimeBlock;
                    auto *allEnd = eventTime;
                    *validBlock = AvailableTimeBlock(people, allStart, allEnd);
                    validTimeBlocks.push_back(validBlock);

                    allStart = nullptr;
                }
            }

            addedPeople.erase(addedPeople.begin() + getIndexOfPerson(addedPeople, eventTime->getOwner()));
        }
        else
        {
            // This is assuming that a person can't have two events going on at the same time
            Person *personPtr = eventTime->getOwner();
            addedPeople.push_back(personPtr);

            bool hasEveryone = vectorsContainSamePeople(people, addedPeople);

            if (hasEveryone && allStart == nullptr)
            {
                allStart = eventTime;
            }
        }
    }

    /*
     * Yeah, I eat my asparagus, how could you tell?
     */
    string found = " valid time block";
    if (validTimeBlocks.size() > 1)
    {
        found += "s";
    }
    found += ":";

    /*
     * Output the found valid time blocks to the user
     */
    cout << validTimeBlocks.size() << found << endl;
    for (int i = 0; i < validTimeBlocks.size(); i++)
    {
        /*
         * This is so sad but I can't find any better way to do it :(
         * https://stackoverflow.com/questions/10289017/how-to-format-date-and-time-string-in-c
         */

        AvailableTimeBlock *availableTimeBlock = validTimeBlocks.at(i);
        auto startTime = availableTimeBlock->getStartEvent().getTime();
        auto startTimeStruct = *localtime(&startTime);
        auto endTime = availableTimeBlock->getEndEvent().getTime();
        auto endTimeStruct = *localtime(&endTime);

        char format[] = "%a. %m/%d/%y %H:%M";

        std::stringstream buffer1;
        buffer1 << std::put_time(&startTimeStruct, format);
        string startTimeString = buffer1.str();

        std::stringstream buffer2;
        buffer2 << std::put_time(&endTimeStruct, format);
        string endTimeString = buffer2.str();

        cout << " " << i + 1 << ". " << startTimeString << " to " << endTimeString << endl;
    }

    return 0;
}
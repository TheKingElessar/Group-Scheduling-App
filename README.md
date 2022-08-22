# Final Project: Scheduling App

Have you ever tried to organize a Dungeons and Dragons session with five other people? Everybody has their own busy schedules, so it’s hard to find a time that works for everyone. This program eases those pains by taking everyone’s schedules (in the form of available time blocks) and automatically finding time blocks that the most people are available for.

## Usage

To run this program, build it with CLion and run the executable. You'll be prompted to enter file names—these correspond to `.txt` files in the directory `people`. To load the file `people/Nathan.txt`, you would enter "Nathan", and press enter. When you've entered all the file names, press enter twice.

All the main logic takes place in the main function. Utility functions are relegated to the `Util` file. `AvailableTimeBlock` stores start and end times and the block's owner. `EventTime` stores a time, the block's owner, and whether or not the time is the ending time. Person stores a name and a list of their time blocks.

One new feature that could be implemented would be allowing the user to input how many people need to be available during a time block for the time block to be valid. This could be done by taking the user's input in an `int` through `cin`, and then, while looping through the timeline, checking the size of the `addedPeople` vector, instead of comparing `addedPeople` and `people` vectors.

One aspect that could be improved would be the getter/setter functions, like `EventTime::getOwner()`. I had to make some strange getter functions, because returning constant references doesn't always work for my purposes. The getter functions should be updated to return pointers in more cases.

## Tests

```
Input:
	Nathan
	Mr. Potato Head
Output:
	4 valid time blocks:
	 1. Wed. 12/08/21 17:30 to Wed. 12/08/21 21:00
	 2. Thu. 12/09/21 13:30 to Thu. 12/09/21 14:00
	 3. Sat. 12/11/21 17:00 to Sat. 12/11/21 18:00
	 4. Sat. 12/11/21 19:00 to Sat. 12/11/21 21:00
```
```
Input:
	Nathan
Output:
	You must enter two or more people!
```
```
Input:
	Nathan
	President-Elect Barack Obama
Output:
	File people/President-Elect Barack Obama.txt could not be opened. Skipping.
	You must enter two or more people!
```
```
Input:
	Nathan
	Mr. Potato Head
	Dr. Whom
Output:
	people/Dr. Whom.txt:4 is formatted incorrectly. It should look like 12/08/21 08:00 10:30.
	1 valid time block:
	 1. Wed. 12/08/21 17:30 to Wed. 12/08/21 20:00
```
```
Input:
	Dr. Whom
Output:
	people/Dr. Whom.txt:4 is formatted incorrectly. It should look like 12/08/21 08:00 10:30.
	You must enter two or more people!
```

## Reflections

During my work on this project, I learned a ton, primarily about pointers, memory, and project structure. I spent a very long time sorting out some circular dependencies, and finally figured it out with forward declarations and storing pointers instead of full objects. And I spent a while figuring out when to use pointers, when to use references, when to just copy the objects, etc. At one point I saw that the memory addresses of some objects kept changing, and couldn't figure out why, until I realized it was because they were in a vector, and the vector was changing size so was being moved around. This stuff is crazy. Anyway, thanks for reading. Have a nice day!
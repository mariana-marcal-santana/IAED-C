#ifndef _PROTOTYPES_
#define _PROTOTYPES_

#include "structs.h"

/* MAIN FUNCTION 
- return 0 */

int main();

/* FUNCTIONS FOR COMMAND C */

/*
- argument: pointer to systemData
- handles command C
- return void */

void caseC (SystemData *systemData);

/*
- arguments: pointer to systemData
- prints data about all lines ((first stop, last stop), 
    number of stops, total cost, total time)
- return void */

void listAllLines (SystemData *systemData);

/*
- arguments: pointer to lineName, pointer to systemData
- prints line's stops in order
- return void */

void listLine (const char *lineName, SystemData *systemData);

/*
- arguments: pointer to lineName, pointer to systemData
- creates and sets data for a new line
- return void */

void createLine (const char *lineName, SystemData *systemData);

/*
- argument: pointer to string
- checks if string is a valid reverse command
- return TRUE if it is, FALSE if not */

int isReverse (char *string);

/*
- arguments: pointer to lineName, pointer to systemData
- prints line's stops in reverse order
- return void */

void listLineReverse (const char *lineName, SystemData *systemData);

/* FUNCTIONS FOR COMMAND P */

/*
- argument: pointer to systemData
- handles command P
- return void */

void caseP (SystemData *systemData);

/*
- argument: pointer to systemData
- prints data about all stops (name, latitude, longitude, number of lines)
- return void */

void listAllStops (SystemData *systemData);

/*
- arguments: pointer to stopName, latitude, longitude, pointer to systemData
- creates and sets data for a new stop
- return void */

void createStop (const char *stopName, double stopLatitude,
        double stopLongitude, SystemData *systemData);

/*
- arguments: pointer to stopName, pointer to systemData
- prints data about a stop (latitude, longitude)
- return void */

void listStop (char *stopName, SystemData *systemData);

/*
- arguments: index of stop, pointer to systemData
- counts the number of lies that pass through the stop
- return number of lines */

int countLines (int stopIndex, SystemData *systemData);

/* FUNCTIONS FOR COMMAND L */

/*
- argument: pointer to systemData
- handles command L
- return void */

void caseL (SystemData *systemData);

/*
- arguments: pointer to line, pointer to stopOrigin and stopDestination,
    linkCost, linkTime, pointer to systemData
- creates and sets data for indexes for the line's first link
- return void */

void createFirstLink (Line *line, Stop *stopOrigin, Stop *stopDestination,
    double linkCost, double linkTime, SystemData *systemData);

/* 
- arguments: pointer to line, pointer to stopOrigin and stopDestination,
    linkCost, linkTime, pointer to systemData
- creates and sets data for a new link
- return void */

void addLink (Line * line, Stop * stopOrigin, Stop * stopDestination,
    double linkCost, double linkTime, SystemData *systemData);

/*
- arguments: pointer to line, pointer to stopOrigin and stopDestination,
    linkCost, linkTime, pointer to systemData
- creates and sets data for indexes for a line's link
- return void */

void createLink (Line *line, Stop *stopOrigin, Stop *stopDestination,
    double linkCost, double linkTime, SystemData *systemData);

/*
- arguments: pointer to line and stopOriginIndex
- checks if stopOrigin is the last stop of the line
- return TRUE if it is, FALSE if not */

int checkOriginStop (Line * line, int stopOriginIndex);

/*
- arguments: pointer to line and stopOriginIndex
- checks if stopDestination is the first stop of the line
- return TRUE if it is, FALSE if not */

int checkDestinationStop (Line * line, int stopDestinationIndex);

/* FUNCTIONS FOR COMMAND I */

/*
- argument: pointer to systemData
- handles command I
- return void */

void caseI (SystemData *systemData);

/*
- arguments: stopIndex, pointer to systemData
- creates a list of line going through the stop calls function to sort and
    print the list and frees the list
- return void */

void listLinesAlphabetically (int stopIndex, SystemData *systemData);

/*
- arguments: pointer to linkedList
- sorts and prints the linkedlist
- return void */

void sortPrintLinkedListAlphabetically (listOfWords *linkedList);

/*
- arguments: 2 pointer to words
- swaps the words
- return void */

void swapWords(Word *element1, Word *element2);

/* FUNCTIONS FOR COMMAND R */

/*
- argument: pointer to systemData
- handles command R
- return void */

void caseR (SystemData *systemData);

/*
- arguments: pointer to lineName, pointer to systemData
- removes a line from the system
- return void */

void freeLine (char *lineName, SystemData *systemData);

/*
- arguments: pointer to lineName, pointer to systemData
- frees all the links of said line
- return void */

void freeLineLinks (char *lineName, SystemData *systemData);

/*
- arguments: pointer to linkToFree, pointer to systemData
- removes a link from the system
- return void */

void freeLink (Link *linkToFree, SystemData *systemData);

/* FUNCTIONS FOR COMMAND E */

/*
- argument: pointer to systemData
- handles command E
- return void */

void caseE (SystemData *systemData);

/*
- arguments: stopIndex, pointer to systemData
- checks for the stop to remove in all the lines and calls function to remove
- return void */

void removeStopLinks (int stopIndex, SystemData *systemData);

/*
- arguments: pointer to stopName, pointer to systemData
- removes a stop from the system
- return void */

void freeStop (char *stopName, SystemData *systemData);

/*
- arguments: pointer to line, stopIndex
- finds the index of the stop before on the line
- return index of the stop before */

Index* findPreviousStopLine (Line *line, int stopIndex);

/*
- arguments: pointer to line, stopIndex
- finds the index of the stop after on the line
- return index of the stop after */

Index * findNextStopLine (Line *line, int stopIndex);

/*
- arguments: pointer to line, stopIndex, pointer to systemData
- removes the first stop of the line and updates the line's data
- return void */

void removeStopLinkBeggining (Line *line, int stopIndex, SystemData *systemData);

/*
- arguments: pointer to line, stopIndex, pointer to systemData
- removes the last stop of the line and updates the line's data
- return void */

void removeStopLinkEnd (Line *line, int stopIndex, SystemData *systemData);

/*
- arguments: pointer to line, stopIndex, pointer to previousStopIndex and
    nextStopIndex, pointer to systemData
- updates the line's data, removes a stop and calls function to remove the link
- return void */

void removeStopLinkMiddle (Line *line, int stopIndex,
    Index *previousStopIndex, Index *nextStopIndex, SystemData *systemData);

/*
- arguments: pointer to line, pointer to link, pointer to previousStopIndex and
    nextStopIndex, newLinkCost, newLinkTime, pointer to element and auxElement
- updates a link's data and removes the link after
- return void */

void auxRemoveStopLinkMiddle(Line *line, Link *link, Index* previousStopIndex,
    Index *nextStopIndex, double newLinkCost, double newLinkTime,
    Index *element, Index *auxElement);

/*
- arguments: pointer to line, pointer to link, newStopOriginIndex,
    newStopDestinationIndex, newLinkCost, newLinkTime
- updates a link's data
- return void */

void changeLink (Line *line, Link *link, 
    int newStopOriginIndex, int newStopDestinationIndex,
    double newLinkCost, double newLinkTime);

/*
- arguments: pointer to line, 2 stopIndexes, pointer to systemData
- finds the first link of the line that goes through the 2 stops
- return pointer to the link */

Link * findLink (Line *line, int stop1Index, int stop2Index,
    SystemData *systemData);

/*
- arguments: pointer to line, 2 stopIndexes, pointer to systemData
- finds the index of the first link of the line that goes through the 2 stops
- return pointer to the index */

Index * findElementLine (Line *line, int stop1Index, int stop2Index,
    SystemData *systemData);

/* COMMAND A */

/*
- argument: pointer to systemData
- handles command A (clears the systemData)
- return void */

void caseA (SystemData *systemData);

/* GENERAL FUNCTIONS */

/* PARSING OF INPUT 
- arguments: array for charcters
- reads input from input and stores it in array
- return 0 if end of line, 1 if not */

int readWord (char str[]);

/* MALLOC VARIATION
- arguments: pointer to systemData and size of memory to be allocated
- checks if it's possible to allocate memory and if not, prints error message
- return void */

void * checksMalloc (SystemData *systemData, unsigned int size);

/* FIND STRUCTS */

/*
- arguments: pointer to lineName, pointer to systemData
- finds the line with lineName in the system
- return pointer to the line */

Line * lineNameToLine (const char *lineName, SystemData *systemData);

/*
- arguments: pointer to stopName, pointer to systemData
- finds the stop with stopName in the system
- return pointer to the stop */

Stop * stopNameToStop (const char *stopName, SystemData *systemData);

/*
- arguments: linkIndex, pointer to systemData
- finds the link with linkIndex in the system
- return pointer to the link */

Link * linkIndexToLink (int linkIndex, SystemData *systemData);

/* CHECK EXISTENCE */

/*
- arguments: pointer to lineName, pointer to systemData
- checks if a line with lineName exists in the system
- return its index if it exists, ERROR if it doesn't */

int lookupLine (char *lineName, SystemData *systemData);

/*
- arguments: pointer to stopName, pointer to systemData
- checks if a stop with stopName exists in the system
- return its index if it exists, ERROR if it doesn't */

int lookupStop (char *stopName, SystemData *systemData);

/* GET NAME */

/*
- arguments: stopIndex, pointer to systemData
- finds the name of the stop with stopIndex in the system
- return pointer to the name of the stop */
char * stopIndexToName (int stopIndex, SystemData *systemData);

/* CREATE LISTS  */

/*
- arguments: pointer to systemData
- creates a lists of lines
- return pointer to the list */

listOfLines * createListOfLines (SystemData *systemData);

/*
- arguments: pointer to systemData
- creates a lists of stops
- return pointer to the list */

listOfStops * createListOfStops (SystemData *systemData);

/*
- arguments: pointer to systemData
- creates a lists of links
- return pointer to the list */

listOfLinks * createListOfLinks (SystemData *systemData);

/*
- arguments: pointer to systemData
- creates a lists of indexes
- return pointer to the list */

listOfIndexes * createListOfIndexes (SystemData *systemData);

/*
- arguments: pointer to systemData
- creates a lists of words
- return pointer to the list */

listOfWords * createListOfWords (SystemData *systemData);

/* ADD STRUCTS TO LISTS */

/*
- arguments: pointer to linkedList, pointer to newLine
- adds the line to the end of the list
- return void */

void insertLineEnd (listOfLines *linkedList, Line *newLine);

/*
- arguments: pointer to linkedList, pointer to newStop
- adds the stop to the end of the list
- return void */

void insertStopEnd (listOfStops *linkedList, Stop *newStop);

/*
- arguments: pointer to linkedList, pointer to newLink
- adds the link to the end of the list
- return void */

void insertLinkEnd (listOfLinks *linkedList, Link *newLink);

/*
- arguments: pointer to linkedList, pointer to word, pointer to systemData
- allocs memory for word and adds it to the end of the list
- return void */

void insertWordEnd (listOfWords *linkedList, const char *word, SystemData *systemData);

/*
- arguments: pointer to linkedList, pointer to systemData
- creates and adds the index to the beggining of the list
- return void */

void addLinkIndexBeggining (listOfIndexes *linkedList, SystemData *systemData);

/*
- arguments: pointer to linkedList, pointer to systemData
- creates and adds the index to the end of the list
- return void */

void addLinkIndexEnd (listOfIndexes *linkedList, SystemData *systemData);

/*
- arguments: pointer to linkedList, pointer to stopToAdd, pointer to systemData
- adds the index to the beggining of the list
- return void */

void addStopIndexBeggining (listOfIndexes *linkedList, Stop *stopToAdd, SystemData *systemData);

/*
- arguments: pointer to linkedList, pointer to stopToAdd, pointer to systemData
- adds the index to the end of the list
- return void */

void addStopIndexEnd (listOfIndexes *linkedList, Stop *stopToAdd, SystemData *systemData);

/* FREE LISTS */

/*
- arguments: pointer to systemData
- frees all the lists inside systemData and the systemData itself
- return void */

void freeAll (SystemData *systemData);

/*
- arguments: pointer to list of lines
- frees the list of lines
- return void */

void freeListOfLines (listOfLines *list);

/*
- arguments: pointer to list of stops
- frees the list of stops
- return void */

void freeListOfStops (listOfStops *list);

/*
- arguments: pointer to list of links
- frees the list of links
- return void */

void freeListOfLinks (listOfLinks *list);

/*
- arguments: pointer to list of indexes
- frees the list of indexes
- return void */

void freeListOfIndexes (listOfIndexes *list);

/*
- arguments: pointer to list of words
- frees the list of words
- return void */

void freeListOfWords (listOfWords *list);

#endif

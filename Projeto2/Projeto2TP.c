/* iaed-23 - ist1106992 - project2 */
/* Mariana Santana - ist1106992 */

#include "constants.h"
#include "structs.h"
#include "prototypes.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main () {
    /* alloc memory for systemData */
    SystemData * systemData = (SystemData *) malloc(sizeof(SystemData));
    int c;
    /* initializes the struct systemData */
    systemData -> numberOfLines = 0;
    systemData -> numberOfStops = 0;
    systemData -> numberOfLinks = 0;
    systemData -> allLines = createListOfLines(systemData);
    systemData -> allStops = createListOfStops(systemData);
    systemData -> allLinks = createListOfLinks(systemData);
    /* reads commands from terminal and directs to the specific functions */
    while ((c = getchar()) != EOF) {
		switch (c) {
            case 'q': freeAll(systemData);
                return 0;
            case 'c': caseC(systemData);
                break;
            case 'p': caseP(systemData);
                break;
            case 'l': caseL(systemData);
                break;
            case 'i': caseI(systemData);
                break;
            case 'r': caseR(systemData);
                break;
            case 'e': caseE(systemData);
                break;
            case 'a': caseA(systemData);
                break;
            case 'f': caseF(systemData);
                break;
        }
    }
    return 0;  
}

/* CASE C */

void caseC (SystemData *systemData) {

    char c1;
    int check;
    /* checks if the command letter is followed by a '\n' character */
    if ((c1 = getchar()) == '\n')
        listAllLines(systemData);

    else {
        char lineName[MAX_INPUT];
        /* if the name is followed by a '\n' character */
        if (readWord(lineName) == FALSE) {
            check = lookupLine(lineName, systemData);
            /* if the line exists lists its stops */
            if (check != ERROR)
                listLine(lineName, systemData);
            /* if it does not exist creates a new line */
            else
                createLine(lineName, systemData);
        }
        else {
            /* initializes and collects the next word from the input */
            char command[MAX_INPUT];
            readWord(command);
            /* checks if the collected word matches a reverse command */
            if (isReverse(command) == TRUE)
                listLineReverse(lineName, systemData); 
            /* if it does not prints an error */
            else
                printf(INCORRECT_SORT_OPTION);
        }
    }    
}

void listAllLines (SystemData *systemData) {
    Line *line = systemData -> allLines -> head;
    while (line != NULL) {
        if (strlen(line -> name) < 6) {
            printf("%s ", line -> name);
            /* if the line has links */
            if (line -> numberOfStops >= 2) {
                /* print line data */
                printf("%s ", stopIndexToName(line -> indexesOfStops -> head -> index,
                    systemData));
                printf("%s ", stopIndexToName(line -> indexesOfStops -> tail -> index,
                    systemData));
                printf("%d ", line -> numberOfStops);
                printf("%.2f ", line -> totalCost);
                printf("%.2f\n", line -> totalTime);
            }
            else
            printf("0 0.00 0.00\n");
        }
        line = line -> nextLine;
    }
}

void listLine (const char *lineName, SystemData *systemData) {
    Line *line = lineNameToLine(lineName, systemData);
    /* if the line found has stops */
    if (line -> numberOfStops != 0) {
        /* print them in order */
        Index * element = line -> indexesOfStops -> head;
        printf("%s", stopIndexToName(element -> index, systemData));

        for (element = element -> nextIndex; element != NULL; element = element -> nextIndex)
            printf(", %s", stopIndexToName(element -> index, systemData));
        putchar('\n');
    }
    
}

void createLine (const char *lineName, SystemData *systemData) {

    /* allocs memory to store line and lineName */
    Line *newLine = (Line *) checksMalloc(systemData, sizeof(Line));
    newLine -> name = (char *) checksMalloc(systemData, sizeof(char) * (strlen(lineName) + 1));

    /* initializes line and sets its name */
    strcpy(newLine -> name, lineName);
    newLine -> numberOfStops = 0;
    newLine -> totalCost = 0;
    newLine -> totalTime = 0;
    newLine -> lineIndex = systemData -> numberOfLines;
    newLine -> indexesOfStops = createListOfIndexes(systemData);
    newLine -> indexesOfLinks = createListOfIndexes(systemData);

    /* adds line to systemData */
    insertLineEnd(systemData -> allLines, newLine);
    systemData -> numberOfLines ++;
}

int isReverse (char *string) {

    /* initializes all the possible reverse commands */
    char str1[] = "inverso", str2[] = "invers", str3[] = "inver",
        str4[] = "inve", str5[] = "inv";

    /* returns wether the argument string equals any of the commands */
    if (strcmp(string, str1) == 0 || strcmp(string, str2) == 0 ||
        strcmp(string, str3) == 0 || strcmp(string, str4) == 0 ||
        strcmp(string, str5) == 0) 
        return TRUE;

    return FALSE;
}

void listLineReverse (const char *lineName, SystemData *systemData) {
    Line *line = lineNameToLine(lineName, systemData);
    /* if the line found has stops */
    if (line -> numberOfStops != 0) {
        /* print them in reverse order */
        Index * element = line -> indexesOfStops -> tail;
        printf("%s", stopIndexToName(element -> index, systemData));

        for (element = element -> previousIndex; element != NULL;
            element = element -> previousIndex)
            printf(", %s", stopIndexToName(element -> index, systemData));
    }
    putchar('\n');
}

/* CASE P */

void caseP (SystemData *systemData) {

    int c1;
    int coordinates;
    double stopLatitude, stopLongitude;
    /* checks if the command letter is followed by a '\n' character */
    if ((c1 = getchar()) == '\n')
        listAllStops(systemData);

    else {
        char stopName[MAX_INPUT];
        /* if the name is followed by a '\n' character */
        if (readWord(stopName) == TRUE) {

            int check = lookupStop(stopName, systemData);
            coordinates = scanf("%lf %lf", &stopLatitude, &stopLongitude);

            if (coordinates == 2) {
                /* if the stop doesn't exist creates a new one */
                if (check == ERROR)
                    if (-90 <= stopLatitude && stopLatitude <= 90 &&
                    -180 <= stopLongitude && stopLongitude <= 180)
                        createStop(stopName, stopLatitude, stopLongitude, systemData);
                    else 
                        printf("invalid location.\n");
                /* if it does raises an error */
                else
                    printf(STOP_ALREADY_EXISTS, stopName); 
            }
        }
        else {
            int check = lookupStop(stopName, systemData);
            /* if the stop exists prints its data */
            if (check != ERROR)
                listStop(stopName, systemData);
            /* if it doesn't raises an error */
            else
                printf(NO_SUCH_STOP, stopName);
        }
        
    }
}

void listAllStops (SystemData * systemData) {
    Stop * stop = systemData -> allStops -> head;
    /* iterates through all the system's stops */
    while (stop != NULL) {
        /* prints their data */
        printf("%s:", stop -> name);
        printf(" %16.12f", stop -> latitude);
        printf(" %16.12f", stop -> longitude);
        printf(" %d\n", countLines(stop -> stopIndex, systemData));
        stop = stop -> nextStop;
    }
}

void createStop (const char *stopName, double stopLatitude,
    double stopLongitude, SystemData *systemData) {
    /* alloc memory for new stop and its name */
    Stop *newStop = (Stop *) checksMalloc(systemData, sizeof(Stop));
    newStop -> name = (char *) checksMalloc(systemData, sizeof(char) * (strlen(stopName) + 1));
    /* set stop data */
    strcpy(newStop -> name, stopName);
    newStop -> latitude = stopLatitude;
    newStop -> longitude = stopLongitude;
    newStop -> stopIndex = systemData -> numberOfStops;
    /* add stop to systemData */
    insertStopEnd(systemData -> allStops, newStop);
    /* increment number of stops in the system */
    systemData -> numberOfStops ++;
}

void listStop (char *stopName, SystemData *systemData) {
    Stop * stop = stopNameToStop(stopName, systemData);
    printf("%16.12f ", stop -> latitude);
    printf("%16.12f\n", stop -> longitude);
}

int countLines (int stopIndex, SystemData *systemData) {
    int count = 0;
    Line * line = systemData -> allLines -> head;
    /* iterates through system's lines */
    while (line != NULL) {
        Index * element = line -> indexesOfStops -> head;
        /* iterates through each line's stops*/
        while (element != NULL) {
            /* if the index of the stop matches the index passed as
            argument, increments counter and breaks inner while loop */
            if (element -> index == stopIndex) {
                count ++;
                break;
            }
            element = element -> nextIndex;
        }
        line = line -> nextLine;
    }
    return count;
}

/* CASE L */

void caseL (SystemData * systemData) {

    char lineName[MAX_INPUT];
    char stopOriginName[MAX_INPUT];
    char stopDestinationName[MAX_INPUT];
    double linkCost, linkTime;
    /* read words from input */
    readWord(lineName);
    readWord(stopOriginName);
    readWord(stopDestinationName);
    scanf("%lf %lf", &linkCost, &linkTime);
    /* checks if the line and the stops exist, 
    if they don't raises an error */
    if (lookupLine(lineName, systemData) == ERROR)
        printf(NO_SUCH_LINE, lineName);
    else {
        if (lookupStop(stopOriginName, systemData) == ERROR)
            printf(NO_SUCH_STOP, stopOriginName);
        else if (lookupStop(stopDestinationName, systemData) == ERROR)
            printf(NO_SUCH_STOP, stopDestinationName);

        else {
            /* get structs for the line and the stops */
            Line * line = lineNameToLine(lineName, systemData);
            Stop * stopOrigin = stopNameToStop(stopOriginName, systemData);
            Stop * stopDestination = 
                stopNameToStop(stopDestinationName, systemData);
            /* if it is the first link */
            if (line -> numberOfStops == 0) {
                /* checks validity of linkCost and linkTime */
                if (linkCost >= 0 && linkTime >= 0) {
                    createFirstLink(line, stopOrigin, stopDestination,
                        linkCost, linkTime, systemData);
                    addLink(line, stopOrigin, stopDestination, linkCost,
                        linkTime, systemData);
                }
                else
                    printf(NEGATIVE_COST_DURATION);
            }
            else {
                /* if the link can be added to the line adds it,
                otherwise raises an error */
                if (checkDestinationStop(line, stopDestination -> stopIndex) == FALSE
                    && checkOriginStop(line, stopOrigin -> stopIndex) == FALSE)
                        printf(LINK_CANNOT_ASSOCIATE);
                else {
                    /* checks validity of linkCost and linkTime */
                    if (linkCost >= 0 && linkTime >= 0) {
                        createLink(line, stopOrigin, stopDestination, linkCost,
                            linkTime, systemData);
                        addLink(line, stopOrigin, stopDestination, linkCost,
                            linkTime, systemData);
                    }
                    else
                        printf(NEGATIVE_COST_DURATION);
                }
            }
        }
    }
}

void createFirstLink (Line *line, Stop *stopOrigin, Stop *stopDestination,
    double linkCost, double linkTime, SystemData *systemData) {
        /* alloc memory for 2 indexes */
        Index *index1 = (Index *) checksMalloc(systemData, sizeof(Index));
        Index *index2 = (Index *) checksMalloc(systemData, sizeof(Index));
        /* set indexes data */
        index1 -> nextIndex = index2;
        index1 -> previousIndex = NULL;
        index1 -> index = stopOrigin -> stopIndex;
        index2 -> nextIndex = NULL;
        index2 -> previousIndex = index1;
        index2 -> index = stopDestination -> stopIndex;
        /* set index 1 and 2 as head and tail of the list of stop indexes,
        respectively */
        line -> indexesOfStops -> head = index1;
        line -> indexesOfStops -> tail = index2;
        /* update line data */
        line -> numberOfStops = 2;
        line -> totalCost += linkCost;
        line -> totalTime += linkTime;
        /* add new link's index to the line's list of link indexes */
        addLinkIndexEnd(line -> indexesOfLinks, systemData);
}

void addLink (Line * line, Stop* stopOrigin, Stop * stopDestination,
    double linkCost, double linkTime, SystemData * systemData) {
        /* alloc memory for a new link */
        Link *newLink = (Link *) checksMalloc(systemData, sizeof(Link));
        /* set link data */
        newLink -> linkIndex = systemData -> numberOfLinks;
        newLink -> lineIndex = line -> lineIndex;
        newLink -> stopOriginIndex = stopOrigin -> stopIndex;
        newLink -> stopDestinationIndex = stopDestination -> stopIndex;
        newLink -> linkCost = linkCost;
        newLink -> linkTime = linkTime;
        /* add link to systemData */
        insertLinkEnd(systemData -> allLinks, newLink);
        /* increment number of links in the system */
        systemData -> numberOfLinks ++;
}

void createLink (Line *line, Stop *stopOrigin, Stop *stopDestination,
    double linkCost, double linkTime, SystemData *systemData) {

        int firstStopIndex = line -> indexesOfStops -> head -> index;
        int lastStopIndex = line -> indexesOfStops -> tail -> index;
        /* for circular lines */
        if (lastStopIndex == stopOrigin -> stopIndex && 
        firstStopIndex == stopDestination -> stopIndex) {
            addStopIndexEnd(line -> indexesOfStops, stopDestination, systemData);
            addLinkIndexEnd(line -> indexesOfLinks, systemData);
        }
        /* adding stop and link in the end */
        else if (lastStopIndex == stopOrigin -> stopIndex) {
            addStopIndexEnd(line -> indexesOfStops, stopDestination, systemData);
            addLinkIndexEnd(line -> indexesOfLinks, systemData);
        }
        /* adding stop and link in the beggining */
        else if (firstStopIndex == stopDestination -> stopIndex) {
            addStopIndexBeggining(line -> indexesOfStops, stopOrigin, systemData);
            addLinkIndexBeggining(line -> indexesOfLinks, systemData);
        }
        /* update line data */
        line -> numberOfStops ++;
        line -> totalCost += linkCost;
        line -> totalTime += linkTime;
}

int checkOriginStop (Line * line, int stopOriginIndex) {
    if (line -> indexesOfStops -> tail -> index == stopOriginIndex)
        return TRUE;
    return FALSE;
}

int checkDestinationStop (Line* line, int stopDestinationIndex) {
    if (line -> indexesOfStops -> head -> index == stopDestinationIndex)
        return TRUE;
    return FALSE;
}

/* CASE I */

void caseI (SystemData *systemData) {
    Stop * stop = systemData -> allStops -> head;
    int numberOfLines;
    /* iterates through the system's stops */
    while (stop != NULL) {
        numberOfLines = countLines(stop -> stopIndex, systemData);
        /* if there're itersections of line in that stop */
        if (numberOfLines > 1) {
            /* prints first part of the data */
            printf("%s %d:", stop -> name, numberOfLines);
            listLinesAlphabetically(stop -> stopIndex, systemData);      
        }
        stop = stop -> nextStop;  
    }
}

void listLinesAlphabetically (int stopIndex, SystemData *systemData) {
    /* create a list of words */
    listOfWords * listOfLineNames = createListOfWords(systemData);
    Line * line = systemData -> allLines -> head;

    while (line != NULL) {
        Index * element = line -> indexesOfStops -> head;
        while (element != NULL) {
            if (element -> index == stopIndex) {
                /* add name of line to a list to sort */
                insertWordEnd(listOfLineNames, line -> name, systemData);
                break;
            }
            element = element -> nextIndex;
        }
        line = line -> nextLine;
    }
    /* sort and print the created list */
    sortPrintLinkedListAlphabetically(listOfLineNames);
    /* free the created list */
    freeListOfWords(listOfLineNames);
}

void sortPrintLinkedListAlphabetically (listOfWords *linkedList) {

    Word * element1 = linkedList -> head;
    Word * element2 = linkedList -> head;
    int flag = 1;

    while (flag) {
        flag = 0;
        element1 = linkedList -> head;
        /* bubble sorts words in the linked list  with 
        added variable flag for efficiency */
        while (element1 -> nextWord != NULL) {
            if (strcmp(element1 -> word, element1 -> nextWord -> word) > 0) {
                swapWords(element1, element1 -> nextWord);
                flag = 1;
            }
            element1 = element1 -> nextWord;
        }     
    }
    /* iterates through the sorted list's words */
    while (element2 != NULL) {
        /* prints the list's words */
        printf(" %s", element2 -> word);
        element2 = element2 -> nextWord;
    }
    putchar('\n');
}

void swapWords(Word *element1, Word *element2) {
    char *temp = element1 -> word;
    element1 -> word = element2 -> word;
    element2 -> word = temp;
}

/* CASE R */

void caseR (SystemData *systemData) {

    char lineName[MAX_INPUT];
    readWord(lineName);
    /* if the line doesn't exist in the system raises an error */
    if(lookupLine(lineName, systemData) == ERROR)
        printf(NO_SUCH_LINE, lineName);
    else {
        freeLine(lineName, systemData);
        freeLineLinks(lineName, systemData);
    }
}

void freeLine (char lineName[], SystemData *systemData) {
    Line * lineToFree = lineNameToLine(lineName, systemData);
    Line * head = systemData -> allLines -> head;
    Line * tail = systemData -> allLines -> tail;
    /* if there is only 1 line */
    if (head -> lineIndex == tail -> lineIndex) {

        Line * auxLine = lineToFree;
        systemData -> allLines -> head = NULL;
        systemData -> allLines -> tail = NULL;

        free(auxLine -> name);
        freeListOfIndexes(auxLine -> indexesOfStops);
        freeListOfIndexes(auxLine -> indexesOfLinks);
        free(auxLine);

    }
    /* if it's freeing the first line */
    else if (lineToFree -> lineIndex == head -> lineIndex) {

        Line * auxLine = lineToFree;
        Line * lineAfter = lineToFree -> nextLine;
        systemData -> allLines -> head = lineAfter;

        free(auxLine -> name);
        freeListOfIndexes(auxLine -> indexesOfStops);
        freeListOfIndexes(auxLine -> indexesOfLinks);
        free(auxLine);
    }
    /* if it's freeing the last line */
    else if (lineToFree -> lineIndex == tail -> lineIndex) {
        
        Line * auxLine = lineToFree;
        Line * lineBefore = systemData -> allLines -> head;

        while (lineBefore -> nextLine -> lineIndex != lineToFree -> lineIndex)
            lineBefore = lineBefore -> nextLine;

        systemData -> allLines -> tail = lineBefore;
        lineBefore -> nextLine = NULL;

        free(auxLine -> name);
        freeListOfIndexes(auxLine -> indexesOfStops);
        freeListOfIndexes(auxLine -> indexesOfLinks);
        free(auxLine);
    }
    /* if its freeing a line in the middle */
    else {
        Line * lineBefore = systemData -> allLines -> head;

        while (lineBefore -> nextLine -> lineIndex != lineToFree -> lineIndex)
            lineBefore = lineBefore -> nextLine;

        lineBefore -> nextLine = lineToFree -> nextLine;

        free(lineToFree -> name);
        freeListOfIndexes(lineToFree -> indexesOfStops);
        freeListOfIndexes(lineToFree -> indexesOfLinks);
        free(lineToFree);
    } 
}

void freeLineLinks (char lineName[], SystemData *systemData) {
    Link * linkToFree = systemData -> allLinks -> head;
    int lineIndex = lookupLine(lineName, systemData);
    /* iterates through every link in the system */
    while (linkToFree != NULL) {
        /* if the link belongs to the line */
        if (linkToFree -> lineIndex == lineIndex)
            freeLink(linkToFree, systemData);
        linkToFree = linkToFree -> nextLink;
    }
}

void freeLink (Link *linkToFree, SystemData *systemData) {
    Link * head = systemData -> allLinks -> head;
    Link * tail = systemData -> allLinks -> tail;
    /* there's only 1 link in the system */
    if (head -> linkIndex == tail -> linkIndex) {

        Link * auxLink = linkToFree;
        systemData -> allLinks -> head = NULL;
        systemData -> allLinks -> tail = NULL;
        free(auxLink);
    }
    /* if it's the first link*/
    else if (linkToFree -> linkIndex == head -> linkIndex) {

        Link * auxLink = linkToFree;
        Link * linkAfter = linkToFree -> nextLink;
        systemData -> allLinks -> head = linkAfter;
        free(auxLink);
    }
    /* if it's the last link */
    else if (linkToFree -> linkIndex == tail -> linkIndex) {

        Link * auxLink = linkToFree;
        Link * linkBefore = systemData -> allLinks -> head;

        while (linkBefore -> nextLink -> linkIndex != linkToFree -> linkIndex)
            linkBefore = linkBefore -> nextLink;

        systemData -> allLinks -> tail = linkBefore;
        linkBefore -> nextLink = NULL;
        free(auxLink);
    }
    /* if the link is in the middle */
    else {
        Link * linkBefore = systemData -> allLinks -> head;

        while (linkBefore -> nextLink -> linkIndex != linkToFree -> linkIndex)
            linkBefore = linkBefore -> nextLink;

        linkBefore -> nextLink = linkToFree -> nextLink;
        free(linkToFree);
    } 
}

/* CASE E */
   
void caseE (SystemData *systemData) {

    char stopName[MAX_INPUT];
    int stopIndex;

    readWord(stopName);
    stopIndex = lookupStop(stopName, systemData);
    /* if the stop doesn't exist raises an error */
    if (stopIndex == ERROR)
        printf(NO_SUCH_STOP, stopName);
    else {
        if (countLines(stopIndex, systemData) != 0)
            removeStopLinks(stopIndex, systemData);
        freeStop(stopName, systemData);
    }
}

void removeStopLinks (int stopIndex, SystemData *systemData) {
    Line *line = systemData -> allLines -> head;
    /* iterates through the lines in the system */
    while (line != NULL) {
        Index *element = line -> indexesOfStops -> head;
        /* iterates through the line's list of stop indexes */
        while (element != NULL) {
            Index *auxElement = element -> nextIndex;
            if (element -> index == stopIndex) {
                /* find the previous and next stops to the one to remove */
                Index* previousStop = findPreviousStopLine(line, stopIndex);
                Index* nextStop = findNextStopLine(line, stopIndex);
                /* if the line has 2 stops/1 link */
                if (line -> numberOfStops == 2) {
                    /* clears line's data */
                    line -> numberOfStops = 0;
                    line -> totalCost = 0;
                    line -> totalTime = 0;
                    freeListOfIndexes(line -> indexesOfStops);
                    freeListOfIndexes(line -> indexesOfLinks);
                    line -> indexesOfStops = createListOfIndexes(systemData);
                    line -> indexesOfLinks = createListOfIndexes(systemData);
                    break;
                }
                else {
                    /* if the stop to remove is the first of the line */
                    if (previousStop == NULL)
                        removeStopLinkBeggining(line, stopIndex, systemData);  
                    /* if the stop to remove is the last of the line */            
                    else if (nextStop == NULL)
                        removeStopLinkEnd(line, stopIndex, systemData);
                    /* if the stop to remove is in the middle of the line */
                    else
                        removeStopLinkMiddle(line, stopIndex,
                            previousStop, nextStop, systemData);
                }
            }
            element = auxElement;
        }
        line = line -> nextLine;
    }
}

void freeStop (char *stopName, SystemData *systemData) {
    Stop * stopToFree = stopNameToStop(stopName, systemData);
    Stop * head = systemData -> allStops -> head;
    Stop * tail = systemData -> allStops -> tail;
    /* if there's only one stop in the system */
    if (head -> stopIndex == tail -> stopIndex) {
        Stop * auxStop = stopToFree;
        systemData -> allStops -> head = NULL;
        systemData -> allStops -> tail = NULL;
        free(auxStop -> name);
        free(auxStop);
    }
    /* if it is the first stop */
    else if (stopToFree -> stopIndex == head -> stopIndex) {
        Stop * auxStop = stopToFree;
        Stop * stopAfter = stopToFree -> nextStop;
        systemData -> allStops -> head = stopAfter;
        free(auxStop -> name);
        free(auxStop);
    }
    /* if it is the last stop */
    else if (stopToFree -> stopIndex == tail -> stopIndex) {
        Stop * auxStop = stopToFree;
        Stop * stopBefore = systemData -> allStops -> head;
        while (stopBefore -> nextStop -> stopIndex != stopToFree -> stopIndex)
            stopBefore = stopBefore -> nextStop;
        systemData -> allStops -> tail = stopBefore;
        stopBefore -> nextStop = NULL;
        free(auxStop -> name);
        free(auxStop);
    }
    /* if the stop is in the middle */
    else {
        Stop * stopBefore = systemData -> allStops -> head;
        while (stopBefore -> nextStop -> stopIndex != stopToFree -> stopIndex)
            stopBefore = stopBefore -> nextStop;
        stopBefore -> nextStop = stopToFree -> nextStop;
        free(stopToFree -> name);
        free(stopToFree);
    }
}

Index* findPreviousStopLine (Line *line, int stopIndex) {
    Index *element = line -> indexesOfStops -> head;
    /* iterates through the line's list of stop indexes */
    while (element != NULL) {
        /* when the element if found returns the previous */
        if (element -> index == stopIndex)
            return element -> previousIndex;
        element = element -> nextIndex;
    }
    return NULL;
}

Index * findNextStopLine (Line *line, int stopIndex) {
    Index *element = line -> indexesOfStops -> head;
    /* iterates through the line's list of stop indexes */
    while (element != NULL) {
        /* when the element if found returns the next */
        if (element -> index == stopIndex)
            return element -> nextIndex;
        element = element -> nextIndex;
    }
    return NULL;
}

void removeStopLinkBeggining (Line *line, int stopIndex, SystemData *systemData) {

    Index *nextStop = findNextStopLine(line, stopIndex);
    Index *linkIndexToFree = line -> indexesOfLinks -> head;
    Index *stopIndexToFree = line -> indexesOfStops -> head;
    int firstLinkIndex = linkIndexToFree -> index;
    Link *firstLink = linkIndexToLink(firstLinkIndex, systemData);
    double linkCost = firstLink -> linkCost;
    double linkTime = firstLink -> linkTime;
    Index *auxLink = linkIndexToFree;
    Index *auxStop = stopIndexToFree;
    /* updates line data */
    line -> numberOfStops --;
    line -> totalCost -= linkCost;
    line -> totalTime -= linkTime;
    /* remove first link from the line's list of link indexes */
    linkIndexToFree -> nextIndex -> previousIndex = NULL;
    line -> indexesOfLinks -> head = linkIndexToFree -> nextIndex;
    /* remove first link from the line's list of stop indexes */
    line -> indexesOfStops -> head = nextStop;
    nextStop -> previousIndex = NULL;
    /* frees previously allocated memory for removed link and stop */
    free(auxLink);
    free(auxStop);
}

void removeStopLinkEnd (Line *line, int stopIndex, SystemData *systemData) {

    Index *previousStop = findPreviousStopLine(line, stopIndex);
    Index *linkIndexToFree = line -> indexesOfLinks -> tail;
    Index *stopIndexToFree = line -> indexesOfStops -> tail;
    int lastLinkIndex = linkIndexToFree -> index;
    Link *lastLink = linkIndexToLink(lastLinkIndex, systemData);
    double linkCost = lastLink -> linkCost;
    double linkTime = lastLink -> linkTime;
    Index *auxLink = linkIndexToFree;
    Index *auxStop = stopIndexToFree;
    /* updates line data */
    line -> numberOfStops --;
    line -> totalCost -= linkCost;
    line -> totalTime -= linkTime;
    /* remove last link from the line's list of link indexes */
    line -> indexesOfLinks -> tail = linkIndexToFree -> previousIndex;
    line -> indexesOfLinks -> tail -> nextIndex = NULL;
    /* remove last stop from the line's list of stop indexes */
    line -> indexesOfStops -> tail = previousStop;
    previousStop -> nextIndex = NULL;
    /* frees previously allocated memory for removed link and stop */
    free(auxLink);
    free(auxStop);                                                                                                                                     
}

void removeStopLinkMiddle (Line *line, int stopIndex,
    Index *previousStopIndex, Index *nextStopIndex, SystemData *systemData) {

    Link *link = findLink(line, previousStopIndex -> index, stopIndex, systemData);
    Link *nextLink = findLink(line, stopIndex, nextStopIndex -> index, systemData);
    double newLinkCost = link -> linkCost + nextLink -> linkCost;
    double newLinkTime = link -> linkTime + nextLink -> linkTime;
    Index *element = findElementLine(line, previousStopIndex -> index,
        stopIndex, systemData);
    Index *auxElement = element;
    Index *stopToFree = previousStopIndex -> nextIndex;
    Index *auxStopToFree = stopToFree;
    /* updates line data */
    line -> numberOfStops --;
    previousStopIndex -> nextIndex = nextStopIndex;
    nextStopIndex -> previousIndex = previousStopIndex;

    auxRemoveStopLinkMiddle(line, link, previousStopIndex, nextStopIndex,
        newLinkCost, newLinkTime, element, auxElement);
    /* frees the stop */
    free(auxStopToFree);
}

void auxRemoveStopLinkMiddle(Line *line, Link *link, Index* previousStopIndex,
    Index *nextStopIndex, double newLinkCost, double newLinkTime,
    Index *element, Index *auxElement) {
    /* if there're only 2 links in the line */
    if (element -> previousIndex == NULL && element -> nextIndex -> nextIndex == NULL) {
        Index *auxElementToFree = auxElement -> nextIndex;
        changeLink(line, link, previousStopIndex -> index,
            nextStopIndex -> index, newLinkCost, newLinkTime);
        line -> indexesOfLinks -> head = element;
        line -> indexesOfLinks -> tail = element;
        element -> previousIndex = NULL;
        element -> nextIndex = NULL;
        free(auxElementToFree);
    }
    /* if the link to remove is the first of the list */
    else if (element -> previousIndex == NULL) {
        Index *auxElementToFree = auxElement -> nextIndex;
        changeLink(line, link, previousStopIndex -> index,
            nextStopIndex -> index, newLinkCost, newLinkTime);
        element -> previousIndex = NULL;
        element -> nextIndex = element -> nextIndex -> nextIndex;
        auxElementToFree -> nextIndex -> previousIndex = element; 
        free(auxElementToFree);
    }
    /* if the link to remove is the last of the list */
    else if (element -> nextIndex -> nextIndex == NULL) {
        Index *auxElementToFree = auxElement -> nextIndex;
        changeLink(line, link, previousStopIndex -> index,
            nextStopIndex -> index, newLinkCost, newLinkTime);
        line -> indexesOfLinks -> tail = element;
        element -> nextIndex = NULL;
        free(auxElementToFree);
    }
    /* if the link to remove is in the middle of the list */
    else {
        Index *auxElementToFree = auxElement -> nextIndex;
        changeLink(line, link, previousStopIndex -> index,
            nextStopIndex -> index, newLinkCost, newLinkTime);
        element -> nextIndex = element -> nextIndex -> nextIndex;
        auxElementToFree -> nextIndex -> previousIndex = element;
        free(auxElementToFree);
    }
}

void changeLink (Line *line, Link *link, 
    int newStopOriginIndex, int newStopDestinationIndex,
    double newLinkCost, double newLinkTime) {
    /* update the link's data to the passed arguments */
    link -> lineIndex = line -> lineIndex;
    link -> stopOriginIndex = newStopOriginIndex;
    link -> stopDestinationIndex = newStopDestinationIndex;
    link -> linkCost = newLinkCost;
    link -> linkTime = newLinkTime;
}

Link * findLink (Line *line, int stop1Index, int stop2Index,
    SystemData *systemData) {
    Index *element = line -> indexesOfLinks -> head;
    /* iterates through the line's list of link indexes */
    while (element != NULL) {
        Link *link = linkIndexToLink(element -> index, systemData);
        /* compares the links data with the passed arguments */
        if (link -> lineIndex == line -> lineIndex &&
            link -> stopOriginIndex == stop1Index &&
            link -> stopDestinationIndex == stop2Index)
            return link;
        element = element -> nextIndex;
    }
    return NULL;
}

Index * findElementLine (Line *line, int stop1Index, int stop2Index,
    SystemData *systemData) {
    /* iterate through the line's list of link indexes */
    Index *element = line -> indexesOfLinks -> head;
    while (element != NULL) {
        Link *link = linkIndexToLink(element -> index, systemData);
        /* compares the links data with the passed arguments */
        if (link -> lineIndex == line -> lineIndex &&
            link -> stopOriginIndex == stop1Index &&
            link -> stopDestinationIndex == stop2Index)
            return element;
        element = element -> nextIndex;
    }
    return NULL;
}

/* CASE A */

void caseA (SystemData *systemData) {
    /* frees everything inside systemData */
    freeListOfLines(systemData -> allLines);
    freeListOfStops(systemData -> allStops);
    freeListOfLinks(systemData -> allLinks);
    /* reinitialzes the counters */
    systemData -> numberOfLines = 0;
    systemData -> numberOfStops = 0;
    systemData -> numberOfLinks = 0;
    /* creates new lists for data inside systemData */
    systemData -> allLines = createListOfLines(systemData);
    systemData -> allStops = createListOfStops(systemData);
    systemData -> allLinks = createListOfLinks(systemData);
}

/* CASE F */

void caseF (SystemData *systemData) {
    char stopName[MAX_INPUT];
    int check;
    readWord(stopName);
    check = lookupStop(stopName, systemData);

    if (check == ERROR)
        printf(NO_SUCH_STOP, stopName);
    else
        showLines(check, systemData);
}

void showLines(int stopIndex, SystemData *systemData) {
    Line *line = systemData -> allLines -> head;
    int flag = 0;
    while (line != NULL) {
        Index *element = line -> indexesOfStops -> tail;
        if (element != NULL) {
            if (line -> indexesOfStops -> tail -> index == stopIndex) {
                printf("%s", line -> name);
                flag = 1;
                break;
            }
        }
        line = line -> nextLine;
    }
    if (line != NULL)
        line = line -> nextLine;
    while (line != NULL) {
        Index *element = line -> indexesOfStops -> tail;
        if (element != NULL) {
            if (line -> indexesOfStops -> tail -> index == stopIndex)
                printf(" %s", line -> name);
        }
        line = line -> nextLine;
    }
    if (flag)
        putchar('\n');
}

/* GENERAL FUNCTIONS */

int readWord (char str[]) {

	int c = getchar(), i = 0;
    /* skips blank spaces at the front of the word */
	while (c == ' ' || c == '\t')
		c = getchar();

    /* if the character sequence starts with quotes */
    if (c == '"') {
        c = getchar();
        /* reads and adds to a string until the next quote */
        while (c != '"' && c != '\n') {
            str[i++] = c;
		    c = getchar();
        }
    }
    /* if the character sequence starts with a letter */
    else 
        /* reads and adds to a string until the next space */
        while (c != ' ' && c != '\t' && c != '\n') {
            str[i++] = c;
		    c = getchar();   
        }
    /* adds '\0' to the end of the string */
    str[i] = '\0';

    /* returns boolean int: whether the input line has ended */
    return (c != '\n');
}

void * checksMalloc (SystemData *systemData, unsigned int size) {

    void * check = malloc(size);
	/* checks if it is possible to allocate memory */
	if (check != NULL)
		return check;
	else {
        /* clears the struct systemData */
        freeAll(systemData);
        printf("No memory.\n");
        return NULL;
    }
}

/* FIND STRUCTS */

Line * lineNameToLine (const char *lineName, SystemData * systemData) {
    Line * line = systemData -> allLines -> head;
    /* iterates through the system's lines */
    while (line != NULL) {
        if (strcmp(line -> name, lineName) == 0)
            return line;
        line = line -> nextLine;
    }
    return NULL;
}

Stop * stopNameToStop (const char *stopName, SystemData * systemData) {
    Stop * stop = systemData -> allStops -> head;
    /* iterates through the system's stops */
    while (stop != NULL) {
        if (strcmp(stop -> name, stopName) == 0)
            return stop;
        stop = stop -> nextStop;
    }
    return NULL;
}

Link * linkIndexToLink (int linkIndex, SystemData *systemData) {
    Link *link = systemData -> allLinks -> head;
    while (link != NULL) {
        if (link -> linkIndex == linkIndex)
            return link;
        link = link -> nextLink;
    }
    return NULL;
}

/* CHECK EXISTENCE */

int lookupLine (char *lineName, SystemData *systemData) {
    Line * l = systemData -> allLines -> head;
    /* iterates through systemData´s lines */
    while (l != NULL) {
        /* returs the index of the line with the name in the argument */
        if(strcmp(l -> name, lineName) == 0)
            return l -> lineIndex;
        l = l -> nextLine;
    }
    return ERROR;
}

int lookupStop (char *stopName, SystemData *systemData) {
    Stop * s = systemData -> allStops -> head;
    /* iterates through systemData´s stops */
    while (s != NULL) {
        /* returs the index of the line with the name in the argument */
        if(strcmp(s -> name, stopName) == 0)
            return s -> stopIndex;
        s = s -> nextStop;
    }
    return ERROR;
}

/* GET NAME */

char * stopIndexToName (int stopIndex, SystemData *systemData) {
    Stop * stop = systemData -> allStops -> head;
    /* iterates through the system's stops */
    while (stop != NULL) {
        if (stop -> stopIndex == stopIndex)
            return stop -> name;
        stop = stop -> nextStop;
    }
    return NULL;
}

/* CREATE LISTS */

listOfLines * createListOfLines (SystemData *systemData) {
    /* alloc memory for a list of lines */
	listOfLines * newList = (listOfLines *) checksMalloc(systemData, sizeof(listOfLines));
	newList -> head = NULL;
	newList -> tail = NULL;
	return newList;
}

listOfStops * createListOfStops (SystemData *systemData) {
    /* alloc memory for a list of stops */
	listOfStops * newList = (listOfStops *) checksMalloc(systemData, sizeof(listOfStops));
	newList -> head = NULL;
	newList -> tail = NULL;
	return newList;
}

listOfLinks * createListOfLinks (SystemData *systemData) {
    /* alloc memory for a list of links */
    listOfLinks * newList = (listOfLinks *) checksMalloc(systemData, sizeof(listOfLinks));
    newList -> head = NULL;
	newList -> tail = NULL;
	return newList;
}

listOfIndexes * createListOfIndexes (SystemData *systemData) {
    /* alloc memory for a list of indexes */
    listOfIndexes * newList = (listOfIndexes *) checksMalloc(systemData, sizeof(listOfIndexes));
    newList -> head = NULL;
    newList -> tail = NULL;

    return newList;
}

listOfWords * createListOfWords (SystemData *systemData) {
    /* alloc memory for a list of words */
    listOfWords * list = (listOfWords *) checksMalloc(systemData, sizeof(listOfWords));
    list -> head = NULL;
    return list;
}

/* ADD STRUCTS TO LISTS */

void insertLineEnd (listOfLines *linkedList, Line *newLine) {
    /* adds to list */
    /* if it's the first element in the list*/
	if (!linkedList -> head) {
		linkedList -> head = newLine;
		linkedList -> tail = newLine;
        newLine -> nextLine = NULL;
	}
    else {
        linkedList -> tail -> nextLine = newLine;
        linkedList -> tail = newLine;
        newLine -> nextLine = NULL;
    }
}

void insertStopEnd (listOfStops *linkedList, Stop *newStop) {
    /* adds to list */
    /* if it's the first element in the list*/
	if (!linkedList -> head) {
		linkedList -> head = newStop;
		linkedList -> tail = newStop;
        newStop -> nextStop = NULL;
	}
    else {
        linkedList -> tail -> nextStop = newStop;
        linkedList -> tail = newStop;
        newStop -> nextStop = NULL;
    }
}

void insertLinkEnd (listOfLinks * linkedList, Link * newLink) {
    /* adds to list */
    /* if it's the first element in the list*/
    if (linkedList -> head == NULL) {
        linkedList -> head = newLink;
        linkedList -> tail = newLink;
        newLink -> nextLink = NULL;
    }
    else {
        linkedList -> tail -> nextLink = newLink;
        linkedList -> tail = newLink;
        newLink -> nextLink = NULL;
    }
}

void insertWordEnd (listOfWords *linkedList, const char *word,
    SystemData *systemData) {
    /* alloc memory for a new word */
    Word *wordToAdd = (Word *) checksMalloc(systemData, sizeof(Word));
    wordToAdd -> word = (char *) checksMalloc(systemData, strlen(word) + 1);
    strcpy(wordToAdd -> word, word);
    /* adds to list */
    /* if it's the first element in the list*/
    if (!linkedList -> head) {
        linkedList -> head = wordToAdd;
        linkedList -> tail = wordToAdd;
        wordToAdd -> nextWord = NULL;
    }
    else {
        linkedList -> tail -> nextWord = wordToAdd;
        linkedList -> tail = wordToAdd;
        wordToAdd -> nextWord = NULL;
    }
}

void addLinkIndexBeggining (listOfIndexes *linkedList, SystemData *systemData) {
    /* alloc memory for new index and sets its data */
    Index *indexToAdd = (Index* ) checksMalloc(systemData, sizeof(Index));
    indexToAdd -> index = systemData -> numberOfLinks;
    /* adds to list */
    /* if it's the first element in the list*/
    if (!linkedList -> head) {
		linkedList -> head = indexToAdd;
		linkedList -> tail = indexToAdd;
        indexToAdd -> nextIndex = NULL;
        indexToAdd -> previousIndex = NULL;
	}
    else {
        indexToAdd -> previousIndex = NULL;
        indexToAdd -> nextIndex = linkedList -> head;
        linkedList -> head -> previousIndex = indexToAdd;
        linkedList -> head = indexToAdd;
    }  
}

void addLinkIndexEnd (listOfIndexes *linkedList, SystemData *systemData) {
    /* alloc memory for new index and sets its data */
    Index *indexToAdd = (Index* ) checksMalloc(systemData, sizeof(Index));
    indexToAdd -> index = systemData -> numberOfLinks;
    /* adds to list */
    /* if it's the first element in the list*/
    if (!linkedList -> head) {
		linkedList -> head = indexToAdd;
		linkedList -> tail = indexToAdd;
        indexToAdd -> nextIndex = NULL;
        indexToAdd -> previousIndex = NULL;
	}
    else {
        indexToAdd -> nextIndex = NULL;
        indexToAdd -> previousIndex = linkedList -> tail;
        linkedList -> tail -> nextIndex = indexToAdd;
        linkedList -> tail = indexToAdd;
    }
}

void addStopIndexBeggining (listOfIndexes * linkedList, Stop * stopToAdd,
    SystemData * systemData) {
    /* alloc memory for new index */
    Index *indexToAdd = (Index* ) checksMalloc(systemData, sizeof(Index));
    /* sets its data and adds it to the beggining of the linked list
    passed as argument */
    indexToAdd -> index = stopToAdd -> stopIndex;
    indexToAdd -> previousIndex = NULL;
    indexToAdd -> nextIndex = linkedList -> head;
    linkedList -> head -> previousIndex = indexToAdd;
    linkedList -> head = indexToAdd;
}

void addStopIndexEnd (listOfIndexes *linkedList, Stop *stopToAdd,
    SystemData *systemData) {
    /* alloc memory for new index */
    Index *indexToAdd = (Index *) checksMalloc(systemData, sizeof(Index));
    /* sets its data and adds it to the end of the linked list
    passed as argument */
    indexToAdd -> nextIndex = NULL;
    indexToAdd -> index = stopToAdd -> stopIndex;
    indexToAdd -> previousIndex = linkedList -> tail;
    linkedList -> tail -> nextIndex = indexToAdd;
    linkedList -> tail = indexToAdd;
}

/* FREE LISTS */

void freeAll (SystemData *systemData) {
    /* frees the struct systemData */
    freeListOfLines(systemData -> allLines);
    freeListOfStops(systemData -> allStops);
    freeListOfLinks(systemData -> allLinks);
    free(systemData);
}

void freeListOfLines (listOfLines *list) {
    Line * nextLineToFree = list -> head;
    Line * auxLine;
    /* iterates through the list of lines */
    while (nextLineToFree != NULL) {
        /* frees the line's name, lists and the line itself*/
        free(nextLineToFree -> name);
        freeListOfIndexes(nextLineToFree -> indexesOfStops);
        freeListOfIndexes(nextLineToFree -> indexesOfLinks);
        auxLine = nextLineToFree;
        nextLineToFree = nextLineToFree -> nextLine;
        free(auxLine);
    }
    /* frees the empty list */
    free(list);
}

void freeListOfStops (listOfStops *list) {
    Stop * nextStopToFree = list -> head;
    Stop * auxStop;
    /* iterates through the list of stops */
    while (nextStopToFree != NULL) {
        /* frees the stop´s name and the stop itself */
        free(nextStopToFree -> name);
        auxStop = nextStopToFree;
        nextStopToFree = nextStopToFree -> nextStop;
        free(auxStop);
    }
    /* frees the empty list*/
    free(list);
}

void freeListOfLinks (listOfLinks *list) {
    Link * nextLinkToFree = list -> head;
    Link * auxLink;
    /* iterates through the list of links */
    while (nextLinkToFree != NULL) {
        /* frees each link */
        auxLink = nextLinkToFree;
        nextLinkToFree = nextLinkToFree -> nextLink;
        free(auxLink);
    }
    /* frees the empty list */
    free(list);
}

void freeListOfIndexes (listOfIndexes *list) {
    Index * nextIndexToFree = list -> head;
    Index * auxIndex;
    /* iterates through the list of indexes */
    while (nextIndexToFree != NULL) {
        /* frees each index */
        auxIndex = nextIndexToFree;
        nextIndexToFree = nextIndexToFree -> nextIndex;
        free(auxIndex);
    }
    /* frees the empty list*/
    free(list);
}

void freeListOfWords (listOfWords *list) {
    Word * nextWordToFree = list -> head;
    Word * auxWord;
    /* iterates through the list of words */
    while (nextWordToFree != NULL) {
        /* frees the word and the struct word itself */
        free(nextWordToFree -> word);
        auxWord = nextWordToFree;
        nextWordToFree = nextWordToFree -> nextWord;
        free(auxWord);
    }
    /* frees the empty list */
    free(list);
}
#ifndef _STRUCTS_
#define _STRUCTS_

typedef struct Index {
    int index;
    struct Index *nextIndex;
    struct Index *previousIndex;
} Index;

typedef struct {
    Index *head;
    Index *tail;
} listOfIndexes;

typedef struct Stop {
    char *name;
    double latitude, longitude;
    int stopIndex;
    struct Stop *nextStop;
} Stop;

typedef struct {
    Stop *head;
    Stop *tail;
} listOfStops;

typedef struct Line {
    char *name;
    int numberOfStops, lineIndex;
    double totalCost, totalTime;
    listOfIndexes *indexesOfStops;
    listOfIndexes *indexesOfLinks;
    struct Line *nextLine;
} Line;

typedef struct {
    Line *head;
    Line *tail;
} listOfLines;

typedef struct Link {
    int lineIndex, linkIndex;
    int stopOriginIndex, stopDestinationIndex;
    double linkCost, linkTime;
    struct Link *nextLink;
} Link;

typedef struct {
    Link *head;
    Link *tail;
} listOfLinks;

typedef struct Word {
    char *word;
    struct Word *nextWord;
} Word;

typedef struct {
    Word *head;
    Word *tail;
} listOfWords;

/* instead of global variables */
typedef struct {
    int numberOfLines;
    int numberOfStops;
    int numberOfLinks;
    listOfLines *allLines;
    listOfStops *allStops;
    listOfLinks *allLinks;
} SystemData;

#endif
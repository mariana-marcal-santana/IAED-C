/* iaed-23 - ist1106992 - project1 */
/* A totalidade do código referente ao projeto 
encontra-se neste ficheiro.*/
/* Mariana Santana - ist1106992 */

#include <stdio.h>
#include <string.h>

/* DEFINITION OF CONSTANTS */

#define MAX_NAME_LENGTH_LINE 21
#define MAX_NAME_LENGTH_STOP 51
#define MAX_LENGTH_COMMAND_REVERSE 8
#define MAX_LINES 200
#define MAX_STOPS 10000
#define MAX_LINKS 30000

#define FALSE 0
#define TRUE 1
#define ERROR -1

/* DATA TYPES / STRUCTURES */

typedef struct {
    char name[MAX_NAME_LENGTH_STOP];
    double latitude, longitude;
} Stop;

typedef struct {
    char name[MAX_NAME_LENGTH_LINE];
    int numberOfStops;
    double totalCost, totalTime;
    int listOfStops[MAX_STOPS];
} Line;

/* GLOBAL VARIABLES */

int currentLines = 0;
Line arrayLines[MAX_LINES];

int currentStops = 0;
Stop arrayStops[MAX_STOPS];

/* GENERAL FUNCTIONS - used by multiple funtcions troughout the code */

/* int readWord (char str[]) - receives a string as an argument, reads a word
from the input line and saves it onto the variable str; returns wether the 
end of the input line has been reached  */

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

/* int lineExistsIndex (char name[]) - receives as argument a string with the
name of the line and checks if it exists in the system; if it does returns its
index, otherwise returns ERROR. */

int lineExistsIndex (char lineName[]) {
    int i;
    /* iterates trough arrayLines searching for lineName */
    for (i = 0; i < currentLines; i++) 
        if (strcmp(lineName, arrayLines[i].name) == 0)
            return i;
    return ERROR;
}

/* int stopExistsIndex (char name[]) - receives as argument a string with the
name of the stop and checks if it exists in the system; if it does returns its
index, otherwise returns ERROR. */

int stopExistsIndex (char stopName[]) {
    int i;
    /* iterates trough arrayStops searching for stopName */
    for (i = 0; i < currentStops; i++)
        if (strcmp(stopName, arrayStops[i].name) == 0)
            return i;
    return ERROR;
}

/* char * findLineName (int lineIndex) - receives as argument an int
(index) and returns the lineName corresponding to that index in arrayLines. */

char * findLineName (int lineIndex) {

    return arrayLines[lineIndex].name;
}

/* char * findStopName (int StopIndex) - receives as argument an int
(index) and returns the stopName corresponding to that index in arrayStops. */

char * findStopName (int stopIndex) {

    return arrayStops[stopIndex].name;
}

/* CASE C FUNCTIONS - functions used by the caseC function */

/* void listAllLines () - This function prints a list with information
about each line in the system, icluding its name; if the line has at least
1 link prints the name of the first and last stop, number of stops, cost and
time of the line, if it does not have links it prints just the number of stops,
cost and time (all of those values are 0). */

void listAllLines () {

    int i, numberOfStops;
    int stopOriginIndex, stopDestinationIndex;
    
    for (i = 0; i < currentLines; i++) {

        printf("%s ", arrayLines[i].name);
        numberOfStops = arrayLines[i].numberOfStops;

        /* if the line has at least 1 link */
        if (numberOfStops >= 2) {

            stopOriginIndex = arrayLines[i].listOfStops[0];
            stopDestinationIndex = arrayLines[i].listOfStops[numberOfStops - 1];

            printf("%s ", findStopName(stopOriginIndex));
            printf("%s ", findStopName(stopDestinationIndex));
            printf("%d ", numberOfStops);
            printf("%.2f ", arrayLines[i].totalCost);
            printf("%.2f\n", arrayLines[i].totalTime);
        }

        else
            printf("0 0.00 0.00\n");
    }
}

/* void listLine (int index) - This function receives an int (index of
the line to list) and lists all the stops of the corresponding line by order
of the route. */

void listLine (int index) {

    int i, stopIndex = arrayLines[index].listOfStops[0];

    /* if the line has stops */
    if (arrayLines[index].numberOfStops != 0) {

        printf("%s", findStopName(stopIndex));
        /* iterates trough the listOfStops and prints its contents */
        for (i = 1; i < arrayLines[index].numberOfStops; i++) {
            stopIndex = arrayLines[index].listOfStops[i];
            printf(", %s", findStopName(stopIndex));
        }
        putchar('\n');
    }
}

/* void createLine (char lineName[]) - This functions receives as argument a
string of the name of a non existent line and creates a new line by
initializing the values of the structure as 0. */

void createLine (char lineName[]) {

    /* places the new line in the first available index in arrayLines and
    inicializes the struct values */
    strcpy(arrayLines[currentLines].name, lineName);
    arrayLines[currentLines].numberOfStops = 0;
    arrayLines[currentLines].totalCost = 0;
    arrayLines[currentLines].totalTime = 0;
    /* increments the number of lines in the system */
    currentLines ++;
}

/* int isReverse (char string[]) - receives as argument a string (array of
characters) and checks if the string matches the word "inverso" or any of
its abreviations up to 3 characters. */

int isReverse (char string[]) {

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

/* void listLineReverse (int index) - This function receives an int
(index of the line to list) and lists all the stops of the corresponding line
by opposite order of the route. */

void listLineReverse (int index) {
    
    int i;
    int numberOfStops = arrayLines[index].numberOfStops;
    int stopIndex = arrayLines[index].listOfStops[numberOfStops - 1];

    printf("%s", findStopName(stopIndex));
    /* iterates trough the listOfStops (from end to start) 
    and prints its contents */
    for (i = numberOfStops - 2; i >= 0; i--) {
        stopIndex = arrayLines[index].listOfStops[i];
        printf(", %s", findStopName(stopIndex));
    }
    putchar('\n');
}

/* CASE P FUNCTIONS - functions used by the caseP function */

/* int countLines (int stopIndex) - This function receives as argument an
int (stopIndex) and counts the number of lines going through that
stop. */

int countLines (int stopIndex) {

    int i, j, count = 0;

    for (i = 0; i < currentLines; i++)
        for (j = 0; j < arrayLines[i].numberOfStops; j++)
            if (arrayLines[i].listOfStops[j] == stopIndex) {
                /* when the a stop is found once in the line the counter is
                incremented and for second for loop is broken */
                count ++;
                break;
            }
    return count;
}

/* void listAllStops () - This function prints information about each stop in
the system: stopName, its coordinates and the number of lines going 
through it. */

void listAllStops () {

    int i;

    for (i = 0; i < currentStops; i++) {
        printf("%s:", arrayStops[i].name);
        printf(" %16.12f", arrayStops[i].latitude);
        printf(" %16.12f", arrayStops[i].longitude);
        printf(" %d\n", countLines(i));
    }
}

/* void listStop (int index) - This function receives an int (index of
the stop to list) and prints its coordinates. */

void listStop (int index) {

    printf("%16.12f ", arrayStops[index].latitude);
    printf("%16.12f\n", arrayStops[index].longitude);
}

/* void createStop (char stopName[], double stopLatitude, double stopLongitude)
- This function receives as arguments a string, stopName and 2 doubles and sets
these values as the name and coordinates of a new stop in the system. */

void createStop (char stopName[], double stopLatitude, 
    double stopLongitude) {

    /* places the new stop in the first available index in arrayStops and
    inicializes the struct values */
    strcpy(arrayStops[currentStops].name, stopName);
    arrayStops[currentStops].latitude = stopLatitude;
    arrayStops[currentStops].longitude = stopLongitude;
    currentStops ++;
}

/* CASE L FUNCTIONS - functions used by the caseL function */

/* int checkOriginStop (char lineName[], char stopOriginName[]) - This function
receives as argument 2 strings: a lineName and a stopOriginName, checks if
the stopOrigin is the last stop in the listOfStops of the line passed as
argument and returns TRUE if it is and FALSE otherwise. */

int checkOriginStop (char lineName[], char stopOriginName[]) {
    
    int lineIndex = lineExistsIndex(lineName);
    int numberOfStops = arrayLines[lineIndex].numberOfStops;
    int stopIndex = arrayLines[lineIndex].listOfStops[numberOfStops - 1];
    
    if (strcmp(stopOriginName, findStopName(stopIndex)) == 0)
        return TRUE;
    return FALSE;
}

/* int checkDestinationStop (char lineName[], char stopDestinationName[]) -
This function receives as argument 2 strings: a lineName and a 
stopDestinationName, checks if the stopDestination is the first stop in the
listOfStops of the line passed as argument and returns TRUE if it is and 
FALSE otherwise. */

int checkDestinationStop (char lineName[], char stopDestinationName[]) {

    int lineIndex = lineExistsIndex(lineName);
    int stopIndex = arrayLines[lineIndex].listOfStops[0];

    if (strcmp(stopDestinationName, findStopName(stopIndex)) == 0)
        return TRUE;
    return FALSE;
}

/* void shiftsStops (int lineIndex, int listOfStops[], char stopName[]) -
This function receives an int lineIndex, an array of ints listofStops and
a string with the name of the stop to add to the listOfStops. */

void shiftsStops (int lineIndex, int listOfStops[], char stopName[]) {
    
    int i;
    int numberOfStops = arrayLines[lineIndex].numberOfStops;

    /* shifts all elements of the array from index x to index x+1 */
    for (i = numberOfStops; i > 0; i--)
        listOfStops[i] = listOfStops[i - 1];
    /* adds the index of the stop to the first place of the array */
    listOfStops[0] = stopExistsIndex(stopName);
}

void createLink (char lineName[], char stopOriginName[], 
    char stopDestinationName[], double linkCost, double linkTime) {

    int lineIndex = lineExistsIndex(lineName);
    int numberOfStops = arrayLines[lineIndex].numberOfStops;
    /* if the link is the first of the line */
    if (numberOfStops == 0) {

        arrayLines[lineIndex].listOfStops[0] = stopExistsIndex(stopOriginName);
        arrayLines[lineIndex].listOfStops[1] = stopExistsIndex(stopDestinationName);
        arrayLines[lineIndex].numberOfStops = 2;
        arrayLines[lineIndex].totalCost += linkCost;
        arrayLines[lineIndex].totalTime += linkTime; 
    }
    else {

        int firstStopIndex, lastStopIndex;
        int stopOriginIndex, stopDestinationIndex;
        firstStopIndex = arrayLines[lineIndex].listOfStops[0];
        lastStopIndex = arrayLines[lineIndex].listOfStops[numberOfStops - 1];
        stopOriginIndex = stopExistsIndex(stopOriginName);
        stopDestinationIndex = stopExistsIndex(stopDestinationName);

        /* for circular lines */
        if (lastStopIndex == stopOriginIndex && 
        firstStopIndex == stopDestinationIndex)
            arrayLines[lineIndex].listOfStops[numberOfStops] = stopDestinationIndex;
        /* for adding a stop in the end */
        else if (lastStopIndex == stopOriginIndex)
            arrayLines[lineIndex].listOfStops[numberOfStops] = stopDestinationIndex;
        /* for adding a stop at the beggining */     
        else if (firstStopIndex == stopExistsIndex(stopDestinationName))
            shiftsStops(lineIndex, arrayLines[lineIndex].listOfStops, stopOriginName);

        /* incrementing numberOfStops by 1 and adding the cost and time of the
        link to the cost and time of the line */
        arrayLines[lineIndex].numberOfStops ++;
        arrayLines[lineIndex].totalCost += linkCost;
        arrayLines[lineIndex].totalTime += linkTime;
    }
}

/* CASE I FUNCTIONS - functions used by the caseI function */

/* void sortarrayAlphabetically (int arrayLinesIndexes[], int numberOfLines)
- This function receives as argument an array with lineIndexes and and int
numberOfLines and bubble sorts a array of lineNames alphabetically. */

void sortarrayAlphabetically (int arrayLinesIndexes[], int numberOfLines) {

    char arrayLinesNames[MAX_LINES][MAX_NAME_LENGTH_LINE];
    int i, j;
    char auxName[MAX_NAME_LENGTH_LINE];

    /* puts in the array arrayLinesNames the lineName correspondig to the
    lineIndex in the same index of the arrayLinesIndexes array */
    for (i = 0; i < numberOfLines; i++)
        strcpy(arrayLinesNames[i], findLineName(arrayLinesIndexes[i]));

    /* uses bubble sort on the array to sort the words */
    for (i = 0; i < numberOfLines - 1; i++)
        for (j = i + 1; j < numberOfLines; j++)
            if (strcmp(arrayLinesNames[i], arrayLinesNames[j]) > 0) {
                strcpy(auxName, arrayLinesNames[i]);
                strcpy(arrayLinesNames[i], arrayLinesNames[j]);
                strcpy(arrayLinesNames[j], auxName);
            }
    /* prints the lines in alphabetical order */
    for (i = 0; i < numberOfLines; i++)
        printf(" %s", arrayLinesNames[i]);

    putchar('\n');
}

/* void listLinesAlphabetically (int stopIndex, int numberOfLines) - This
function receives 2 ints: stopIndex and numberOfLines and adds lineIndexes
to an array, prints part of the information for the command and calls the 
function sortarrayAlphabetically for the created array. */

void listLinesAlphabetically (int stopIndex, int numberOfLines) {

    int i, j, k = 0, arrayLinesIndexes[MAX_LINES];
    
    /* adds to the array arrayLinesIndexes the indexes of lines that go
    through the stop corresponding to the stopIndex */
    for (i = 0; i < currentLines; i++)
        for (j = 0; j < arrayLines[i].numberOfStops; j++)
            if (arrayLines[i].listOfStops[j] == stopIndex) {
                arrayLinesIndexes[k++] = i;
                break;
            }
    /* prints the stop name and its number of lines */
    printf("%s %d:", findStopName(stopIndex), numberOfLines);

    sortarrayAlphabetically(arrayLinesIndexes, numberOfLines);
}

/* COMMAND FUNCTIONS */

/* void caseC () - This functions checks the arguments in the C command line
and executes it according to the number of arguments and validity of the 
information on the input line. */

void caseC () {

    char c1;
    
    /* checks if the command letter is followed by a '\n' character */
    if ((c1 = getchar()) == '\n')
        listAllLines();

    else {
        /* collects lineName from the input */
        char lineName[MAX_NAME_LENGTH_LINE];
        /* if the name is followed by a '\n' character */
        if (readWord(lineName) == FALSE) {
            /* if the line exists lists its stops */
            if (lineExistsIndex(lineName) != ERROR)
                listLine(lineExistsIndex(lineName));
            /* if it does not exist creates a new line */
            else
                createLine(lineName);
        }
        else {
            /* initializes and collects the next word from the input */
            char command[MAX_LENGTH_COMMAND_REVERSE];
            readWord(command);

            /* checks if the collected word matches a reverse command */
            if (isReverse(command) == TRUE)
                listLineReverse(lineExistsIndex(lineName)); 
            /* if it does not prints an error */
            else 
                printf("incorrect sort option.\n");  
        }
    }    
}

/* void caseP () - This functions checks the arguments in the P command line
and executes it according to the number of arguments and validity of the 
information on the input line. */

void caseP () {

    int c1;
    int coordinates;
    double stopLatitude, stopLongitude;

    /* checks if the command letter is followed by a '\n' character */
    if ((c1 = getchar()) == '\n')
        listAllStops();

    else {
        /* collects stopName from the input */
        char stopName[MAX_NAME_LENGTH_STOP];
        /* if the name is not followed by a '\n' character */
        if (readWord(stopName) == TRUE) {
            /* gets the stops coordinates from the input and assings the number
            of coordinates read to the variabel coordinates */
            coordinates = scanf("%lf %lf", &stopLatitude, &stopLongitude);

            if (coordinates == 2) {
                /* if the stop does not exist yet creates a new one */
                if (stopExistsIndex(stopName) == ERROR) {
                    createStop(stopName, stopLatitude, stopLongitude);
                }
                /* if it exists prints an error */
                else
                    printf("%s: stop already exists.\n", stopName); 
            }
        }
        else {
            /* if the stop exists lists its coordinates */
            if (stopExistsIndex(stopName) != ERROR)
                listStop(stopExistsIndex(stopName));
            /* if it does not exist prints an error */
            else
                printf("%s: no such stop.\n", stopName);
            }
        
    }
}

/* void caseL () - This functions collects a lineName, 2 stopNames and data
about the link; it checks the validity of the parameters and if and where to
add the link in the corresponding line and adds it. */

void caseL () {

    char lineName[MAX_NAME_LENGTH_LINE];
    char stopOriginName[MAX_NAME_LENGTH_STOP];
    char stopDestinationName[MAX_NAME_LENGTH_STOP];
    int data;
    double linkCost, linkTime;
    /* collects names and data from the input */
    readWord(lineName);
    readWord(stopOriginName);
    readWord(stopDestinationName);
    data = scanf("%lf %lf", &linkCost, &linkTime);

    /* checks validity of the line */
    if (lineExistsIndex(lineName) == ERROR)
        printf("%s: no such line.\n", lineName);
    else {
        /* checks validity of the stops */
        if (stopExistsIndex(stopOriginName) == ERROR)
            printf("%s: no such stop.\n", stopOriginName);
        else if (stopExistsIndex(stopDestinationName) == ERROR)
            printf("%s: no such stop.\n", stopDestinationName);

        else {
            /* if it is the first link in the line it does not check whether
            the link can be associated with the line */
            if (arrayLines[lineExistsIndex(lineName)].numberOfStops == 0 &&
                data == 2 && linkCost > 0 && linkTime > 0) 
                /* positions the link in its proper place in the line */
                createLink(lineName, stopOriginName, stopDestinationName,
                        linkCost, linkTime);
            else {
                /* checks if the link can be added to the line */
                if (checkOriginStop(lineName, stopOriginName) == FALSE &&
                    checkDestinationStop(lineName, stopDestinationName) == FALSE)
                    printf("link cannot be associated with bus line.\n");
                else {
                    if (data == 2) {
                        /* checks the validity of the introduced values */
                        if (linkCost < 0 || linkTime < 0)
                            printf("negative cost or duration.\n");
                        else
                            /* positions the link in its proper place in the line */
                            createLink(lineName, stopOriginName, stopDestinationName,
                                linkCost, linkTime);
                    } 
                }
            }
        }
    }
}

/* void caseI () - This function checks for multiples lines going through
each stop and prints the stopName followed by the number of lines and an
alphabetically sorted list of the lines. */

void caseI () {

    int i, numberOfLines;

    for (i = 0; i < currentStops; i++) {
        numberOfLines = countLines(i);
        /* if there is more than 1 line going through the stop */
        if (numberOfLines > 1)
            listLinesAlphabetically(i, numberOfLines);
    }
}

/* int main () - The main functions gets the first character 
of the input line and directs the program to the corresponding command. */

int main () {

    int c;
    
    while ((c = getchar()) != EOF) {
		switch (c) {
            case 'q':
                return 0;
            case 'c': caseC();
                break;
            case 'p': caseP();
                break;
            case 'l': caseL();
                break;
            case 'i': caseI();
                break;
        }
    }
    return 0;  
}
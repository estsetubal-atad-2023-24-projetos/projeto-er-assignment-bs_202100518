#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "helpers.h"
#include "input.h"
#include "list.h"

#define MAX_NUMS_STR 200

int startMenu() {
    int res = -1;

    printf("\n---------- Olympics Super Parser ----------\n");
    printf("1. LOAD_A - Loads all athletes in athletes.csv.\n");
    printf("2. LOAD_M - Loads all medals in medals.csv.\n");
    printf("3. LOAD_M - Loads all hosts in hosts.csv.\n");
    printf("4. CLEAR - Clears all data in memory.\n");
    printf("5. SHOW_ALL - Shows all athletes.\n");
    printf("6. SHOW_PARTICIPATIONS - Shows all athletes that participated x amount.\n");
    printf("7. SHOW_FIRST - Shows all athletes that first participated in x year.\n");
    printf("8. SHOW_HOST - Show a specific host data.\n");
    printf("9. DISCIPLINE_STATISTICS - Shows statistics about a given discipline\n");
    printf("10. ATHLETE_INFO - Shows info about an athlete\n");
    printf("11. TOPN - N athletes with most medals\n");
    printf("0. QUIT - Leaves the program (all data is cleared).\n");
    printf("-------------------------------------------\n\n");

    printf("Input -> ");

    fflush(stdin);
    readInteger(&res);

    return res;
}

int getNumbersFromString(char *str) {
    char *p = str;

    int numbers = 0;
    while (*p)
        if (isdigit(*p) || ((*p == '-' || *p=='+') && isdigit(*(p+1))))
            numbers = concatenate(numbers, strtol(p, &p, 10));  // Read number
        else p++; // Move to next char

    return numbers;
}

char* getCharsOnlyFromString(char *str) {
    char *p = str;

    char *finalString = malloc(strlen(str) + 1);
    if (finalString == NULL) return NULL;

    int i = 0;
    while(*p) {
        if(!isdigit(*p)) finalString[i++] = *p;
        p++;
    }

    // Terminate the string
    finalString[i] = '\0';

    return finalString;
}

int getDateDiffInDays(char *startDate, char *endDate) {
    int startYear = 0, startMonth = 0, startDay = 0;
    int endYear = 0, endMonth = 0, endDay = 0;

    // Parse start date
    int res = sscanf(startDate, "%d-%d-%dT", &startYear, &startMonth, &startDay);

    if(res != 3) return -1;

    // Parse end date
    res = sscanf(endDate, "%d-%d-%dT", &endYear, &endMonth, &endDay);

    if(res != 3) return -1;

    // Get julian days (number of days since January 1, 4713 BCE)
    // Unix time would be better, but there may be records dating further
    // than 1970 year, that would result in negative values
    int startJulian = dateToJulianDay(startYear, startMonth, startDay);
    int endJulian = dateToJulianDay(endYear, endMonth, endDay);

    return abs(endJulian - startJulian);
}

int dateToJulianDay(int year, int month, int day) {
    if (month < 3) {
        year--;
        month += 12;
    }

    int A = year / 100;
    int B = A / 4;
    int C = 2 - A + B;
    int D = 365.25 * (year + 4716);
    int E = 30.6001 * (month + 1);

    return D + E + day + C - 1524;
}


int concatenate(int x, int y) {
    int pow = 10;
    while(y >= pow) pow *= 10;
    
    return x * pow + y;        
}

void clearScreen(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void quickSort(PtList *athletes, int low, int high) {
    if (low >= high) return;

    int pivot = partition(athletes, low, high);

    quickSort(athletes, low, pivot - 1); // Sort first half
    quickSort(athletes, pivot + 1, high); // Sort second half
}

// Selects the last element (pivot) and moves all athletes with name lesser than
// the pivot to the left, and greater to the right
int partition(PtList *athletes, int low, int high) {
    // Get pivot
    Athlete pivotAth;
    listGet(*athletes, high, &pivotAth);

    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        Athlete currentAth;
        listGet(*athletes, j, &currentAth);

        if (strcmp(currentAth.athleteName, pivotAth.athleteName) < 0) {
            i++;
            swapAthletes(athletes, i, j);
        }
    }

    swapAthletes(athletes, i + 1, high);
    return (i + 1);
}

void swapAthletes(PtList *athletes, int i, int j) {
    Athlete ath1, ath2;
    listGet(*athletes, i, &ath1);
    listGet(*athletes, j, &ath2);

    listSet(*athletes, i, ath2, NULL);
    listSet(*athletes, j, ath1, NULL);
}

int getYearFromDate(char* date) {
    int year;

    sscanf(date, "%d-", &year);

    return year;
}

char* stringToLower(char* str) {
    if (str == NULL) return NULL;
    
    char* lowercase = malloc(strlen(str) + 1);
    if (lowercase == NULL) return NULL;
    
    for (int i = 0; str[i] != '\0'; i++)
        lowercase[i] = tolower((char)str[i]);
    
    // Terminate string
    lowercase[strlen(str)] = '\0';
    
    return lowercase;
}
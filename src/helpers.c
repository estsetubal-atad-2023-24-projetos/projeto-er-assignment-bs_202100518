/**
 * @file helpers.c
 * @brief Implementation file for helper functions used throughout the Olympics Super Parser program.
 *
 * This file includes implementations of utility functions that assist with string manipulation,
 * sorting algorithms, data parsing, and other general-purpose functionalities to support
 * the main operations of the program. Functions include date handling, string processing,
 * quick sort algorithm for lists, and more.
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "helpers.h"
#include "input.h"
#include "list.h"

#define MAX_NUMS_STR 200

/**
 * @brief Displays the start menu and captures user choice.
 * @return The user's menu choice as an integer.
 */
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

/**
 * @brief Extracts integers from a string.
 * @param str The string to extract numbers from.
 * @return A concatenated integer of all numbers found in the string.
 */
int getNumbersFromString(char *str) {
    char *p = str;

    int numbers = 0;
    while (*p)
        if (isdigit(*p) || ((*p == '-' || *p=='+') && isdigit(*(p+1))))
            numbers = concatenate(numbers, strtol(p, &p, 10));  // Read number
        else p++; // Move to next char

    return numbers;
}

/**
 * @brief Extracts non-numeric characters from a string and returns them as a new string.
 * @param str The string to process.
 * @return A new string containing only non-numeric characters.
 */
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

/**
 * @brief Calculates the difference in days between two dates.
 * @param startDate The start date in the format "YYYY-MM-DDT".
 * @param endDate The end date in the format "YYYY-MM-DDT".
 * @return The number of days between the two dates.
 */
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

/**
 * @brief Converts a given date to the Julian day number.
 * @param year Year of the date.
 * @param month Month of the date.
 * @param day Day of the date.
 * @return Julian day number.
 */
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

/**
 * @brief Concatenates two integers.
 * @param x First integer.
 * @param y Second integer.
 * @return Concatenated result as an integer.
 */
int concatenate(int x, int y) {
    int pow = 10;
    while(y >= pow) pow *= 10;
    
    return x * pow + y;        
}

/**
 * @brief Clears the terminal screen based on the operating system.
 */
void clearScreen(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

/**
 * @brief Implements the quick sort algorithm on a list of athletes.
 * @param athletes Pointer to the list of athletes.
 * @param low Starting index.
 * @param high Ending index.
 */
void quickSort(PtList *athletes, int low, int high) {
    if (low >= high) return;

    int pivot = partition(athletes, low, high);

    quickSort(athletes, low, pivot - 1); // Sort first half
    quickSort(athletes, pivot + 1, high); // Sort second half
}

/**
 * @brief Partitions the list around a pivot for quick sort.
 * @param athletes Pointer to the list of athletes.
 * @param low Starting index.
 * @param high Ending index.
 * @return New pivot index.
 */
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

/**
 * @brief Swaps two athletes in a list.
 * @param athletes Pointer to the list of athletes.
 * @param i Index of the first athlete.
 * @param j Index of the second athlete.
 */
void swapAthletes(PtList *athletes, int i, int j) {
    Athlete ath1, ath2;
    listGet(*athletes, i, &ath1);
    listGet(*athletes, j, &ath2);

    listSet(*athletes, i, ath2, NULL);
    listSet(*athletes, j, ath1, NULL);
}


/**
 * @brief Extracts the year from a date string.
 * @param date Date string in the format "YYYY-MM-DD".
 * @return The year as an integer.
 */
int getYearFromDate(char* date) {
    int year;

    sscanf(date, "%d-", &year);

    return year;
}

/**
 * @brief Converts a string to lowercase.
 * @param str String to convert.
 * @return A new string in lowercase.
 */
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
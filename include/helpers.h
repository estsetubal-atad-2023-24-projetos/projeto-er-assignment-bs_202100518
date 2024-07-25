/**
 * @file helpers.h
 * @brief Header file for helper functions used in the Olympics Super Parser program.
 *
 * Declares utility functions for string manipulation, sorting algorithms,
 * date handling, and other general-purpose functions that support various
 * operations across the program. These functions include user interface
 * components, date calculations, quick sort implementation, and more.
 */
#pragma once

#include "list.h"

/**
 * @brief Displays the start menu and captures user input for menu selection.
 * @return The selected menu option as an integer.
 */
int startMenu();

/**
 * @brief Extracts all numeric values from a string and concatenates them into an integer.
 * @param str String containing numbers and other characters.
 * @return Integer formed by concatenating all numbers found in the string.
 */
int getNumbersFromString(char *str);

/**
 * @brief Extracts only alphabetical characters from a string and returns a new string.
 * @param str The original string containing both digits and characters.
 * @return A dynamically allocated string containing only the characters from the original string.
 */
char* getCharsOnlyFromString(char *str);

/**
 * @brief Calculates the number of days between two dates.
 * @param startDate The starting date in YYYY-MM-DD format.
 * @param endDate The ending date in YYYY-MM-DD format.
 * @return The difference in days between the two dates, or -1 if there is an error.
 */
int getDateDiffInDays(char *startDate, char *endDate);

/**
 * @brief Converts a Gregorian date to Julian Day Number.
 * @param year Year of the date.
 * @param month Month of the date.
 * @param day Day of the date.
 * @return The Julian Day Number corresponding to the provided date.
 */
int dateToJulianDay(int year, int month, int day);

/**
 * @brief Concatenates two integers into one.
 * @param x The first integer.
 * @param y The second integer to be appended to the first.
 * @return The new integer formed by concatenating x and y.
 */
int concatenate(int x, int y);

/**
 * @brief Clears the console screen based on the operating system.
 */
void clearScreen();

/**
 * @brief Implements a quick sort on a list of athletes.
 * @param athletes Pointer to the list of athletes.
 * @param low The starting index for the sort.
 * @param high The ending index for the sort.
 */
void quickSort(PtList *athletes, int low, int high);

/**
 * @brief Partitions a list for quick sorting by selecting a pivot and reordering elements.
 * @param athletes Pointer to the list of athletes.
 * @param low The lower index for partitioning.
 * @param high The higher index for partitioning.
 * @return The index of the pivot after partitioning.
 */
int partition(PtList *athletes, int low, int high);

/**
 * @brief Swaps two athletes in a list.
 * @param athletes Pointer to the list of athletes.
 * @param i Index of the first athlete.
 * @param j Index of the second athlete to swap with the first.
 */
void swapAthletes(PtList *athletes, int i, int j);

/**
 * @brief Extracts the year from a date string.
 * @param date The date string in the format YYYY-MM-DD.
 * @return The year as an integer.
 */
int getYearFromDate(char* date);

/**
 * @brief Converts a string to lowercase.
 * @param str The string to convert.
 * @return A dynamically allocated string containing the lowercase version of the input.
 */
char* stringToLower(char* str);

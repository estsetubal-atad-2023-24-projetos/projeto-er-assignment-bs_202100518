#pragma once

#include "list.h"

int startMenu();

int getNumbersFromString(char *str);

char* getCharsOnlyFromString(char *str);

int getDateDiffInDays(char *startDate, char *endDate);

int dateToJulianDay(int year, int month, int day);

int concatenate(int x, int y);

void clearScreen();

void quickSort(PtList *athletes, int low, int high);

int partition(PtList *athletes, int low, int high);

void swapAthletes(PtList *athletes, int i, int j);

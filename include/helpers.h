#pragma once

#include "list.h"

int startMenu();

int getNumbersFromString(char *str);

int concatenate(int x, int y);

void clearScreen();

void quickSort(PtList *athletes, int low, int high);

int partition(PtList *athletes, int low, int high);

void swapAthletes(PtList *athletes, int i, int j);

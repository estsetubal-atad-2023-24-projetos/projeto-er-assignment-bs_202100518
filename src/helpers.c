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
    printf("0. QUIT - Leaves the program (all data is cleared).\n");
    printf("-------------------------------------------\n\n");

    printf("Input -> ");

    fflush(stdin);
    scanf("%d", &res);

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
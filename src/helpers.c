#include "helpers.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
    if(!readInteger(&res)) return -1;    

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

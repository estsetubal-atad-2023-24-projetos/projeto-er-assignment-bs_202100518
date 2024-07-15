#include "helpers.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>

int startMenu() {
    int res = -1;

    printf("\n---------- Olympics Super Parser ----------\n");
    printf("\n######## Load commands\n");
    printf("1. LOAD_A - Loads all athletes in athletes.csv\n");
    printf("2. LOAD_M - Loads all medals in medals.csv\n");
    printf("3. LOAD_M - Loads all hosts in hosts.csv\n");
    printf("4. CLEAR - Clears all data in memory\n");
    printf("\n######## Other\n");
    printf("0. QUIT - Leaves the program (all data is cleared)\n");
    printf("\n-------------------------------------------\n");

    printf("Input -> ");
    if(!readInteger(&res)) return -1;    

    return res;
}
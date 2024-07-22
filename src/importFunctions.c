#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "importFunctions.h"
#include "helpers.h"
#include "list.h"
#include "map.h"
#include "listMedal.h"
#include "athlete.h"
#include "medal.h"
#include "host.h"
#include "input.h"

#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 100
#define MAX_FIELD_HEADERS 10

PtList importAthletes() {
    PtList athletes = listCreate();

    FILE* fs = fopen("data/athletes.csv", "r");
    
    if(fs == NULL) {
        printf("File not Found\n");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, fs); //skip first line
    int athleteCount = 0;
    while (fgets(line, MAX_LINE_LENGTH, fs))
    {
        char* tempLine = strdup(line);

        // Trim line endings
        //tempLine[strcspn(line, "\n")] = '\0';
        
        char** tokens = splitString(tempLine, 5, ";");

        int year = 0;
        if(tokens[4] != NULL) 
            if(strlen(tokens[4]) > 0)
                year = atoi(tokens[4]);

        Athlete *athlete = createAthlete(tokens[0], tokens[1], atoi(tokens[2]), getNumbersFromString(tokens[3]), year);
            
        // Get index to add to        
        listSize(athletes, &athleteCount);

        // Add to list
        listAdd(athletes, athleteCount, *athlete);
                
        free(tokens);
        free(tempLine);
    }

    return athletes;
}

PtListMedal importMedals(){
    return NULL;
}

PtMap importHosts(){
    return NULL;
}

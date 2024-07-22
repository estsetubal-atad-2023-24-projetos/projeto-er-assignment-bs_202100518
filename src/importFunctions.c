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

#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 100
#define MAX_FIELD_HEADERS 10

PtList importAthletes() {
    PtList athletes = listCreate();

    FILE* fs = fopen("data/athletes.csv", "r");
    
    if(fs == NULL) {
        printf("Error opening athletes.csv\n");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    char *fieldHeaders[MAX_FIELD_HEADERS];
    bool isFirst = true;
    while (fgets(line, MAX_LINE_LENGTH, fs))
    {
        char* tempLine = strdup(line);

        // Trim line endings
        tempLine[strcspn(line, "\n")] = '\0';
        
        Athlete *athlete = createEmptyAthlete();

        int field_count = 0;
        char *token = strtok(tempLine, ";");
        while (token && field_count < MAX_FIELD_HEADERS) {
            if(isFirst) // Map columns to indexes in first line
                fieldHeaders[field_count] = token;
            else { // Map values to object in other lines
                if(strcmp(fieldHeaders[field_count], "athlete_id") == 0) {
                    strcpy(athlete->athleteID, token);
                }
                else if(strcmp(fieldHeaders[field_count], "athlete_full_name") == 0) {
                    strcpy(athlete->athleteName, token);
                }
                else if(strcmp(fieldHeaders[field_count], "games_participations") == 0) {
                    athlete->gamesParticipations = atoi(token);
                }
                else if(strcmp(fieldHeaders[field_count], "first_game") == 0) {
                    athlete->yearFirstParticipation = getNumbersFromString(token);
                }
                else if(strcmp(fieldHeaders[field_count], "athlete_year_birth") == 0) {
                    athlete->athleteBirth = atoi(token);
                }
                else if(strcmp(fieldHeaders[field_count], "") != 0) {
                    printf("Found invalid column in athletes.csv\n");
                    return NULL;
                }
            }            
            
            field_count++;
            token = strtok(NULL, ";"); // Read next token
        }
        
        // Add record to list
        if(!isFirst) {
            // Get index to add to
            int athleteCount = 0;
            listSize(athletes, &athleteCount);

            // Add to list
            listAdd(athletes, athleteCount, *athlete);
        }
        
        isFirst = false;
        
        //free(tempLine);
        free(token);
    }

    return athletes;
}

PtListMedal importMedals(){
    return NULL;
}

PtMap importHosts(){
    return NULL;
}

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
                    if(strlen(token) == 0) athlete->athleteBirth = 0;
                    else athlete->athleteBirth = atoi(token);
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
    PtListMedal medals = listMedalCreate();

    FILE* fs = fopen("data/medals.csv", "r");
    
    if(fs == NULL) {
        printf("Error opening medals.csv\n");
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
        tempLine[strcspn(line, "\r")] = '\0';
        
        Medal *medal = createEmptyMedal();

        int field_count = 0;
        char *token = strtok(tempLine, ";");
        while (token && field_count < MAX_FIELD_HEADERS) {
            if(isFirst) // Map columns to indexes in first line
                fieldHeaders[field_count] = token;
            else { // Map values to object in other lines
                if(strcmp(fieldHeaders[field_count], "discipline_title") == 0) {
                    strcpy(medal->discipline, token);
                }
                else if(strcmp(fieldHeaders[field_count], "slug_game") == 0) {
                    strcpy(medal->game, token);
                }
                else if(strcmp(fieldHeaders[field_count], "event_title") == 0) {
                    strcpy(medal->eventTitle, token);
                }
                else if(strcmp(fieldHeaders[field_count], "event_gender") == 0) {
                    strcpy(medal->gender, token);
                }
                else if(strcmp(fieldHeaders[field_count], "medal_type") == 0) {
                    if(strcmp(token, "GOLD") == 0) medal->medalType = 'G';
                    else if (strcmp(token, "SILVER") == 0) medal->medalType = 'S';
                    else if (strcmp(token, "BRONZE") == 0) medal->medalType = 'B';
                }
                else if(strcmp(fieldHeaders[field_count], "participant_type") == 0) {
                    if(strcmp(token, "Athlete") == 0) medal->participantType = 'A';
                    else if (strcmp(token, "GameTeam") == 0) medal->participantType = 'G';
                }
                else if(strcmp(fieldHeaders[field_count], "participant_title") == 0) {
                    // Do nothing, we dont store this value
                }
                else if(strcmp(fieldHeaders[field_count], "athlete_id") == 0) {
                    strcpy(medal->athleteID, token);
                }
                else if(strcmp(fieldHeaders[field_count], "country_name") == 0) {
                    strcpy(medal->country, token);
                }
                else if(strcmp(fieldHeaders[field_count], "country_3_letter_code") == 0) {
                    // Do nothing, we dont store this value
                }
                else if(strcmp(fieldHeaders[field_count], "") != 0) {
                    printf("Found invalid column in athletes.csv\n");
                    return NULL;
                }
            }

            // Validate athlete_id
            if(medal->participantType == 'A' && strlen(medal->athleteID) == 0)
                strcpy(medal->athleteID, "UNKNOWN");
            
            field_count++;
            token = strtok(NULL, ";"); // Read next token
        }
        
        // Add record to list
        if(!isFirst) {
            // Get index to add to
            int medalCount = 0;
            listSize(medals, &medalCount);

            // Add to list
            listMedalAdd(medals, medalCount, *medal);
        }
        
        isFirst = false;
        
        //free(tempLine);
        free(token);
    }

    return medals;
}

PtMap importHosts(){
    PtMap hosts = mapCreate();

    FILE* fs = fopen("data/hosts.csv", "r");
    
    if(fs == NULL) {
        printf("Error opening hosts.csv\n");
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
        
        Host *host = createEmptyHost();

        int field_count = 0;
        char *token = strtok(tempLine, ";");
        while (token && field_count < MAX_FIELD_HEADERS) {
            if(isFirst) // Map columns to indexes in first line
                fieldHeaders[field_count] = token;
            else { // Map values to object in other lines
                if(strcmp(fieldHeaders[field_count], "game_slug") == 0) {
                    strcpy(host->gameSlug, token);
                }
                else if(strcmp(fieldHeaders[field_count], "game_end_date") == 0) {
                    strcpy(host->endDate, token);
                }
                else if(strcmp(fieldHeaders[field_count], "game_start_date") == 0) {
                    strcpy(host->startDate, token);
                }
                else if(strcmp(fieldHeaders[field_count], "game_location") == 0) {
                    strcpy(host->location, token);
                }
                else if(strcmp(fieldHeaders[field_count], "game_name") == 0) {
                    strcpy(host->gameName, token);
                }
                else if(strcmp(fieldHeaders[field_count], "game_season") == 0) {
                    strcpy(host->season, token);
                }
                else if(strcmp(fieldHeaders[field_count], "game_year") == 0) {
                    host->year = atoi(token);
                }
                else if(strcmp(fieldHeaders[field_count], "") != 0) {
                    printf("Found invalid column in athletes.csv\n");
                    return NULL;
                }
            }            
            
            field_count++;
            token = strtok(NULL, ";"); // Read next token
        }
        
        // Add record to map
        if(!isFirst)
            mapPut(hosts, host->gameSlug, *host);
        
        isFirst = false;
        
        //free(tempLine);
        free(token);
    }

    return hosts;
}

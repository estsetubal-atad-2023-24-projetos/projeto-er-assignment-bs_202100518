#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "helpers.h"
#include "importFunctions.h"
#include "list.h"
#include "appLogic.h"
#include "input.h"
#include "athlete.h"
#include "host.h"
#include "adtSet.h"

bool validateAthletes(PtList a);
bool validateMedals(PtListMedal m);
bool validateHosts(PtMap m);


int main() {
    /* Field Declaration */
    PtList athletes = NULL;
    PtListMedal medals = NULL;
    PtMap hosts = NULL;
    /* ----------------- */


    while(true) { // Start main menu
        switch(startMenu()) {
            case 1: // LOAD_A
                {
                    // Clear current list
                    listClear(athletes);
                    listDestroy(&athletes);

                    athletes = importAthletes();

                    // Means they were not loaded properly
                    if(athletes == NULL) athletes = listCreate();
                    
                    break;
                }
            case 2: // LOAD_M
                {
                    // Clear current list
                    listMedalClear(medals);
                    listMedalDestroy(&medals);

                    medals = importMedals();

                    // Means they were not loaded properly
                    if(medals == NULL) medals = listMedalCreate();
                    
                    break;
                }
            case 3: // LOAD_H
                {
                    // Clear current map
                    mapClear(hosts);
                    mapDestroy(&hosts);

                    hosts = importHosts();

                    // Means they were not loaded properly
                    if(hosts == NULL) hosts = mapCreate();
                    
                    break;
                }
            case 4: // CLEAR
                {
                    int athleteCleanSize, medalCleanSize, hostCleanSize;
                    
                    // Get sizes
                    listSize(athletes, &athleteCleanSize);
                    listMedalSize(medals, &medalCleanSize);
                    mapSize(hosts, &hostCleanSize);
                    
                    // Clear data
                    listClear(athletes);
                    listMedalClear(medals);
                    mapClear(hosts);

                    // Show final message
                    printf("Records deleted from Athletes (%d) | Medals (%d) | Hosts (%d)", athleteCleanSize, medalCleanSize, hostCleanSize);
                }
                break;
            case 5: // SHOW_ALL
                {
                    if(!validateAthletes(athletes)) break;

                    PtList athleteCopy = listAthleteShallowCopy(athletes);
                    orderAthletesAlphabetic(&athleteCopy);
                    if(athleteCopy == NULL) {
                        printf("Could not sort athletes, the resulting list is empty.");
                        free(athleteCopy);
                        return EXIT_FAILURE;
                    }

                    paginate(athleteCopy);

                    free(athleteCopy);
                }
                break;
            case 6: // SHOW_PARTICIPATIONS
                {
                    if(!validateAthletes(athletes)) break;

                    clearScreen();
                    int participations = 0;

                    printf("Insert number of participations -> ");

                    fflush(stdin);
                    scanf("%d", &participations);

                    if(participations < 0) {
                        printf("The number of participations is invalid\n");
                        return EXIT_FAILURE;
                    }

                    // Filter per participation
                    PtList filteredAthletes = filterAthletesPerParticipation(athletes, participations);
                    
                    // Order by name
                    orderAthletesAlphabetic(&filteredAthletes);

                    if(filteredAthletes == NULL) {
                        printf("Could not filter athletes, the resulting list is empty.");
                        free(filteredAthletes);
                        return EXIT_FAILURE;
                    }

                    // Validate size
                    int size = 0;
                    listSize(filteredAthletes, &size);

                    if(size < 1) printf("No athletes found with at least %d participations", participations);
                    else paginate(filteredAthletes);

                    free(filteredAthletes);
                }
                break;
            case 7: // SHOW_FIRST
                {
                    if(!validateAthletes(athletes)) break;
                    
                    clearScreen();
                    int year = 0;

                    printf("Insert year -> ");

                    fflush(stdin);
                    scanf("%d", &year);

                    if(year < 1) {
                        printf("The year is invalid\n");
                        return EXIT_FAILURE;
                    }

                    // Filter per participation
                    PtList filteredAthletes = filterAthletesPerFirstYear(athletes, year);

                    // Order by name
                    orderAthletesAlphabetic(&filteredAthletes);

                    if(filteredAthletes == NULL) {
                        printf("Could not filter athletes, the resulting list is empty.");
                        free(filteredAthletes);
                        return EXIT_FAILURE;
                    }

                    // Validate size
                    int size = 0;
                    listSize(filteredAthletes, &size);

                    if(size < 1) printf("No athletes whose first participation was at %d", year);
                    else paginate(filteredAthletes);

                    free(filteredAthletes);
                }
                break;
            case 8: //SHOW_HOST
                {
                    if(!validateHosts(hosts)) break;

                    char location[MAX_ID_LENGTH];

                    printf("Insert a location -> ");
                    readString(location, MAX_ID_LENGTH);

                    int size = 0;
                    mapSize(hosts, &size);

                    bool found = false;
                    MapValue *values = mapValues(hosts);
                    int i = 0;
                    for(; i < size; i++) {
                        if(strcmp(stringToLower(values[i].location), stringToLower(location)) == 0) {
                            found = true;
                            break;
                        }
                    }

                    if(!found) {
                        printf("Could not find a host with that slug!\n");
                        break;
                    }

                    clearScreen();
                    printHost(values[i]);
                    printf("\nPress any key to continue.");
                    getchar();

                    free(values);
                    break;
                }
            case 9: //DISCIPLINE_STATISTICS
                {
                    if(!validateMedals(medals)) break;
                    
                    char gameSlug[MAX_GAME_LENGTH];

                    printf("Insert a game slug -> ");
                    readString(gameSlug, MAX_ID_LENGTH);

                    // Fetch all disciplines for a gameSlug
                    PtAdtSet disciplines = getGameSlugDisciplines(medals, gameSlug);



                    break;
                }
            case 10: //ATHLETE_INFO
                {
                    if(!validateAthletes(athletes)) break;
                    if(!validateMedals(medals)) break;

                    char *athleteID = malloc(sizeof(char) * MAX_ID_LENGTH);
                    printf("Insert an athlete ID -> ");
                    readString(athleteID, MAX_ID_LENGTH);

                    
                    showAthleteInfo(athletes, medals, athleteID);
                    break;
                }
            case 11: //TOPN
                {
                    if(!validateAthletes(athletes)) break;
                    if(!validateMedals(medals)) break;
                    if(!validateHosts(hosts)) break;

                    int athleteCount = 0;
                    printf("Insert the amount of athlete records to see -> ");
                    readInteger(&athleteCount);

                    int startYear = 0, endYear = 0;
                    printf("Insert the start year -> ");
                    readInteger(&startYear);
                    if(startYear < 0) {
                        printf("Invalid start year\n");
                        break;
                    }

                    printf("Insert the end year -> ");
                    readInteger(&endYear);

                    if(endYear < 0 || endYear < startYear) {
                        printf("Invalid end year\n");
                        break;
                    }
                    
                    int gameTypeChoice = 0;
                    char gameType[7];
                    printf("Choose a game type, Winter (1) or Summer (2) -> ");
                    readInteger(&gameTypeChoice);

                    if(gameTypeChoice == 1) strcpy(gameType, "Winter");
                    else if(gameTypeChoice == 2) strcpy(gameType, "Summer");
                    else {
                        printf("Invalid game type\n");
                        break;
                    }

                    showTopN(athleteCount, startYear, endYear, gameType, athletes, medals, hosts);
                    
                    break;
                }
            case 0: // QUIT
                // Destroy data
                if(athletes != NULL) listDestroy(&athletes);
                if(medals != NULL) listMedalDestroy(&medals);
                if(hosts != NULL) mapDestroy(&hosts);

                return 0;
            default:
                printf("Invalid number, press any key to try again.");
                getchar();
        }
    }

    return EXIT_SUCCESS;
}

bool validateAthletes(PtList a) {
    if(a == NULL) {
        printf("Please import a list of athletes before performing this operation!\n");
        return false;
    }

    return true;
}

bool validateMedals(PtListMedal m) {
    if(m == NULL) {
        printf("Please import a list of medals before performing this operation!\n");
        return false;
    }

    return true;
}

bool validateHosts(PtMap m) {
    if(m == NULL) {
        printf("Please import a list of hosts before performing this operation!\n");
        return false;
    }

    return true;
}
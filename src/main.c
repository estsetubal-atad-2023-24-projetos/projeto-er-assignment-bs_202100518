#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "helpers.h"
#include "importFunctions.h"
#include "list.h"
#include "appLogic.h"

bool validateAthletes(PtList a);
bool validateMedals(PtListMedal m);
bool validateHosts(PtMap m);


int main() {
    /* Field Declaration */
    PtList athletes;
    PtListMedal medals;
    PtMap hosts;
    /* ----------------- */


    while(true) { // Start main menu
        switch(startMenu()) {
            case 1: // LOAD_A
                {
                    // Clear current list
                    listClear(athletes);

                    //athletes = importAthletes();
                    athletes = tempImportAthletes();

                    // Means they were not loaded properly
                    if(athletes == NULL) return EXIT_FAILURE;
                    break;
                }
            case 2: // LOAD_M

                break;
            case 3: // LOAD_H

                break;
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
                    break;
                }
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
                    break;
                }
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

                    // Copy list
                    PtList athleteCopy = listAthleteShallowCopy(athletes);

                    // Filter per participation
                    filterAthletesPerParticipation(&athleteCopy, participations);

                    // Order by name
                    orderAthletesAlphabetic(&athleteCopy);

                    if(athleteCopy == NULL) {
                        printf("Could not filter athletes, the resulting list is empty.");
                        free(athleteCopy);
                        return EXIT_FAILURE;
                    }

                    // Validate size
                    int size = 0;
                    listSize(athleteCopy, &size);

                    if(size < 1) printf("No athletes found with at least %d participations", participations);
                    else paginate(athleteCopy);

                    free(athleteCopy);
                    break;
                }
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

                    // Copy list
                    PtList athleteCopy = listAthleteShallowCopy(athletes);

                    // Filter per participation
                    filterAthletesPerFirstYear(&athleteCopy, year);

                    // Order by name
                    orderAthletesAlphabetic(&athleteCopy);

                    if(athleteCopy == NULL) {
                        printf("Could not filter athletes, the resulting list is empty.");
                        free(athleteCopy);
                        return EXIT_FAILURE;
                    }

                    // Validate size
                    int size = 0;
                    listSize(athleteCopy, &size);

                    if(size < 1) printf("No athletes whose first participation was at %d", year);
                    else paginate(athleteCopy);

                    free(athleteCopy);
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
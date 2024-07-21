#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "helpers.h"
#include "importFunctions.h"
#include "list.h"
#include "appLogic.h"

int main() {
    /* Field Declaration */
    PtList athletes;
    PtListMedal medals;
    PtMap hosts;
    /* ----------------- */


    // Start main menu
    while(true) {
        switch(startMenu()) {
            case 1: // LOAD_A
                athletes = importAthletes();

                if(athletes == NULL) // Means they were not loaded properly
                    return EXIT_FAILURE;
                break;
            case 2: // LOAD_M

                break;
            case 3: // LOAD_H

                break;
            case 4: // CLEAR
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
            case 5: // SHOW_ALL
                PtList sortedAthletes = orderAthletesAlphabetic(athletes);

                paginate(sortedAthletes);

                free(sortedAthletes);
                break;
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
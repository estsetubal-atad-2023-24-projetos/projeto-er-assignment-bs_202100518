#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "appLogic.h"
#include "list.h"
#include "helpers.h"

#define MAX_PAGE_SIZE 20

void paginate(PtList athletes) {
    int athletesCount = 0;
    int currentPage = 1;
        
    listSize(athletes, &athletesCount);
    if(athletesCount == 0) {
        printf("No athletes were found.\n");
        return;
    }
    
    char option = ' ';
    Athlete *ath = NULL;
    while(tolower(option) != 'c') {        
        int endRecord = MAX_PAGE_SIZE * currentPage;
        int startRecord = endRecord - MAX_PAGE_SIZE;

        // This means we have reached the end (aka last page)
        if(endRecord > athletesCount) endRecord = athletesCount;

        clearScreen();
        printf("%d Atheletes were found!\n\n", athletesCount);
        printf("+------------+--------------+----------------------+-----------------------------+---------------+\n");
        printf("| Athlete ID | Athlete Name | Games Participations | Year of First Participation | Athlete Birth |\n");
        printf("+------------+--------------+----------------------+-----------------------------+---------------+\n");

        for(int i = startRecord-1; (i < athletesCount) || (i < endRecord); i++) {            
            listGet(athletes, i, ath);

            printf("| %10s | %12s | %20d | %27d | %13d |\n", 
                ath->athleteID, ath->athleteName, ath->gamesParticipations, ath->yearFirstParticipation, ath->athleteBirth);
            printf("+------------+--------------+----------------------+-----------------------------+---------------+\n");
        }

        printf("\nDisplaying from %d to %d records. Total of %d records.\n", startRecord, endRecord, athletesCount);
        printf("Press 'f' to go to next page, 'p' to go to previous or 'q' to quit.\n");
        printf("Input -> ");

        scanf("%c", &option);

        if(tolower(option) == 'f') {
            if(endRecord < athletesCount) currentPage++;
        }
        else if(tolower(option) == 'p') {
            if(currentPage > 1) currentPage--;
        }        
    }    
}

PtList orderAthletesAlphabetic(PtList athletes) {
    int athCount = 0;

    PtList list = listAthleteShallowCopy(athletes);
    listSize(list, &athCount);

    for(int i = 0; i < athCount; i++) {
        for(int j = 0; j < athCount - i - 1; j++) {
            Athlete currentAth, nextAth;
            listGet(list, j, &currentAth);
            listGet(list, j+1, &nextAth);

            // Current is greater or equal than the next, so we keep the order
            if(strcmp(currentAth.athleteName, nextAth.athleteName) > 0) {
                listSet(list, j, nextAth, NULL);
                listSet(list, j+1, currentAth, NULL);
            }         
        }

    }

    return list;
}

PtList listAthleteShallowCopy(PtList athletes) {
    int athleteCount = 0;
    PtList list = listCreate();

    listSize(athletes, &athleteCount);

    for(int i = 0; i < athleteCount; i++) {
        Athlete ath;
        listGet(athletes, i, &ath);

        listAdd(list, i, ath);
    }

    return list;
}

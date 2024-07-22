#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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
    Athlete ath;
    while(tolower(option) != 'q') {        
        int endRecord = MAX_PAGE_SIZE * currentPage;
        int startRecord = endRecord - MAX_PAGE_SIZE + 1;

        // This means we have reached the end (aka last page)
        if(endRecord > athletesCount) endRecord = athletesCount;

        clearScreen();
        printf("%d Atheletes were found!\n\n", athletesCount);
        printf("+--------------------------------+-------------------------------------+----------------------+-----------------------------+---------------+\n");
        printf("| Athlete ID                     | Athlete Name                        | Games Participations | Year of First Participation | Athlete Birth |\n");
        printf("+--------------------------------+-------------------------------------+----------------------+-----------------------------+---------------+\n");

        for(int i = startRecord-1; (i < athletesCount && athletesCount < endRecord) || (i < endRecord); i++) {            
            if(listGet(athletes, i, &ath) != LIST_OK) {
                printf("An error ocurred fetching records");
                return;
            }

            printf("| %30s | %35s | %20d | %27d | %13d |\n", 
                ath.athleteID, ath.athleteName, ath.gamesParticipations, ath.yearFirstParticipation, ath.athleteBirth);
            printf("+--------------------------------+-------------------------------------+----------------------+-----------------------------+---------------+\n");
        }

        printf("\nDisplaying from %d to %d records. Total of %d records.\n", startRecord, endRecord, athletesCount);
        printf("Press 'f' to go to next page, 'p' to go to previous or 'q' to quit.\n");
        printf("Input -> ");

        fflush(stdin);
        scanf("%c", &option);

        if(tolower(option) == 'f') {
            if(endRecord < athletesCount) currentPage++;
        }
        else if(tolower(option) == 'p') {
            if(currentPage > 1) currentPage--;
        }
        else if(tolower(option) == 'q') break;
    }
}

void orderAthletesAlphabetic(PtList *athletes) {
    if(athletes == NULL) return;
    
    int athCount = 0;
    listSize(*athletes, &athCount);
    quickSort(athletes, 0, athCount-1);
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

PtList filterAthletesPerParticipation(PtList athletes, int participations) {
    if(athletes == NULL) return NULL;

    PtList list = listCreate();

    int athleteSize = 0;
    listSize(athletes, &athleteSize);

    for(int i = 0; i < athleteSize; i++) {
        Athlete currrentAth;
        listGet(athletes, i, &currrentAth);

        if(currrentAth.gamesParticipations >= participations) {
            int size = 0;
            listSize(list, &size);

            listAdd(list, size, currrentAth);
        }
    }

    return list;
}

PtList filterAthletesPerFirstYear(PtList athletes, int year) {
    if(athletes == NULL) return NULL;

    PtList list = listCreate();

    int athleteSize = 0;
    listSize(athletes, &athleteSize);

    for(int i = 0; i < athleteSize; i++) {
        Athlete currrentAth;
        listGet(athletes, i, &currrentAth);

        if(currrentAth.yearFirstParticipation == year){
            int size = 0;
            listSize(list, &size);

            listAdd(list, size, currrentAth);
        }
    }

    return list;
}
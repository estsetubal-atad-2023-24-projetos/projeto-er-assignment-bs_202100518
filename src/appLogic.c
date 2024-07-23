#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "appLogic.h"
#include "list.h"
#include "map.h"
#include "listMedal.h"
#include "helpers.h"
#include "topAthlete.h"

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

void showAthleteInfo(PtList athletes, PtListMedal medals, char *athleteID) {

    // Fetch corresponding athlete
    Athlete filteredAths;
    if(!getAthleteById(athletes, athleteID, &filteredAths)) {
        printf("Could not find an athlete with that ID.\n");
        return;
    }

    // Fetch corresponding medals
    PtListMedal filteredMedals = getMedalsPerAthlete(medals, athleteID);
    if(filteredMedals == NULL) {
        printf("That athlete didn't earn any medals.\n");
        return;
    }

    int medalSize = 0;
    listMedalSize(filteredMedals, &medalSize);

    // Gather info about the contries that the player
    // represented, and slugs that he earned medals
    char* countries = malloc(sizeof(char) * 250);
    char* slugs = malloc(sizeof(char) * 250);    
    for(int i = 0; i < medalSize; i++) {
        Medal current;
        listMedalGet(filteredMedals, i, &current);

        // Countries
        strcat(countries, current.country);
        strcat(countries, ", ");

        // Editions
        strcat(slugs, current.game);
        strcat(slugs, ", ");
    }

    free(countries);
    free(slugs);
    free(filteredMedals);
}

PtListMedal getMedalsPerAthlete(PtListMedal medals, char *athleteID) {
    if(medals == NULL) return NULL;

    PtList list = listMedalCreate();

    int size = 0, subsize = 0;
    listMedalSize(medals, &size);

    for(int i = 0; i < size; i++) {
        Medal medal;
        listMedalGet(medals, i, &medal);

        if(strcmp(medal.athleteID, athleteID) == 0) {
            listMedalSize(medals, &subsize);
            listMedalAdd(medals, subsize, medal);
        }
    }

    if(subsize == 0) return NULL;

    return list;
}

bool getAthleteById(PtList athletes, char *athleteID, Athlete* athlete) {
    int size = 0;
    listSize(athletes, &size);

    for(int i = 0; i < size; i++) {
        listGet(athletes, i, athlete);

        if(strcmp(athlete->athleteID, athleteID) == 0) return true;
    }

    athlete = NULL;
    return false;
}

PtListMedal filterMedalsPerDate(int startYear, int endYear, PtListMedal medals, PtMap hosts) {
    if(medals == NULL) return NULL;

    int size = 0, lstSize = 0;
    listMedalSize(medals, &size);
    
    PtListMedal list = listMedalCreate();
    for(int i = 0; i < size; i++) {
        Medal current;
        listMedalGet(medals, i, &current);

        // Get host
        Host host;
        mapGet(hosts, current.game, &host);

        if(getYearFromDate(host.startDate) >= startYear && getYearFromDate(host.endDate) <= endYear) {
            listMedalSize(list, &lstSize);
            listMedalAdd(list, lstSize, current);
        }        
    }

    return list;
}

PtListMedal filterMedalsPerGameType(char *gameType, PtListMedal medals, PtMap hosts) {
    if(medals == NULL) return NULL;

    int size = 0, lstSize = 0;
    listMedalSize(medals, &size);
    
    PtListMedal list = listMedalCreate();
    for(int i = 0; i < size; i++) {
        Medal current;
        listMedalGet(medals, i, &current);

        // Get host
        Host host;
        mapGet(hosts, current.game, &host);

        if(strcmp(gameType, host.season) == 0) {
            listMedalSize(list, &lstSize);
            listMedalAdd(list, lstSize, current);
        }        
    }

    return list;
}

void showTopN(int n, int startYear, int endYear, char *gameType, PtList athletes, PtListMedal medals, PtMap hosts) {
    if(athletes == NULL || medals == NULL || hosts == NULL) {
        printf("Make sure athletes, medals and hosts have been imported!");
        return;
    }

    PtListMedal filteredMedals = filterMedalsPerDate(startYear, endYear, medals, hosts);
    PtListMedal finalFilteredMedals = filterMedalsPerGameType(gameType, filteredMedals, hosts);
    free(filteredMedals);


    int athSize = 0, medalSize = 0;
    listSize(athletes, &athSize);
    listMedalSize(finalFilteredMedals, &medalSize);

    
    TopAthlete *topAthletes = malloc(sizeof(TopAthlete) * athSize);
    int topAthletesCount = 0;
    for(int i = 0; i < athSize; i++) {
        Athlete currentAthlete;
        listGet(athletes, i, &currentAthlete);
        
        bool found = false; // Use this thing to only create records for athletes with medals
        for(int j = 0; j < medalSize; j++) {
            Medal currentMedal;
            listMedalGet(finalFilteredMedals, j, &currentMedal);

            if(!found) {
                topAthletes[topAthletesCount].totalMedals = 0;
            }

            if(strcmp(currentMedal.athleteID, currentAthlete.athleteID) == 0) {
                found = true; 

                // Add total medals
                topAthletes[topAthletesCount].totalMedals++;

                // Add medals per game
                MedalsPerGame *medalsPerGame = getMedalsPerGame(&topAthletes[topAthletesCount], currentMedal.game);
                if(medalsPerGame == NULL) { // Create new
                    MedalsPerGame *newMedalsPerGame = malloc(sizeof(MedalsPerGame));
                    strcpy(newMedalsPerGame->game, currentMedal.game);
                    newMedalsPerGame->medals = 1;

                    addMedalsPerGame(&topAthletes[topAthletesCount], *newMedalsPerGame);
                }
                else { // Increment existent
                    medalsPerGame->medals++;
                }

                // Sum days played
                Host currentHost;
                mapGet(hosts, currentMedal.game, &currentHost);

                topAthletes[topAthletesCount].daysPlayed = getDateDiffInDays(currentHost.startDate, currentHost.endDate);
            }
        }

        if(found) {
            strcpy(topAthletes[topAthletesCount].athlete, currentAthlete.athleteID);
            topAthletesCount++;
        }
    }

    // Validate empty filtered athletes
    if(topAthletesCount == 0) {
        printf("There aren't any athletes that won any medals.\n");
        return;
    }

    // Display information
    for(int j = 0; (j < topAthletesCount && topAthletesCount < n) || (j < n); j++) {
        printf("\n----------\n");

        printf("Athlete: %s\n", topAthletes[j].athlete);

        printf("Participated Countries: \n");
        for(int k = 0; k < topAthletes[j].medalsPerGameSize; k++) {
            Host currentHost;
            mapGet(hosts, topAthletes[j].medalsPerGame[k].game, &currentHost);

            printf("- %s\n", currentHost.location);
        }
        printf("\n");
        
        printf("Total Medals Earned: %d\n", topAthletes[j].totalMedals);

        if(topAthletes[j].medalsPerGameSize == 0)
            printf("Average Medals per Game: N/A (no medals per game)\n");
        else
            printf("Average Medals per Game: %d\n", topAthletes[j].totalMedals / topAthletes[j].medalsPerGameSize);

        if(topAthletes[j].daysPlayed == 0)
            printf("Average Medals per Day: N/A (No days played)\n");
        else
            printf("Average Medals per Day: %d\n", topAthletes[j].totalMedals / topAthletes[j].daysPlayed);
        
        printf("----------\n");
    }

    free(finalFilteredMedals);
    
    // This thing throws an exception, no idea why
    //free(topAthletes);
}
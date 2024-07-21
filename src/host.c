#include "host.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para criar um novo host
Host* createHost(const char* slug, const char* endDate, const char* startDate, const char* location,
                 const char* gameName, const char* season, int year) {
    Host* newHost = (Host*) malloc(sizeof(Host));
    if (newHost) {
        strncpy(newHost->gameSlug, slug, MAX_ID_LENGTH);
        strncpy(newHost->endDate, endDate, MAX_HOST_NAME_LENGTH);
        strncpy(newHost->startDate, startDate, MAX_HOST_NAME_LENGTH);
        strncpy(newHost->location, location, MAX_LOCATION_LENGTH);
        strncpy(newHost->gameName, gameName, MAX_GAME_NAME_LENGTH);
        strncpy(newHost->season, season, MAX_HOST_NAME_LENGTH);
        newHost->year = year;
    }
    return newHost;
}

// Função para imprimir informações do host
void printHost(Host host) {
    printf("Game Slug: %s\n", host.gameSlug);
    printf("End Date: %s\n", host.endDate);
    printf("Start Date: %s\n", host.startDate);
    printf("Location: %s\n", host.location);
    printf("Game Name: %s\n", host.gameName);
    printf("Season: %s\n", host.season);
    printf("Year: %d\n", host.year);
}
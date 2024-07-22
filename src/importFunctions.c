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

PtList tempImportAthletes() {
    PtList athletes = listCreate();

    int size = 0;

    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("wojciech-knapik", "Wojciech KNAPIK", 2, 2004, 1980));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("gheorghe-langa", "Gheorghe LANGA", 1, 1960, 1930));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("valentin-ivanov-1", "Valentin IVANOV", 1, 1988, 1966));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("andris-sics", "Andris SICS", 5, 2006, 1985));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("bert-romp", "Bert ROMP", 2, 1992, 1958));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("zinaida-belovetskaya", "Zinaida BELOVETSKAYA", 1, 1960, 1939));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("tserenkhand-dorjgotov", "Tserenkhand DORJGOTOV", 2, 2000, 1977));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("olavi-onni-albin-hynninen", "Olavi Onni Albin HYNNINEN", 1, 1948, 1910));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("eva-molnar", "Eva MOLNAR", 1, 1980, 1958));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("hendrik-jan-zwolle", "Hendrik Jan ZWOLLE", 3, 1988, 1964));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("nele-zilinskiene", "Nele ZILINSKIENE", 3, 1992, 1969));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("jake-pates", "Jake PATES", 1, 2018, 1998));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("genevieve-fortin", "Genevieve FORTIN", 1, 0, 1994));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("koul-hwa-kuo", "Koul-Hwa KUO", 1, 1988, 1968));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("tomas-kraus", "Tomas KRAUS", 2, 2010, 1974));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("khassaraporn-suta", "Khassaraporn SUTA", 1, 2000, 1971));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("julian-munoz-aia", "Julian MUNOZ-AIA", 2, 1988, 1946));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("evin-demirhan", "Evin DEMIRHAN", 1, 2020, 1995));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("mihai-cristian-tentea", "Mihai Cristian TENTEA", 2, 2018, 1998));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("yuji-nagai", "Yuji NAGAI", 1, 1992, 1963));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("josh-taylor", "Josh TAYLOR", 1, 2012, 1991));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("klaus-ofner", "Klaus OFNER", 2, 1988, 1968));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("nicklas-holm", "Nicklas HOLM", 1, 2004, 1981));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("custodio-ezequiel", "Custodio EZEQUIEL", 2, 2000, 1962));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("rene-tebbel", "Rene TEBBEL", 1, 2016, 1969));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("gerald-raymond-ouellette", "Gerald Raymond OUELLETTE", 2, 1956, 1934));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("mark-jensen", "Mark JENSEN", 1, 1980, 1946));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("martine-ripsrud", "Martine RIPSRUD", 1, 2022, 1995));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("raymond-neenan", "Raymond NEENAN", 1, 1980, 1952));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("christiane-weber", "Christiane WEBER", 2, 1984, 1962));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("fares-ibrahim-e-h-elbakh", "Fares Ibrahim E. H. ELBAKH", 2, 2016, 1998));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("christopher-hoeger", "Christopher HOEGER", 1, 2002, 1985));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("juan-carlos-vargas-barneond", "Juan Carlos VARGAS BARNEOND", 3, 1984, 1963));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("tibor-maracsko", "Tibor MARACSKO", 2, 1976, 1948));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("toni-kanaet", "Toni KANAET", 1, 2020, 1995));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("yuanguo-zhou", "Yuanguo ZHOU", 2, 2000, 1977));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("steve-ovett", "Steve OVETT", 3, 1976, 1955));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("robin-goad", "Robin GOAD", 1, 2000, 1970));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("evgeni-anikin", "Evgeni ANIKIN", 1, 1980, 1958));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("adrienn-toth", "Adrienn TOTH", 1, 2012, 1990));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("jared-ward", "Jared WARD", 1, 2016, 1988));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("nan-wang-5", "Nan WANG", 3, 2000, 1978));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("niokhor-diongue", "Niokhor DIONGUE", 1, 1980, 1962));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("jose-feans", "Jose FEANS", 1, 1936, 1912));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("jamie-nicholls", "Jamie NICHOLLS", 2, 2014, 1993));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("kharilaos-vasilakos", "Kharilaos VASILAKOS", 2, 1896, 1876));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("kelci-bryant", "Kelci BRYANT", 2, 2008, 1989));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("avaavau-avaavau", "Avaavau AVAAVAU", 1, 1988, 1965));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("maaike-head", "Maaike HEAD", 2, 2012, 1983));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("kebede-sahilu", "Kebede SAHILU", 1, 1980, 1955));
    listSize(athletes, &size);
    listAdd(athletes, size, *createAthlete("felix-sanchez", "Felix SANCHEZ", 4, 2000, 1977));

    return athletes;
}

PtListMedal importMedals(){
    return NULL;
}

PtMap importHosts(){
    return NULL;
}

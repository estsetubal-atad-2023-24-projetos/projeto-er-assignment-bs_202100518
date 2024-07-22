#pragma once

#include "list.h"
#include "listMedal.h"
#include "map.h"

/**
 * @brief Imports athlete data into a map structure
 * 
 * @return PtList 
 */
PtList importAthletes();

PtList tempImportAthletes();

/**
 * @brief Imports Medals data into a list structure
 * 
 * @return PtListMedal 
 */
PtListMedal importMedals();

/**
 * @brief Imports Hosts data into a allocated array of hosts
 * 
 * @return PtMap 
 */
PtMap importHosts();
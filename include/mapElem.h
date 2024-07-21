/**
 * @file mapElem.h
 * @brief Defines the types MapKey and MapValue.
 * 
 * The MapKey is an alias to the type of keys 
 * held by an instance of the ADT Map (PtMap).
 * 
 * The MapValue is an alias to the type of values 
 * held by an instance of the ADT Map (PtMap).
 *  
 * These aliases must be changed according to the use-case.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#pragma once

#include <stdbool.h>
#include "host.h"

/** Key type definition. Change according to the use-case. */
typedef char *MapKey;

/** Value type definition. Change according to the use-case. */
typedef Host MapValue;

bool mapKeyEquals(MapKey key1, MapKey key2);
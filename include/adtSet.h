/**
 * @file adtSet.h
 * @brief Header file for the Set abstract data type set.
 *
 * This file provides the prototypes for various functions to manipulate
 * sets that store elements of type Medal.
 * @author Raul Rohjans
 */
#pragma once

#include <stdbool.h>
#include "medal.h"

struct AdtSetImpl; ///< Forward declaration of the set implementation.

typedef struct AdtSetImpl *PtAdtSet; ///< Pointer to a set implementation.

/**
 * Creates a new set.
 * @return Pointer to the newly created set.
 */
PtAdtSet setCreate();

/**
 * Destroys a set, freeing all associated resources.
 * @param set The set to be destroyed.
 */
void setDestroy(PtAdtSet set);

/**
 * Adds a Medal to the set.
 * @param set The set to which the Medal will be added.
 * @param elem The Medal to add.
 * @return True if the Medal was added successfully, false otherwise.
 */
bool setAdd(PtAdtSet set, Medal elem);

/**
 * Removes a Medal from the set.
 * @param set The set from which the Medal will be removed.
 * @param elem The Medal to remove.
 * @return True if the Medal was removed successfully, false otherwise.
 */
bool setRemove(PtAdtSet set, Medal elem);

/**
 * Checks if a set contains a specific Medal.
 * @param set The set to check.
 * @param elem The Medal to look for.
 * @return True if the set contains the Medal, false otherwise.
 */
bool setContains(PtAdtSet set, Medal elem);

/**
 * Retrieves the size of the set.
 * @param set The set whose size is to be retrieved.
 * @return The number of elements in the set.
 */
int setSize(PtAdtSet set);

/**
 * Checks if one set is a subset of another.
 * @param subset The set to check if it is a subset.
 * @param set The set to check against.
 * @return True if `subset` is a subset of `set`, false otherwise.
 */
bool setSubset(PtAdtSet subset, PtAdtSet set);

/**
 * Checks if the set is empty.
 * @param set The set to check.
 * @return True if the set is empty, false otherwise.
 */
bool setIsEmpty(PtAdtSet set);

/**
 * Clears all elements from the set.
 * @param set The set to clear.
 */
void setClear(PtAdtSet set);

/**
 * Retrieves an array of Medals stored in the set.
 * @param set The set whose elements are to be retrieved.
 * @return Pointer to an array of Medals. NULL if the set is empty.
 */
Medal* setValues(PtAdtSet set);

/**
 * Prints the elements of the set.
 * @param set The set to be printed.
 */
void setPrint(PtAdtSet set);

/**
 * Compares two Medal elements for equality.
 * @param elem1 First Medal element to compare.
 * @param elem2 Second Medal element to compare.
 * @return True if the elements are equal, false otherwise.
 */
bool setElemCompare(Medal elem1, Medal elem2);
/**
 * @file adtSet.c
 * @brief Implementation file for the Set abstract data type.
 *
 * This file includes the implementation of functions to manipulate
 * sets that store elements of type Medal. It includes functions for
 * creating, managing, and manipulating these sets, as well as
 * detailed memory management to ensure efficient handling of set
 * capacities.
 * @author Raul Rohjans
 */
#include <stdio.h>
#include <stdlib.h>
#include "adtSet.h"
#include "medal.h"

/**
 * Represents the implementation of an ADTSet
 */
typedef struct AdtSetImpl {
    Medal *elements;
    int size;
    int capacity;
} AdtSetImpl;

/**
 * @brief Resizes the set to the new capacity.
 * @param set Pointer to the set to be resized.
 * @param newCapacity The new capacity for the set.
 */
static void resizeSet(PtAdtSet set, int newCapacity) {
    AdtSetImpl *setList = (AdtSetImpl *)set;
    Medal *newElements = (Medal*) malloc(newCapacity * sizeof(Medal));

    for (int i = 0; i < setList->size; i++)
        newElements[i] = setList->elements[i];
        
    free(setList->elements);

    setList->elements = newElements;
    setList->capacity = newCapacity;
}

/**
 * @brief Creates a new set.
 * @return Pointer to the newly created set.
 */
PtAdtSet setCreate() {
    AdtSetImpl *set = (AdtSetImpl*) malloc(sizeof(PtAdtSet));

    set->size = 0;
    set->capacity = 10;
    set->elements = (Medal*) malloc(set->capacity * sizeof(Medal));

    return set;
}

/**
 * @brief Destroys a set, freeing all associated resources.
 * @param set The set to be destroyed.
 */
void setDestroy(PtAdtSet set) {
    if (set == NULL) return;

    AdtSetImpl *setList = (AdtSetImpl *)set;

    free(setList->elements);
    free(setList);
}

/**
 * @brief Adds a Medal to the set.
 * @param set The set to which the Medal will be added.
 * @param elem The Medal to add.
 * @return True if the Medal was added successfully, false otherwise.
 */
bool setAdd(PtAdtSet set, Medal elem) {
    if(set == NULL) return false;

    if (setContains(set, elem))
        return false;

    AdtSetImpl *setList = (AdtSetImpl *)set;
    if (setList->size == setList->capacity)
        resizeSet(set, 2 * setList->capacity);
    
    setList->elements[setList->size++] = elem;
    return true;
}

/**
 * @brief Removes a Medal from the set.
 * @param set The set from which the Medal will be removed.
 * @param elem The Medal to remove.
 * @return True if the Medal was removed successfully, false otherwise.
 */
bool setRemove(PtAdtSet set, Medal elem) {
    if(set == NULL) return false;

    AdtSetImpl *setList = (AdtSetImpl *)set;

    for (int i = 0; i < setList->size; i++) {
        if (setElemCompare(setList->elements[i], elem)) {
            setList->elements[i] = setList->elements[--setList->size];

            if (setList->size > 0 && setList->size == setList->capacity / 4)
                resizeSet(set, setList->capacity / 2);
            
            return true;
        }
    }
    return false;
}

/**
 * @brief Compares two medals to see if they are the same.
 * @param elem1 First medal to compare.
 * @param elem2 Second medal to compare.
 * @return True if the medals are the same, false otherwise.
 */
bool setElemCompare(Medal elem1, Medal elem2) {
    if(elem1.discipline == elem2.discipline &&
        elem1.game == elem2.game &&
        elem1.athleteID == elem2.athleteID) return true;
    else return false;
}

/**
 * @brief Checks if the set contains a specific Medal.
 * @param set The set to check.
 * @param elem The Medal to look for.
 * @return True if the set contains the Medal, false otherwise.
 */
bool setContains(PtAdtSet set, Medal elem) {
    if(set == NULL) return false;

    AdtSetImpl *setList = (AdtSetImpl *)set;
    for (int i = 0; i < setList->size; i++)
        if (setElemCompare(setList->elements[i], elem)) return true;        

    return false;
}

/**
 * @brief Retrieves the size of the set.
 * @param set The set whose size is to be retrieved.
 * @return The number of elements in the set.
 */
int setSize(PtAdtSet set) {
    if(set == NULL) return 0;

    AdtSetImpl *setList = (AdtSetImpl *)set;    
    return setList->size;
}

/**
 * @brief Checks if one set is a subset of another.
 * @param subset The set to check if it is a subset.
 * @param set The set to check against.
 * @return True if `subset` is a subset of `set`, false otherwise.
 */
bool setSubset(PtAdtSet subset, PtAdtSet set) {
    if(subset == NULL || set == NULL) return false;

    AdtSetImpl *subsetList = (AdtSetImpl *)subset;
    for (int i = 0; i < subsetList->size; i++)
        if (!setContains(set, subsetList->elements[i])) return false;

    return true;
}

/**
 * @brief Checks if the set is empty.
 * @param set The set to check.
 * @return True if the set is empty, false otherwise.
 */
bool setIsEmpty(PtAdtSet set) {
    if(set == NULL) return true;

    AdtSetImpl *setList = (AdtSetImpl *)set;

    return setList->size == 0;
}

/**
 * @brief Clears all elements from the set.
 * @param set The set to clear.
 */
void setClear(PtAdtSet set) {
    if(set == NULL) return;

    AdtSetImpl *setList = (AdtSetImpl *)set;

    free(setList->elements);

    setList->size = 0;
    resizeSet(set, 10);
}

/**
 * @brief Retrieves an array of Medals stored in the set.
 * @param set The set whose elements are to be retrieved.
 * @return Pointer to an array of Medals. NULL if the set is empty.
 */
Medal* setValues(PtAdtSet set) {
    if(set == NULL) return NULL;

    AdtSetImpl *setList = (AdtSetImpl *)set;
    Medal *values = (Medal*) malloc(setList->size * sizeof(Medal));

    for (int i = 0; i < setList->size; i++)
        values[i] = setList->elements[i];
    
    return values;
}

/**
 * @brief Prints the elements of the set.
 * @param set The set to be printed.
 */
void setPrint(PtAdtSet set) {
    if(set == NULL) {
        printf("No data to display, set is null.\n");
        return;
    }

    AdtSetImpl *setList = (AdtSetImpl *)set;

    printf("----------------\n");

    for (int i = 0; i < setList->size; i++)
        printMedal(setList->elements[i]);
    
    printf("----------------\n\n");
}

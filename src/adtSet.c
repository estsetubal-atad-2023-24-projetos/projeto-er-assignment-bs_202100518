#include <stdio.h>
#include <stdlib.h>
#include "adtSet.h"
#include "medal.h"

static void resizeSet(Set *set, int newCapacity) {
    Medal *newElements = (Medal*) malloc(newCapacity * sizeof(Medal));

    for (int i = 0; i < set->size; i++)
        newElements[i] = set->elements[i];
        
    free(set->elements);

    set->elements = newElements;
    set->capacity = newCapacity;
}

Set* setCreate() {
    Set *set = (Set*) malloc(sizeof(Set));

    set->size = 0;
    set->capacity = 10;
    set->elements = (Medal*) malloc(set->capacity * sizeof(Medal));

    return set;
}

void setDestroy(Set *set) {
    if (set == NULL) return NULL;

    free(set->elements);
    free(set);
}

bool setAdd(Set *set, Medal elem) {
    if (setContains(set, elem))
        return false;
    
    if (set->size == set->capacity)
        resizeSet(set, 2 * set->capacity);
    
    set->elements[set->size++] = elem;
    return true;
}

bool setRemove(Set *set, Medal elem) {
    for (int i = 0; i < set->size; i++) {
        if (setElemCompare(set->elements[i], elem)) {
            set->elements[i] = set->elements[--set->size];

            if (set->size > 0 && set->size == set->capacity / 4)
                resizeSet(set, set->capacity / 2);
            
            return true;
        }
    }
    return false;
}

bool setElemCompare(Medal elem1, Medal elem2) {
    if(elem1.discipline == elem2.discipline &&
        elem1.game == elem2.game &&
        elem1.athleteID == elem2.athleteID) return true;
    else return false;
}

bool setContains(Set *set, Medal elem) {
    for (int i = 0; i < set->size; i++)
        if (setElemCompare(set->elements[i], elem)) return true;        

    return false;
}

int setSize(Set *set) {
    return set->size;
}

bool setSubset(Set *subset, Set *set) {
    for (int i = 0; i < subset->size; i++)
        if (!setContains(set, subset->elements[i])) return false;

    return true;
}

bool setIsEmpty(Set *set) {
    return set->size == 0;
}

void setClear(Set *set) {
    set->size = 0;
    resizeSet(set, 10);
}

Medal* setValues(Set *set) {
    Medal *values = (Medal*) malloc(set->size * sizeof(Medal));

    for (int i = 0; i < set->size; i++)
        values[i] = set->elements[i];
    
    return values;
}

void setPrint(Set *set) {
    printf("{ ");
    
    for (int i = 0; i < set->size; i++) 
        printf("%d ", set->elements[i]);
    
    printf("}\n");
}

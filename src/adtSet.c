#include <stdio.h>
#include <stdlib.h>
#include "adtSet.h"
#include "medal.h"

typedef struct AdtSetImpl {
    Medal *elements;
    int size;
    int capacity;
} AdtSetImpl;

static void resizeSet(PtAdtSet *set, int newCapacity) {
    AdtSetImpl *setList = (AdtSetImpl *)set;
    Medal *newElements = (Medal*) malloc(newCapacity * sizeof(Medal));

    for (int i = 0; i < setList->size; i++)
        newElements[i] = setList->elements[i];
        
    free(setList->elements);

    setList->elements = newElements;
    setList->capacity = newCapacity;
}

PtAdtSet* setCreate() {
    AdtSetImpl *set = (AdtSetImpl*) malloc(sizeof(AdtSetImpl));

    set->size = 0;
    set->capacity = 10;
    set->elements = (Medal*) malloc(set->capacity * sizeof(Medal));

    return set;
}

void setDestroy(PtAdtSet *set) {
    if (set == NULL) return NULL;

    AdtSetImpl *setList = (AdtSetImpl *)set;

    free(setList->elements);
    free(setList);
}

bool setAdd(PtAdtSet *set, Medal elem) {
    if(set == NULL) return false;

    if (setContains(set, elem))
        return false;

    AdtSetImpl *setList = (AdtSetImpl *)set;
    if (setList->size == setList->capacity)
        resizeSet(set, 2 * setList->capacity);
    
    setList->elements[setList->size++] = elem;
    return true;
}

bool setRemove(PtAdtSet *set, Medal elem) {
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

bool setElemCompare(Medal elem1, Medal elem2) {
    if(elem1.discipline == elem2.discipline &&
        elem1.game == elem2.game &&
        elem1.athleteID == elem2.athleteID) return true;
    else return false;
}

bool setContains(PtAdtSet *set, Medal elem) {
    if(set == NULL) return false;

    AdtSetImpl *setList = (AdtSetImpl *)set;
    for (int i = 0; i < setList->size; i++)
        if (setElemCompare(setList->elements[i], elem)) return true;        

    return false;
}

int setSize(PtAdtSet *set) {
    if(set == NULL) return 0;

    AdtSetImpl *setList = (AdtSetImpl *)set;    
    return setList->size;
}

bool setSubset(PtAdtSet *subset, PtAdtSet *set) {
    if(subset == NULL || set == NULL) return false;

    AdtSetImpl *subsetList = (AdtSetImpl *)subset;
    for (int i = 0; i < subsetList->size; i++)
        if (!setContains(set, subsetList->elements[i])) return false;

    return true;
}

bool setIsEmpty(PtAdtSet *set) {
    if(set == NULL) return true;

    AdtSetImpl *setList = (AdtSetImpl *)set;

    return setList->size == 0;
}

void setClear(PtAdtSet *set) {
    if(set == NULL) return;

    AdtSetImpl *setList = (AdtSetImpl *)set;

    setList->size = 0;
    resizeSet(set, 10);
}

Medal* setValues(PtAdtSet *set) {
    if(set == NULL) return NULL;

    AdtSetImpl *setList = (AdtSetImpl *)set;
    Medal *values = (Medal*) malloc(setList->size * sizeof(Medal));

    for (int i = 0; i < setList->size; i++)
        values[i] = setList->elements[i];
    
    return values;
}

void setPrint(PtAdtSet *set) {
    if(set == NULL) {
        printf("No data to display, set is null.\n");
        return;
    }

    AdtSetImpl *setList = (AdtSetImpl *)set;

    printf("{ ");
    
    for (int i = 0; i < setList->size; i++) 
        printf("%d ", setList->elements[i]);
    
    printf("}\n");
}

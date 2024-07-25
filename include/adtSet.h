#pragma once

#include <stdbool.h>
#include "medal.h"

// Estrutura do Set
typedef struct {
    Medal *elements;
    int size;
    int capacity;
} Set;

Set* setCreate();

void setDestroy(Set *set);

bool setAdd(Set *set, Medal elem);

bool setRemove(Set *set, Medal elem);

bool setContains(Set *set, Medal elem);

int setSize(Set *set);

bool setSubset(Set *subset, Set *set);

bool setIsEmpty(Set *set);

void setClear(Set *set);

Medal* setValues(Set *set);

void setPrint(Set *set);

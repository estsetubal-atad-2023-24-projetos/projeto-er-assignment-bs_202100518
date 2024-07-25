#pragma once

#include <stdbool.h>
#include "medal.h"

struct AdtSetImpl;

/** Definition of pointer to the  data stucture. */
typedef struct AdtSetImpl *PtAdtSet;

PtAdtSet* setCreate();

void setDestroy(PtAdtSet *set);

bool setAdd(PtAdtSet *set, Medal elem);

bool setRemove(PtAdtSet *set, Medal elem);

bool setContains(PtAdtSet *set, Medal elem);

int setSize(PtAdtSet *set);

bool setSubset(PtAdtSet *subset, PtAdtSet *set);

bool setIsEmpty(PtAdtSet *set);

void setClear(PtAdtSet *set);

Medal* setValues(PtAdtSet *set);

void setPrint(PtAdtSet *set);

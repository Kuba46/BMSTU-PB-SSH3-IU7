#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "logic.h"

struct AppParams
{
    const char* filename;
    const char* region;
    int column;
    List* calculateOutputList;
};

enum Operation {
    Init,
    SetFilename,
    LoadData,
    ClearRecords,
    Calculate,
    SetCalculationRegion,
    SetCalculationColumn,
};

Error doOperation(Operation operation, AppContext* context, AppParams* params);

#endif // ENTRYPOINT_H

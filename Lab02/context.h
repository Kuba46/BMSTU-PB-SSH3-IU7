#ifndef CONTEXT_H
#define CONTEXT_H

#define MAX_FILENAME 200
#include <stddef.h>
#include "list.h"

struct AppContext
{
    List records;
    size_t countCorruptedRecords;
    char filename[MAX_FILENAME];
    char region[MAX_REGION_LEN];
    int column;
    struct
    {
        double minimum;
        double maximum;
        double median;
    } metrics;
};

#endif // CONTEXT_H

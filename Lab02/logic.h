#ifndef LOGIC_H
#define LOGIC_H

#include "context.h"
#include "errors.h"

#define MAX_LINE 200
#define LAST_FIELD 7
#define FIRST_FIELD 3

void initialize(AppContext* context);
void setFilename(AppContext* context, const char* filename);
Error loadData(AppContext* context);
void clearRecords(AppContext* context);
Error calculate(AppContext* context, List* output);
void setCalculationRegion(AppContext* context, const char* region);
void setCalculationColumn(AppContext* context, int column);

#endif // LOGIC_H

#include "logic.h"
#include "string.h"
#include <stdio.h>

void initialize(AppContext* context) {
    context->filename[0] = 0;
    context->region[0] = 0;
    context->column = 3;
    context->records = listNew();
    context->metrics = {.minimum = 0, .maximum = 0, .median = 0};
    clearRecords(context);
}

void setFilename(AppContext* context, const char* filename) {
    strcpy_s(context->filename, MAX_FILENAME, filename);
}

void skipLine(FILE* file) {
    char line[MAX_LINE];
    fgets(line, MAX_LINE, file);
}

int readRecord(FILE* file, Record* record) {
    char line[MAX_LINE];
    fgets(line, MAX_LINE, file);
    int count = -1;
    if (strlen(line) > strlen("\r\n")) {
        count = sscanf(line, "%d,%[^,],%lf,%lf,%lf,%lf,%lf", &record->year, &record->region, &record->npg, &record->birth_rate, &record->death_rate, &record->gdw, &record->urbanization);
    }
    return count;
}


Error readAllRecords(AppContext* context, FILE* file) {
    Error error = Error::NO_ERRORS;
    skipLine(file);
    Record record;
    while (!feof(file)) {
        int count = readRecord(file, &record);
        if (count >= 0 && count != LAST_FIELD) {
            context->countCorruptedRecords++;
            continue;
        } else if (count < 0) {
            continue;
        }
        listPush(&context->records, &record);
    }
    return error;
}

Error loadData(AppContext* context) {
    Error error = Error::NO_ERRORS;
    clearRecords(context);
    FILE* file = fopen(context->filename, "r");
    if (file == 0) {
        error = Error::FILE_IS_NOT_OPENED;
    } else {
        error = readAllRecords(context, file);
        fclose(file);
    }
    return error;
}

void clearRecords(AppContext* context) {
    listClear(&context->records);
    context->countCorruptedRecords = 0;
}

double getColumnByIndex(Record* record, int index) {
    double value = 0;
    switch (index) {
    case 3:
        value = record->npg;
        break;
    case 4:
        value = record->birth_rate;
        break;
    case 5:
        value = record->death_rate;
        break;
    case 6:
        value = record->gdw;
        break;
    case 7:
        value = record->urbanization;
        break;
    default:
        break;
    }
    return value;
}

void calculateMetrics(AppContext* context, List* list)
{
    Node* node = list->first;
    if (node) {
        context->metrics.maximum = getColumnByIndex(&node->record, context->column);
        context->metrics.minimum = getColumnByIndex(&node->record, context->column);
    }  else {
        context->metrics.maximum = 0;
        context->metrics.minimum = 0;
        context->metrics.median = 0;
    }
    int i = 0;
    while (node) {
        context->metrics.maximum = getColumnByIndex(&node->record, context->column) > context->metrics.maximum ? getColumnByIndex(&node->record, context->column) : context->metrics.maximum;
        context->metrics.minimum = getColumnByIndex(&node->record, context->column) < context->metrics.minimum ? getColumnByIndex(&node->record, context->column) : context->metrics.minimum;
        if (list->count % 2 && i == list->count / 2) {
            context->metrics.median = getColumnByIndex(&node->record, context->column);
        } else if (!(list->count % 2) && i + 1 == list->count / 2) {
            context->metrics.median = (getColumnByIndex(&node->record, context->column) + getColumnByIndex(&node->next->record, context->column)) / 2;
        }
        node = node->next;
        i++;
    }
}

Error calculate(AppContext* context, List* output)
{
    Error error = Error::NO_ERRORS;
    if (context->column >= FIRST_FIELD && context->column <= LAST_FIELD)
    {
        Node* node = context->records.first;
        while (node)
        {
            if (strlen(context->region) == 0 || (!strcmp(context->region, node->record.region)))
            {
                listPush(output, &node->record);
            }
            node = node->next;
        }
        calculateMetrics(context, output);
    } else {
        error = Error::INCORRECT_COLUMN;
    }
    return error;
}

void setCalculationRegion(AppContext* context, const char* region)
{
    strcpy_s(context->region, MAX_REGION_LEN, region);
}

void setCalculationColumn(AppContext* context, int column)
{
    context->column = column;
}

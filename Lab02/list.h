#ifndef LIST_H
#define LIST_H
#define MAX_REGION_LEN 60

#include <stddef.h>

struct Record
{
    int year;
    char region[MAX_REGION_LEN];
    double npg;
    double birth_rate;
    double death_rate;
    double gdw;
    double urbanization;
};

struct Node
{
    Node* next;
    Record record;
};

struct List
{
    struct Node* first;
    struct Node* end;
    size_t count;
};

List listNew();
void listPush(List* list, Record* record);
void listClear(List* list);

#endif // LIST_H

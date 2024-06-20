#include "list.h"
#include <stdlib.h>
#include <string.h>

List listNew()
{
    return List
        {
        .first = 0,
        .end = 0,
        .count = 0,
    };
}

void listPush(List* list, Record* record)
{
    Node* node = (Node*) malloc(sizeof(Node));
    node->next = 0;
    memcpy_s(&node->record, sizeof(Record), record, sizeof(Record));
    if (!list->first) {
        list->first = node;
        list->end = node;
    } else {
        list->end->next = node;
        list->end = node;
    }
    list->count++;
}

void listClear(List* list)
{
    Node* node = list->first;
    while (node) {
        Node* previous = node;
        node = node->next;
        free(previous);
    }
    list->first = 0;
    list->end = 0;
    list->count = 0;
}

#ifndef USER_ENTRY_H
#define USER_ENTRY_H

#include "logic.h"

enum Operation
{
    INITIALIZE,
    SET_INPUT_SYSTEM,
    SET_OUTPUT_SYSTEM,
    SET_INPUT_NUMBER,
    CONVERT,
    SWAP
};

struct AppParameters
{
    const char* number;
    unsigned numberSystem;
};

Error doOperation(Operation operation, AppContext* context, AppParameters* params);

#endif // USER_ENTRY_H

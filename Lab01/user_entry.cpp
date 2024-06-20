#include "user_entry.h"

Error doOperation(Operation operation, AppContext* context, AppParameters* params)
{
    Error error = Error::NO_ERROR;
    switch (operation)
    {
    case Operation::INITIALIZE:
        init(context);
        break;
    case Operation::SET_INPUT_SYSTEM:
        setInputNumberSystem(context, params->numberSystem);
        break;
    case Operation::SET_OUTPUT_SYSTEM:
        setOutputNumberSystem(context, params->numberSystem);
        break;
    case Operation::SET_INPUT_NUMBER:
        setInputNumber(context, params->number);
        break;
    case Operation::CONVERT:
        error = convert(context);
        break;
    case Operation::SWAP:
        error = swap(context);
        break;
    }
}

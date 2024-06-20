#ifndef ERRORS_H
#define ERRORS_H

enum Error
{
    NO_ERROR,
    MEMORY_OVERFLOW,
    INCORRECT_DIGIT,
    INCORRECT_DIGITS,
    INCORRECT_NUMBER_SYSTEM
};

void handleError(const Error &error);

#endif // ERRORS_H

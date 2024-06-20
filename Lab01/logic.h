#ifndef LOGIC_H
#define LOGIC_H

#include <ctype.h>
#include <string.h>
#include <limits.h>

#include "appcontext.h"
#include "errors.h"

#define BINARY 2
#define DECIMAL 10
#define MAXIMAL_NUMBER_SYSTEM 16
#define MINIMAL_NUMBER_SYSTEM 2
#define SIGN_BIT ~(UINT_MAX >> 1)
#define IS_NOT_NEGATIVE 0
#define IS_NEGATIVE 1
#define MINUS '-'
#define DIGITS "0123456789ABCDEF"

void init(AppContext* context);
void setInputNumber(AppContext* context, const char* number);
void setInputNumberSystem(AppContext* context, unsigned numberSystem);
void setOutputNumberSystem(AppContext* context, unsigned numberSystem);

Error toUnsigned(const char* input, unsigned inputNumberSystem, unsigned* output);
void fromUnsigned(unsigned value, char* output, unsigned outputNumberSystem);
unsigned getValueByDigit(char digit);
unsigned getDigitByValue(unsigned value);
Error isAllowDigit(char digit, unsigned inputNumberSystem);
int countIncorrectCharacters(const char* str, unsigned numberSystem);

Error convert(AppContext* context);
Error swap(AppContext* context);
void swapUnsigned(unsigned* a, unsigned* b);
void Swap(char* a, char* b);
void classicSwap(char* a, char* b);
void reverseString(char* str);

#endif // LOGIC_H

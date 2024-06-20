#include "logic.h"

Error convert(AppContext* context)
{
    unsigned value;
    Error error = Error::NO_ERROR;
    if (strlen(context->inputNumber) == 0 || countIncorrectCharacters(context->inputNumber, context->inputNumberSystem))
    {
        error = Error::INCORRECT_DIGITS;
    }
    if (error == Error::NO_ERROR && (error = toUnsigned(context->inputNumber, context->inputNumberSystem, &value)) == Error::NO_ERROR)
    {
        fromUnsigned(value, context->outputNumber, context->outputNumberSystem);
    }
    return error;
}

Error toUnsigned(const char* input, unsigned inputNumberSystem, unsigned* output)
{
    Error error = Error::NO_ERROR;
    int numberType = input[0] == MINUS && inputNumberSystem == DECIMAL ? IS_NEGATIVE : IS_NOT_NEGATIVE;
    unsigned result = 0;
    for (size_t i = numberType == IS_NEGATIVE ? 1 : 0; i < strlen(input); i++)
    {
        if (result > (UINT_MAX - getValueByDigit(input[i])) / inputNumberSystem)
        {
            error = Error::INCORRECT_DIGITS;
            break;
        }
        else if (inputNumberSystem == DECIMAL && result > ((numberType == IS_NOT_NEGATIVE ? INT_MAX : INT_MIN) - getValueByDigit(input[i])) / inputNumberSystem)
        {
            error = Error::INCORRECT_DIGITS;
            break;
        }
        result = result * inputNumberSystem + getValueByDigit(input[i]);
    }
    if (numberType == IS_NEGATIVE)
    {
        result = ~result + 1;
    }
    if (output)
    {
        *output = result;
    }
    return error;
}

void fromUnsigned(unsigned value, char* output, unsigned outputNumberSystem)
{
    unsigned discharge = 0;
    int numberType = value & SIGN_BIT ? IS_NEGATIVE : IS_NOT_NEGATIVE;
    if (outputNumberSystem == DECIMAL && numberType == IS_NEGATIVE)
    {
        value = ~(value - 1);
    }
    while (value)
    {
        output[discharge] = getDigitByValue(value % outputNumberSystem);
        value /= outputNumberSystem;
        discharge++;
    }
    if (outputNumberSystem == DECIMAL && numberType == IS_NEGATIVE)
    {
        output[discharge] = MINUS;
        discharge++;
    }
    output[discharge] = 0;
    reverseString(output);
}

unsigned getValueByDigit(char digit)
{
    unsigned index = strlen(DIGITS);
    for (size_t i = 0; i < strlen(DIGITS); i++)
    {
        if (DIGITS[i] == digit)
        {
            index = i;
            break;
        }
    }
    return index;
}

unsigned getDigitByValue(unsigned value)
{
    return DIGITS[value];
}

void reverseString(char* str)
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++)
    {
        classicSwap(str + i, str + len - i - 1);
    }
}

void classicSwap(char* a, char* b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

Error isAllowDigit(char digit, unsigned inputNumberSystem)
{
    return getValueByDigit(digit) < inputNumberSystem ? Error::NO_ERROR : Error::INCORRECT_DIGITS;
}

int countIncorrectCharacters(const char* str, unsigned numberSystem)
{
    int amount = 0;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (i == 0 && numberSystem == DECIMAL && str[i] == MINUS)
        {
            continue;
        }
        if (isAllowDigit(str[i], numberSystem) == Error::INCORRECT_DIGITS)
        {
            amount++;
        }
    }
    return amount;
}

Error swap(AppContext* context)
{
    Error error = Error::NO_ERROR;
    if (strlen(context->inputNumber) == 0 || countIncorrectCharacters(context->inputNumber, context->inputNumberSystem) != 0)
    {
        error = Error::INCORRECT_DIGITS;
    }
    else
    {
        swapUnsigned(&context->inputNumberSystem, &context->outputNumberSystem);
        Swap(context->inputNumber, context->outputNumber);
    }
    return error;
}

void setInputNumberSystem(AppContext* context, unsigned numberSystem)
{
    context->inputNumberSystem = numberSystem;
}

void setOutputNumberSystem(AppContext* context, unsigned numberSystem)
{
    context->outputNumberSystem = numberSystem;
}

void setInputNumber(AppContext* context, const char* number)
{
    strcpy_s(context->inputNumber, MAX_BUF_SIZE, number);
    for (size_t i = 0; i < strlen(context->inputNumber); i++)
    {
        context->inputNumber[i] = toupper(context->inputNumber[i]);
    }
}

void swapUnsigned(unsigned* a, unsigned* b)
{
    unsigned temp = *a;
    *a = *b;
    *b = temp;
}

void Swap(char* a, char* b)
{
    char temp[MAX_BUF_SIZE];
    strcpy_s(temp, MAX_BUF_SIZE, a);
    strcpy_s(a, MAX_BUF_SIZE, b);
    strcpy_s(b, MAX_BUF_SIZE, temp);
}

void init(AppContext* context)
{
    context->inputNumber[0] = 0;
    context->outputNumber[0] = 0;
    context->inputNumberSystem = DECIMAL;
    context->outputNumberSystem = BINARY;
}

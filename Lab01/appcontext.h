#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#define MAX_BUF_SIZE 33

struct AppContext
{
    unsigned inputNumberSystem;
    unsigned outputNumberSystem;
    char inputNumber[MAX_BUF_SIZE];
    char outputNumber[MAX_BUF_SIZE];
};

#endif // APPCONTEXT_H

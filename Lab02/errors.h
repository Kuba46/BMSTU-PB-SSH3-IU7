#ifndef ERRORS_H
#define ERRORS_H

#include <QMessageBox>

#define WINDOW_SIZE_X 550
#define WINDOW_SIZE_Y 200

enum Error
{
    NO_ERRORS,
    FILE_IS_NOT_OPENED,
    INCORRECT_COLUMN,
};

void handleError(const Error& error);

#endif // ERRORS_H

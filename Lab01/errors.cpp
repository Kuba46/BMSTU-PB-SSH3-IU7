#include "errors.h"

#include <QMessageBox>

#define MESSAGE_X_SIZE 500
#define MESSAGE_Y_SIZE 200

void handleError(const Error &error)
{
    QMessageBox message;
    switch(error)
    {
    case MEMORY_OVERFLOW:
        message.critical(0, "Error", "Overflow! Your number is too long");
        message.setFixedSize(MESSAGE_X_SIZE, MESSAGE_Y_SIZE);
        break;
    case INCORRECT_DIGIT:
        message.critical(0, "Error", "You've put an incorrect digit");
        message.setFixedSize(MESSAGE_X_SIZE, MESSAGE_Y_SIZE);
        break;
    case INCORRECT_DIGITS:
        message.critical(0, "Error", "The number you've entered containing incorrect digits");
        message.setFixedSize(MESSAGE_X_SIZE, MESSAGE_Y_SIZE);
        break;
    case INCORRECT_NUMBER_SYSTEM:
        message.critical(0, "Error", "The number does not match selected number system");
        message.setFixedSize(MESSAGE_X_SIZE, MESSAGE_Y_SIZE);
        break;
    default:
        message.critical(0, "Error", "An unholded error occupied");
        message.setFixedSize(MESSAGE_X_SIZE, MESSAGE_Y_SIZE);
        break;
    }
}

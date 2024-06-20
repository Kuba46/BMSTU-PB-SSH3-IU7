#include "errors.h"

void handleError(const Error& error)
{
    QMessageBox message;
    switch(error)
    {
    case FILE_IS_NOT_OPENED:
        message.critical(0, "Error!", "File is not opened!");
        message.setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
        break;
    case INCORRECT_COLUMN:
        message.critical(0, "Error!", "You have selected an incorrect column!");
        message.setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
        break;
    default:
        message.critical(0, "Error", "An unholded error occupied");
        message.setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
        break;
    }
}

#include <QMessageBox>

#include "errors.h"

#define TITLE "Ошибка"

#define ERR_MSG_READ_DATA "Коэффиценты трансформации должны быть вещественными!"
#define ERR_MSG_UNKNOWN "Неизвестная ошибка!"


void handle_error(const err_t rc)
{
    switch (rc)
    {
    case (ERR_TRANSFORM_READ):
        QMessageBox::critical(NULL, TITLE, ERR_MSG_READ_DATA);
        break;
    default:
        QMessageBox::critical(NULL, TITLE, ERR_MSG_UNKNOWN);
        break;
    }
}

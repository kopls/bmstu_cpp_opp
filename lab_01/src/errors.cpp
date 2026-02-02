#include <QMessageBox>

#include "errors.h"

#define TITLE "Ошибка"

#define ERR_MSG_READ_DATA "Коэффиценты трансформации должны быть вещественными!"
#define ERR_MSG_UNKNOWN "Неизвестная ошибка!"
#define ERR_MSG_READ_VERTEX "В файле некорректные данные (точки)"
#define ERR_MSG_MEMORY_VERTEXES_ARR "В файле некорректные данные"
#define ERR_MSG_READ_VERTEXES_LEN "В файле некорректные данные (точки)"
#define ERR_MSG_VALUE_VERTEXES_LEN "В файле некорректные данные (точки)"
#define ERR_MSG_READ_LINKS_LEN "В файле некорректные данные (связи)"
#define ERR_MSG_VALUE_LINKS_LEN "В файле некорректные данные (связи)"
#define ERR_MSG_MEMORY_LINKS_ARR "В файле некорректные данные"
#define ERR_MSG_BAD_LINK "В файле некорректные данные (связи)"
#define ERR_MSG_READ_LINK "В файле некорректные данные (связи)"
#define ERR_MSG_OPEN_FILE "Ошибка открытия файла"
#define ERR_MSG_NO_DATA "Ошибка, данные не загружены"


void handle_error(const err_t rc)
{
    switch (rc)
    {
    case (ERR_TRANSFORM_READ):
        QMessageBox::critical(NULL, TITLE, ERR_MSG_READ_DATA);
        break;
    case (ERR_READ_VERTEX):
        QMessageBox::critical(NULL, TITLE, ERR_MSG_READ_VERTEX);
        break;
    case (ERR_MEMORY_VERTEXES_ARR):
        QMessageBox::critical(NULL, TITLE, ERR_MSG_MEMORY_VERTEXES_ARR);
        break;
    case (ERR_READ_VERTEXES_LEN):
        QMessageBox::critical(NULL, TITLE, ERR_MSG_READ_VERTEXES_LEN);
        break;
    case (ERR_VALUE_VERTEXES_LEN):
        QMessageBox::critical(NULL, TITLE, ERR_MSG_VALUE_VERTEXES_LEN);
        break;
    case (ERR_READ_LINKS_LEN):
        QMessageBox::critical(NULL, TITLE, ERR_MSG_READ_LINKS_LEN);
        break;
    case (ERR_MEMORY_LINKS_ARR):
        QMessageBox::critical(NULL, TITLE, ERR_MSG_MEMORY_LINKS_ARR);
        break;
    case (ERR_BAD_LINK):
        QMessageBox::critical(NULL, TITLE, ERR_MSG_BAD_LINK);
        break;
    case (ERR_READ_LINK):
        QMessageBox::critical(NULL, TITLE, ERR_MSG_READ_LINK);
        break;
    case (ERR_OPEN_FILE):
        QMessageBox::critical(NULL, TITLE, ERR_MSG_OPEN_FILE);
        break;
    case (ERR_NO_DATA):
        QMessageBox::critical(NULL, TITLE, ERR_MSG_NO_DATA);
        break;
    default:
        QMessageBox::critical(NULL, TITLE, ERR_MSG_UNKNOWN);
        break;
    }
}

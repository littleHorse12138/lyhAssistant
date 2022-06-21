#include "otherfunctions.h"

OtherFunctions::OtherFunctions()
{

}

void OtherFunctions::giveInfoMessage(QString info, QString title)
{
    QMessageBox::information(nullptr, title, info);
}

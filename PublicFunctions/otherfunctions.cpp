#include "otherfunctions.h"

OtherFunctions::OtherFunctions()
{

}

void OtherFunctions::giveInfoMessage(QString info, QString title)
{
    QMessageBox::information(nullptr, title, info);
}

int OtherFunctions::getNowTimeMesc()
{
    return QDateTime::currentDateTime().toMSecsSinceEpoch();
}

QDate OtherFunctions::getCurrentDay()
{
    return QDateTime::currentDateTime().date();
}

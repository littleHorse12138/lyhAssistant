#ifndef OTHERFUNCTIONS_H
#define OTHERFUNCTIONS_H
#include <QString>
#include <QMessageBox>
#include <QDateTime>
#include <QDate>
class OtherFunctions
{
public:
    OtherFunctions();
    static void giveInfoMessage(QString info, QString title = "lyhAssistant");
    static int getNowTimeMesc();
    static QDate getCurrentDay();
};

#endif // OTHERFUNCTIONS_H

#ifndef OTHERFUNCTIONS_H
#define OTHERFUNCTIONS_H
#include <QString>
#include <QMessageBox>
#include <QDateTime>
class OtherFunctions
{
public:
    OtherFunctions();
    static void giveInfoMessage(QString info, QString title = "lyhAssistant");
    static int getNowTimeMesc();
};

#endif // OTHERFUNCTIONS_H

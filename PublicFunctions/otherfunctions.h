#ifndef OTHERFUNCTIONS_H
#define OTHERFUNCTIONS_H
#include <QString>
#include <QMessageBox>
#include <QDateTime>
#include <QDate>
#include <QUrl>
#include <QDesktopServices>
#include <QSystemTrayIcon>
#include <QDebug>
class OtherFunctions
{
public:
    OtherFunctions();
    static OtherFunctions* getInstance();
    static void giveInfoMessage(QString info, QString title = "lyhAssistant");
    static void giveWarningMessage(QString info, QString title = "lyhAssistant");
    static bool giveQuestionMessage(QString text, QString title = "lyhAssistant");
    static int getNowTimeMesc();             //获取现在的时间以毫秒为单位
    static QDate getCurrentDay();   //获取当前日期
    static QTime getCurrenTime();
    static void openWeb(QString webPath);//打开网站
    static void sendMessageToWindows(QString text, QString title = "lyhAssistant", int showTime = 2000);//向windows消息栏发送通知
private:
    QSystemTrayIcon* m_sti = new QSystemTrayIcon;
};

#endif // OTHERFUNCTIONS_H

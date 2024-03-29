﻿#include "otherfunctions.h"

OtherFunctions::OtherFunctions()
{
    OtherFunctions::getInstance()->m_sti->setIcon(QIcon(":/resc/title/icon.jpg"));
    OtherFunctions::getInstance()->m_sti->show();
}

OtherFunctions* OtherFunctions::getInstance()
{
    static OtherFunctions *instance = nullptr;
    if(!instance){
        instance = new OtherFunctions;
    }
    return instance;
}

void OtherFunctions::giveInfoMessage(QString info, QString title)
{
    QMessageBox::information(nullptr, title, info);
}

void OtherFunctions::giveWarningMessage(QString info, QString title)
{
    QMessageBox::warning(nullptr, title, info);
}

bool OtherFunctions::giveQuestionMessage(QString text, QString title)
{
    return QMessageBox::question(nullptr, title, text) == QMessageBox::Yes ? true : false;
}

int OtherFunctions::getNowTimeMesc()
{
    return QDateTime::currentDateTime().toMSecsSinceEpoch();
}

QDate OtherFunctions::getCurrentDay()
{
    return QDateTime::currentDateTime().date();
}

QTime OtherFunctions::getCurrenTime()
{
    return QTime::currentTime();
}

void OtherFunctions::openWeb(QString webPath)
{
    QDesktopServices::openUrl(QUrl(webPath, QUrl::TolerantMode));
}

void OtherFunctions::sendMessageToWindows(QString text, QString title, int showTime)
{
    OtherFunctions::getInstance()->m_sti->showMessage(title, text,QSystemTrayIcon::Information, showTime);
}

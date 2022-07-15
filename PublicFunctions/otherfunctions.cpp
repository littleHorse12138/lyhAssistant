#include "otherfunctions.h"

OtherFunctions::OtherFunctions()
{

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

void OtherFunctions::openWeb(QString webPath)
{
    QDesktopServices::openUrl(QUrl(webPath, QUrl::TolerantMode));
}

void OtherFunctions::sendMessageToWindows(QString text, QString title)
{
    OtherFunctions::getInstance()->m_sti.showMessage(title, text);
    OtherFunctions::getInstance()->m_sti.setIcon(QIcon("D:\23.webp"));
    OtherFunctions::getInstance()->m_sti.setVisible(true);
    qDebug() << ".." << OtherFunctions::getInstance()->m_sti.isVisible() << OtherFunctions::getInstance()->m_sti.geometry() << OtherFunctions::getInstance()->m_sti.isSystemTrayAvailable();
}

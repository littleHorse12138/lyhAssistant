#include "mainwindow.h"

#include <QApplication>
#include <QSharedMemory>
#include <QTextCodec>
#include "PublicFunctions/filefunctions.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setFont(QFont("Microsoft Yahei", 9));

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QSharedMemory shared_memory;
        shared_memory.setKey(QString("666666"));//设置固定共享内存段的key值
        if(shared_memory.attach())   //尝试将进程附加到该共享内存段
        {
            OtherFunctions::giveWarningMessage(QStringLiteral("请勿多开程序，造成存档覆盖问题"));
            return 0;
        }

        if(shared_memory.create(1)) //创建1byte的共享内存段
        {
            MainWindow w;
            w.show();
            return a.exec();
        }

}

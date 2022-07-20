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
        shared_memory.setKey(QString("666666"));//���ù̶������ڴ�ε�keyֵ
        if(shared_memory.attach())   //���Խ����̸��ӵ��ù����ڴ��
        {
            OtherFunctions::giveWarningMessage(QStringLiteral("����࿪������ɴ浵��������"));
            return 0;
        }

        if(shared_memory.create(1)) //����1byte�Ĺ����ڴ��
        {
            MainWindow w;
            w.show();
            return a.exec();
        }

}

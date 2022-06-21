#ifndef READLOCALCONFIGURATIONWGT_H
#define READLOCALCONFIGURATIONWGT_H

#include <QWidget>
#include <QProcess>
#include <QDebug>
#include "ui_readlocalconfigurationwgt.h"
#include "PublicFunctions/stringfunctions.h"
class ReadLocalConfigurationWgt : public QWidget, public Ui_ReadLocalConfigurationWgt
{
    Q_OBJECT

public:
    explicit ReadLocalConfigurationWgt(QWidget *parent = nullptr);
    ~ReadLocalConfigurationWgt();
protected:
    void init();
    void getInfo();  //获取硬件信息并在le中显示

    QString removeStringBeforeFirstSapce(QString from);
    QString getProcessEnd(QString str);
private:
    Ui::ReadLocalConfigurationWgt *ui;
};

#endif // READLOCALCONFIGURATIONWGT_H

#ifndef CONFIGWGT_H
#define CONFIGWGT_H

#include <QWidget>
#include "ui_configwgt.h"
class ConfigWgt : public QWidget, public Ui_ConfigWgt
{
    Q_OBJECT

public:
    explicit ConfigWgt(QWidget *parent = nullptr);
    ~ConfigWgt();

private:

};

#endif // CONFIGWGT_H

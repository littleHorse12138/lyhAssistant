#ifndef SAVELOGCONFIG_H
#define SAVELOGCONFIG_H

#include <QWidget>
#include "ui_savelogconfig.h"

class SaveLogConfig : public QWidget, public Ui_SaveLogConfig
{
    Q_OBJECT

public:
    explicit SaveLogConfig(QWidget *parent = nullptr);
    ~SaveLogConfig();

private:

};

#endif // SAVELOGCONFIG_H

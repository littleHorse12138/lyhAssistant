#ifndef MAINFUNCWGT_H
#define MAINFUNCWGT_H

#include <QWidget>
#include "ui_mainfuncwgt.h"


class MainFuncWgt : public QWidget, public Ui_MainFuncWgt
{
    Q_OBJECT

public:
    explicit MainFuncWgt(QWidget *parent = nullptr);
    ~MainFuncWgt();

private:

};

#endif // MAINFUNCWGT_H

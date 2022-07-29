#ifndef MAINFUNCWGT_H
#define MAINFUNCWGT_H

#include <QWidget>
#include <QTimer>
#include "ui_mainfuncwgt.h"
#include "PublicFunctions/otherfunctions.h"
#include "CustomControl/lyhcountdown.h"
class MainFuncWgt : public QWidget, public Ui_MainFuncWgt
{
    Q_OBJECT

public:
    explicit MainFuncWgt(QWidget *parent = nullptr);
    ~MainFuncWgt();
protected:
    void init();
    void connectSignalAndSlots();

    void initOnTimeAlarm();
protected:
    void onCBOnTimeAlartToggled();

    void onBtnCountDownPressed();
private:
    QTimer * m_pTimerOnTime = nullptr;
};

#endif // MAINFUNCWGT_H

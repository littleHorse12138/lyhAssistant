#ifndef LYHCOUNTDOWN_H
#define LYHCOUNTDOWN_H

#include <QWidget>
#include <QTimer>
#include "ui_lyhcountdown.h"

class LyhCountDown : public QWidget, public Ui_LyhCountDown
{
    Q_OBJECT

public:
    explicit LyhCountDown(QWidget *parent = nullptr);
    ~LyhCountDown();

    void setIsFrameless(bool isLess);
    bool getIsFrameLess();

    void setIsTitleShow(bool isShow);
    bool getIsTitleShow();
    void setTitle(QString title);
protected:
    void init();
    void connectSignalAndSlots();

    void updateLCDNumber();
protected slots:
    void slotOnBtnExitPressed();
    void slotOnBtnContinuePressed();
    void slotOnBtnStartPressed();
    void slotOnBtnSuspendedPressed();

    void slotOnTimerTimeOut();
private:
    bool m_bIsFrameLess = false;
    bool m_bIsTitleShow = false;

    int m_leftTime = 0;
    QTimer *m_pMainTimer = nullptr;
};

#endif // LYHCOUNTDOWN_H

#include "lyhcountdown.h"

LyhCountDown::LyhCountDown(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    init();
}

LyhCountDown::~LyhCountDown()
{

}

void LyhCountDown::setIsFrameless(bool isLess)
{
    m_bIsFrameLess = isLess;
    if(m_bIsFrameLess){
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    }else{
        this->setWindowFlags(Qt::WindowStaysOnTopHint);
    }
}

bool LyhCountDown::getIsFrameLess()
{
    return m_bIsFrameLess;
}

void LyhCountDown::setIsTitleShow(bool isShow)
{
    m_bIsTitleShow = isShow;
    if(m_bIsTitleShow){
        m_pLabTitle->setVisible(true);
    }else{
        m_pLabTitle->setVisible(false);
    }
}

bool LyhCountDown::getIsTitleShow()
{
    return m_bIsTitleShow;
}

void LyhCountDown::setTitle(QString title)
{
    setIsTitleShow(true);
    m_pLabTitle->setText(title);
}

void LyhCountDown::init()
{
    m_pLabTitle->setVisible(false);
    m_pMainTimer = new QTimer(this);
    connectSignalAndSlots();
}

void LyhCountDown::connectSignalAndSlots()
{
    connect(m_pBtnExit     , &QPushButton::clicked, this, &LyhCountDown::slotOnBtnExitPressed);
    connect(m_pBtnContinue , &QPushButton::clicked, this, &LyhCountDown::slotOnBtnContinuePressed);
    connect(m_pBtnStart    , &QPushButton::clicked, this, &LyhCountDown::slotOnBtnStartPressed);
    connect(m_pBtnSuspended, &QPushButton::clicked, this, &LyhCountDown::slotOnBtnSuspendedPressed);

    connect(m_pMainTimer, &QTimer::timeout, this, &LyhCountDown::slotOnTimerTimeOut);
}

void LyhCountDown::updateLCDNumber()
{
//    m_pLCDTimer->SET
}

void LyhCountDown::slotOnBtnExitPressed()
{
    close();
}

void LyhCountDown::slotOnBtnContinuePressed()
{

}

void LyhCountDown::slotOnBtnStartPressed()
{
    QTime time = m_pTECountDown->time();
    m_leftTime = time.hour() * 3600 + time.minute() * 60 + time.second();
    m_pMainTimer->start(1000);
}

void LyhCountDown::slotOnBtnSuspendedPressed()
{

}

void LyhCountDown::slotOnTimerTimeOut()
{
  //  m_
}

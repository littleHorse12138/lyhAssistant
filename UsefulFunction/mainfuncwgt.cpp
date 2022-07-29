#include "mainfuncwgt.h"
MainFuncWgt::MainFuncWgt(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    init();
}

MainFuncWgt::~MainFuncWgt()
{

}

void MainFuncWgt::init()
{
    initOnTimeAlarm();
    connectSignalAndSlots();
}

void MainFuncWgt::connectSignalAndSlots()
{
    connect(m_pCBOnTImeAlarm, &QCheckBox::stateChanged, this, &MainFuncWgt::onCBOnTimeAlartToggled);

    connect(m_pBtnCountDown , &QPushButton::clicked, this, &MainFuncWgt::onBtnCountDownPressed);
}

void MainFuncWgt::initOnTimeAlarm()
{
    m_pTimerOnTime = new QTimer(this);
    connect(m_pTimerOnTime, &QTimer::timeout, this, [&](){
        QTime time = OtherFunctions::getCurrenTime();
        if(time.second() == 0/* && time.minute() == 0*/){
            QString text = QString::number(time.hour()) + "点已到";
            OtherFunctions::sendMessageToWindows(text);
        }
    });
}

void MainFuncWgt::onCBOnTimeAlartToggled()
{
    if(m_pCBOnTImeAlarm->isChecked()){
        m_pTimerOnTime->start(1000);
    }else{
        m_pTimerOnTime->stop();
    }
}

void MainFuncWgt::onBtnCountDownPressed()
{
    LyhCountDown *pCountDownWgt = new LyhCountDown;
    pCountDownWgt->setAttribute(Qt::WA_DeleteOnClose);
    pCountDownWgt->show();
}

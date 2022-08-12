#include "main3denginewidget.h"

Main3DEngineWidget::Main3DEngineWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    init();
}

Main3DEngineWidget::~Main3DEngineWidget()
{

}

void Main3DEngineWidget::onCBFPSChanged(bool flag)
{
    if(flag){
        m_pLabFPS->show();
    }else{
        m_pLabFPS->hide();
    }
}

void Main3DEngineWidget::init()
{
    m_pBtnExit    ->setFocusPolicy(Qt::NoFocus);
    m_pBtnConfig  ->setFocusPolicy(Qt::NoFocus);
    m_pBtnAddModel->setFocusPolicy(Qt::NoFocus);
    if(!m_pLabFPS){
        m_pLabFPS = new QLabel(this);
        m_pLabFPS->show();
        m_pLabFPS->setText("0");
    }
    connectSignalAndSlots();
}

void Main3DEngineWidget::connectSignalAndSlots()
{
    connect(m_pBtnConfig  , &QPushButton::clicked, this, &Main3DEngineWidget::slotOnBtnConfigPressed);
    connect(m_pBtnAddModel, &QPushButton::clicked, this, &Main3DEngineWidget::slotOnBtnAddModelPressed);
    connect(m_pBtnExit    , &QPushButton::clicked, this, &Main3DEngineWidget::slotOnBtnExitPressed);
}

void Main3DEngineWidget::keyPressEvent(QKeyEvent *ev)
{
    MouseAndKeyManager::getInstance()->keyPressed(ev);
}

void Main3DEngineWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastMosPos = event->pos();
}

void Main3DEngineWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint diff = event->pos() - m_lastMosPos;
    m_lastMosPos = event->pos();

    if(event->buttons() & Qt::RightButton){
        CameraManager::getInstance()->getCurCamera()->swivel(diff.x(), diff.y());
    }
}

void Main3DEngineWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0){
        CameraManager::getInstance()->getCurCamera()->wheelMoveFront();
    }else if(event->delta() < 0){
        CameraManager::getInstance()->getCurCamera()->wheelMoveBack();
    }
}

void Main3DEngineWidget::resizeEvent(QResizeEvent *event)
{
    m_pLabFPS->move(0, 0);
}

void Main3DEngineWidget::slotOnBtnConfigPressed()
{
    OpenglConfigWgt::getInstance()->show();
}

void Main3DEngineWidget::slotOnBtnAddModelPressed()
{
    if(!m_pAddModelWgt){
        m_pAddModelWgt = new AddModelWidget;
    }
    m_pAddModelWgt->show();
}

void Main3DEngineWidget::slotOnBtnExitPressed()
{
    this->close();
}



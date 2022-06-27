#include "eachgrid.h"

eachGrid::eachGrid(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    init();
}

eachGrid::~eachGrid()
{

}

void eachGrid::setIsCanChangeValue(bool isOk)
{
    m_bIsCanChangeValue = isOk;
}

bool eachGrid::getIsCanChangeValue()
{
    return m_bIsCanChangeValue;
}

void eachGrid::setIsChoose(bool isChoose)
{
    m_bIsChosen = isChoose;
    update();
}

void eachGrid::setValue(int value)
{
    if(!m_bIsCanChangeValue){
        return;
    }
    m_value = value;
    update();
}

void eachGrid::setBorderColor(QColor colorUp, QColor colorRight, QColor colorLow, QColor colorLeft)
{
    m_upColor    = colorUp;
    m_rightColor = colorRight;
    m_lowColor   = colorLow;
    m_leftColor  = colorLeft;
    update();
}

void eachGrid::setUpColor(QColor color)
{
    m_upColor    = color;
    update();
}

void eachGrid::setRightColor(QColor color)
{
    m_rightColor = color;
    update();
}

void eachGrid::setLowColor(QColor color)
{
    m_lowColor   = color;
    update();
}

void eachGrid::setLeftColor(QColor color)
{
    m_leftColor  = color;
    update();
}

void eachGrid::init()
{

}

void eachGrid::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    float w,h;
    w = width()  - 0.05;
    h = height() - 0.05;
    //背景
    if(m_bIsCanChosen){
        if(m_bIsChosen){
            painter.setBrush(m_chosenBgColor);
        }else{
            painter.setBrush(m_normalBgColor);
        }
    }else{
        painter.setBrush(m_uneditableBgColor);
    }

    painter.drawRect(0, 0, w ,h);

    //格子
    painter.setPen(m_upColor);
    painter.drawLine(QPoint(0, 0), QPoint(w, 0));
    painter.setPen(m_rightColor);
    painter.drawLine(QPoint(w, 0), QPoint(w, h));
    painter.setPen(m_lowColor);
    painter.drawLine(QPoint(w, h), QPoint(0, h));
    painter.setPen(m_leftColor);
    painter.drawLine(QPoint(0, h), QPoint(0, 0));

    QFont font1; // 需要设置的字体
    font1.resolve(QFont::AllPropertiesResolved);
    font1.setPointSize(m_fontSize);
    painter.setFont(font1);//设置字体
    painter.setPen(QColor(0, 0, 0));//字体颜色
    if(m_value == 10){
        painter.drawText(0,0,width(), height(),Qt::AlignCenter,"e");//位置和内容
    }else if(m_value != -1){
        painter.drawText(0,0,width(), height(),Qt::AlignCenter,QString::number(m_value));//位置和内容
    }

}

void eachGrid::mousePressEvent(QMouseEvent *event)
{
    if(!m_bIsCanChosen){
        return;
    }
    m_bIsChosen = !m_bIsChosen;
    emit sgClicked(m_value);
    update();
}


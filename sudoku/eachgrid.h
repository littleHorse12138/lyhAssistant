#ifndef EACHGRID_H
#define EACHGRID_H

#include <QWidget>
#include <QPainter>
#include "ui_eachgrid.h"
class eachGrid : public QWidget, public Ui_eachGrid
{
    Q_OBJECT

public:
    explicit eachGrid(QWidget *parent = nullptr);
    ~eachGrid();

    void setIsCanChangeValue(bool isOk); //设置是否能改变值
    bool getIsCanChangeValue();
    void setIsCanChoose(bool isOk); //设置是否能选中
    bool getIsCanChoose();
    void setIsChoose(bool isChoose);

    void setValue(int value);
    void setBorderColor(QColor colorUp, QColor colorRight, QColor colorLow, QColor colorLeft);
    void setUpColor(QColor color);
    void setRightColor(QColor color);
    void setLowColor(QColor color);
    void setLeftColor(QColor color);
signals:
    void sgClicked(int val);
protected:
    void init();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    int m_value = -1;
    bool m_bIsCanChangeValue = true;
    bool m_bIsCanChosen = true;
    bool m_bIsChosen = false;
    QColor m_upColor    = QColor(0, 0, 0);
    QColor m_rightColor = QColor(0, 0, 0);
    QColor m_lowColor   = QColor(0, 0, 0);
    QColor m_leftColor  = QColor(0, 0, 0);

    QColor m_uneditableTextColor =  QColor(0, 0, 255);
    QColor m_editableTextColor   =  QColor(255, 0, 0);

    QColor m_normalBgColor     = QColor(255, 255, 255);
    QColor m_uneditableBgColor = QColor(150, 150, 150);
    QColor m_chosenBgColor     = QColor(100, 100, 100);
    int m_fontSize = 20;
};

#endif // EACHGRID_H

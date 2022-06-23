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

void eachGrid::setValue(int value)
{
    if(!m_bIsCanChangeValue){
        return;
    }
    value %= 10;
    m_pShowLab->setText(QString::number(value));
}

void eachGrid::init()
{
    setStyleSheet("QWidget{\n"
                  "border:0.5px solid rgb(0,0,0);\n"
                  "}\n");
}

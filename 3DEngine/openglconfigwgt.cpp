#include "openglconfigwgt.h"

OpenglConfigWgt::OpenglConfigWgt(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    init();
}

OpenglConfigWgt::~OpenglConfigWgt()
{

}

OpenglConfigWgt *OpenglConfigWgt::getInstance()
{
    static OpenglConfigWgt* instance = nullptr;
    if(!instance){
        instance = new OpenglConfigWgt;
    }
    return instance;
}

QColor OpenglConfigWgt::getBackGroundColor()
{
    float r = m_pSBBGColorR->value();
    float g = m_pSBBGColorG->value();
    float b = m_pSBBGColorB->value();
//    r /= 255;
//    g /= 255;
//    b /= 255;
    return QColor(r, g, b);
}

void OpenglConfigWgt::init()
{
    connectSignalAndSlots();
    m_pSBBGColorR->setRange(0, 255);
    m_pSBBGColorG->setRange(0, 255);
    m_pSBBGColorB->setRange(0, 255);

    m_pSBBGColorR->setValue(100);
    m_pSBBGColorG->setValue(140);
    m_pSBBGColorB->setValue(120);
}

void OpenglConfigWgt::connectSignalAndSlots()
{

}


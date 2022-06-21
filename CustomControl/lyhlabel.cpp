#include "lyhlabel.h"

LYHLabel::LYHLabel(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
}

LYHLabel::~LYHLabel()
{

}

void LYHLabel::setText(QString text)
{
    m_pLabMain->setText(text);
}

void LYHLabel::setPic(QString picPath)
{
    m_picPath = picPath;
    updateQSS();
}

void LYHLabel::updateQSS()
{
    m_pLabMain->setStyleSheet("QLabel{"
                              "border-image:url(" + m_picPath + ");\n"
    "}");
}

#include "configwgt.h"

ConfigWgt::ConfigWgt(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    init();
}

ConfigWgt::~ConfigWgt()
{

}

void ConfigWgt::init()
{
    connectSignalAndSlots();
}

void ConfigWgt::connectSignalAndSlots()
{

}

void ConfigWgt::onBtnEnsurePressed()
{
    close();
}

void ConfigWgt::onBtnOpenCacheFilePressed()
{

}

#include "mainfuncwgt.h"
#include "ui_mainfuncwgt.h"

MainFuncWgt::MainFuncWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainFuncWgt)
{
    ui->setupUi(this);
}

MainFuncWgt::~MainFuncWgt()
{
    delete ui;
}

#ifndef ADDMODELWIDGET_H
#define ADDMODELWIDGET_H

#include <QWidget>
#include "ui_addmodelwidget.h"
class AddModelWidget : public QWidget, Ui_AddModelWidget
{
    Q_OBJECT

public:
    explicit AddModelWidget(QWidget *parent = nullptr);
    ~AddModelWidget();

private:

};

#endif // ADDMODELWIDGET_H

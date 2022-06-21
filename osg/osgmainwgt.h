#ifndef OSGMAINWGT_H
#define OSGMAINWGT_H

#include <QWidget>
#include "ui_osgmainwgt.h"

class OsgMainWgt : public QWidget, public Ui_OsgMainWgt
{
    Q_OBJECT

public:
    explicit OsgMainWgt(QWidget *parent = nullptr);
    ~OsgMainWgt();

private:

};

#endif // OSGMAINWGT_H

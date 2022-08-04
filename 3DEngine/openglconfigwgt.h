#ifndef OPENGLCONFIGWGT_H
#define OPENGLCONFIGWGT_H

#include <QWidget>
#include "ui_openglconfigwgt.h"
namespace Ui {
class OpenglConfigWgt;
}

class OpenglConfigWgt : public QWidget, public Ui_OpenglConfigWgt
{
    Q_OBJECT

public:
    explicit OpenglConfigWgt(QWidget *parent = nullptr);
    ~OpenglConfigWgt();
    static OpenglConfigWgt* getInstance();
    QColor getBackGroundColor();
protected:
    void init();
    void connectSignalAndSlots();
private:

};

#endif // OPENGLCONFIGWGT_H

#ifndef MAINFUNCWGT_H
#define MAINFUNCWGT_H

#include <QWidget>

namespace Ui {
class MainFuncWgt;
}

class MainFuncWgt : public QWidget
{
    Q_OBJECT

public:
    explicit MainFuncWgt(QWidget *parent = nullptr);
    ~MainFuncWgt();

private:
    Ui::MainFuncWgt *ui;
};

#endif // MAINFUNCWGT_H

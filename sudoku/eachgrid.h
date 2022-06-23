#ifndef EACHGRID_H
#define EACHGRID_H

#include <QWidget>
#include "ui_eachgrid.h"
class eachGrid : public QWidget, public Ui_eachGrid
{
    Q_OBJECT

public:
    explicit eachGrid(QWidget *parent = nullptr);
    ~eachGrid();

    void setIsCanChangeValue(bool isOk);
    bool getIsCanChangeValue();
    void setValue(int value);
protected:
    void init();
private:
    int value = 0;
    bool m_bIsCanChangeValue = true;
};

#endif // EACHGRID_H

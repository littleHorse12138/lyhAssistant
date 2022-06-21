#ifndef SUDOKUMAINWGT_H
#define SUDOKUMAINWGT_H

#include <QWidget>
#include <QGridLayout>
#include "ui_sudokumainwgt.h"
#include "eachgrid.h"
class SudokuMainWgt : public QWidget, public Ui_SudokuMainWgt
{
    Q_OBJECT

public:
    explicit SudokuMainWgt(QWidget *parent = nullptr);
    ~SudokuMainWgt();
    void init();
private:
    QGridLayout *m_pGridWgt;
    QList <eachGrid*> m_grids
    ;
};

#endif // SUDOKUMAINWGT_H

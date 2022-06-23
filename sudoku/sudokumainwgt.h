#ifndef SUDOKUMAINWGT_H
#define SUDOKUMAINWGT_H

#include <QWidget>
#include <QPainter>
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
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
private:
    QGridLayout *m_pGridWgt;
    QList <eachGrid*> m_grids;

    float m_singleWidth = 1;
    float m_singleHeight = 1;
};

#endif // SUDOKUMAINWGT_H

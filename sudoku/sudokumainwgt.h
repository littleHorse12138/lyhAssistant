#ifndef SUDOKUMAINWGT_H
#define SUDOKUMAINWGT_H

#include <QWidget>
#include <QPainter>
#include <QGridLayout>
#include <PublicFunctions/otherfunctions.h>
#include "ui_sudokumainwgt.h"
#include "eachgrid.h"
class SudokuMainWgt : public QWidget, public Ui_SudokuMainWgt
{
    Q_OBJECT

public:
    explicit SudokuMainWgt(QWidget *parent = nullptr);
    ~SudokuMainWgt();
protected:
    void init();
    void connectSignalAndSlots();
    void resizeEvent(QResizeEvent *event);

    void updateState();
protected slots:
    void slotChosenNumber(int val);
    void slotClickItem(int val);
    void slotClearClick(int val);

    void slotCal();
private:
    QGridLayout *m_pGridWgt;
    QList <eachGrid*> m_grids;
    QList <eachGrid*> m_gridChoose;
    eachGrid* m_chosenGrid = nullptr;
    eachGrid* m_chosenGridNumber = nullptr;
    QColor m_bigBlock   = QColor(255, 0, 0);
    QColor m_smallBlock = QColor(0, 0, 0);

    int m_nowChosenNumber = 0;
};

#endif // SUDOKUMAINWGT_H

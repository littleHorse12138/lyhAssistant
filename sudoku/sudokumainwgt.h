#ifndef SUDOKUMAINWGT_H
#define SUDOKUMAINWGT_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QList>
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
    void mousePressEvent(QMouseEvent *ev);
    void moveEvent(QMoveEvent *ev);

    void updateState();
protected slots:
    void slotChosenNumber(int val);
    void slotClickItem(int val);
    void slotClearClick(int val);

    void slotCal();

    QList<QList<int>> getCal(QList<QList<int>> needToCal); //获取答案
    QList<QList<QList<int>>> sepList(QList<QList<int>> needToSep); //对于不满足条件的list，将其划分
    bool checkIsOk(QList<QList<int>> needToCheck); //查看目前的答案是否满足条件
    int getGridBlock(int row, int column); //获取小块处于哪个大块
    QList<QList<int>> removeUnqualified(QList<QList<int>> map);
private:
    QGridLayout *m_pGridWgt;
    QList <eachGrid*> m_grids;
    QList <eachGrid*> m_gridChoose;
    eachGrid* m_chosenGrid = nullptr;
    eachGrid* m_chosenGridNumber = nullptr;
    QColor m_bigBlock   = QColor(255, 0, 0);
    QColor m_smallBlock = QColor(0, 0, 0);

    int m_nowChosenNumber = 1;
};

#endif // SUDOKUMAINWGT_H

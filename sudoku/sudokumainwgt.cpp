#include "sudokumainwgt.h"
#include <QDebug>
SudokuMainWgt::SudokuMainWgt(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    init();
}

SudokuMainWgt::~SudokuMainWgt()
{

}

void SudokuMainWgt::init()
{
    setWindowTitle("sudoku");
    m_pGridWgt = new QGridLayout(m_pGameWgt);
    m_pGridWgt->setSpacing(0);
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++){
            eachGrid *singleWgt = new eachGrid();
            m_grids.append(singleWgt);
            m_pGridWgt->addWidget(singleWgt, i, j);
        }
    }
    for(int i = 0; i < 9; i++){
        eachGrid *singleWgt = new eachGrid();
        m_gridChoose.append(singleWgt);
        singleWgt->setValue(i);
        singleWgt->setIsCanChangeValue(false);
        m_pHLChoose->addWidget(singleWgt);
    }
    for(int i = 0; i < 1; i++){
        eachGrid *singleWgt = new eachGrid();
        m_gridChoose.append(singleWgt);
        singleWgt->setValue(10);
        singleWgt->setIsCanChangeValue(false);
        m_pHLChoose->addWidget(singleWgt);
    }
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++){
            int cntt = i * 9 + j;
            if(i % 3 == 0){
                m_grids[cntt]->setUpColor(m_bigBlock);
            }
            if(i % 3 == 2){
                m_grids[cntt]->setLowColor(m_bigBlock);
            }
            if(j % 3 == 0){
                m_grids[cntt]->setLeftColor(m_bigBlock);
            }
            if(j % 3 == 2){
                m_grids[cntt]->setRightColor(m_bigBlock);
            }
        }
    }
    m_chosenGridNumber = m_gridChoose[0];
    updateState();
    connectSignalAndSlots();
    resize(400, 467);
}

void SudokuMainWgt::connectSignalAndSlots()
{
    for(int i = 0; i < 9; i++){
        connect(m_gridChoose[i], &eachGrid::sgClicked, this, &SudokuMainWgt::slotChosenNumber);
    }
    connect(m_gridChoose[9], &eachGrid::sgClicked, this, &SudokuMainWgt::slotClearClick);
    for(int i = 0; i < 81; i++){
        connect(m_grids[i], &eachGrid::sgClicked, this, &SudokuMainWgt::slotClickItem);
    }
    connect(m_pBtnCal, &QPushButton::clicked, this, &SudokuMainWgt::slotCal);
}

void SudokuMainWgt::resizeEvent(QResizeEvent *event)
{
    float size = qMin(m_pGameWgt->width(), m_pGameWgt->height());
    m_pGameWgt->resize(size, size);
    update();
    repaint();
}

void SudokuMainWgt::updateState()
{
    for(auto grid: m_grids){
        grid->setIsChoose(false);
    }
    for(auto grid: m_gridChoose){
        grid->setIsChoose(false);
    }
    if(m_chosenGrid){
        m_chosenGrid->setIsChoose(true);
    }
    if(m_chosenGridNumber){
        m_chosenGridNumber->setIsChoose(true);
    }
}

void SudokuMainWgt::slotChosenNumber(int val)
{
    m_nowChosenNumber = val;
    auto sender = QObject::sender();
    m_chosenGridNumber = dynamic_cast<eachGrid*>(sender);
    updateState();
}

void SudokuMainWgt::slotClickItem(int val)
{
    auto sender = QObject::sender();
    m_chosenGrid = dynamic_cast<eachGrid*>(sender);
    int nowVal = m_nowChosenNumber;
    m_chosenGrid->setValue(nowVal);
    updateState();
}

void SudokuMainWgt::slotClearClick(int val)
{
    auto sender = QObject::sender();
    m_chosenGridNumber = dynamic_cast<eachGrid*>(sender);
    m_nowChosenNumber = -1;
    updateState();
}

void SudokuMainWgt::slotCal()
{
    int startTime = OtherFunctions::getNowTimeMesc();

    /* by my own*/
    int endTime = OtherFunctions::getNowTimeMesc();
    qDebug() << "calOntTime" << endTime - startTime << "ms";
}

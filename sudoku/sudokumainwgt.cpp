#include "sudokumainwgt.h"

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
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++){
            eachGrid *m_pSingleWgt = new eachGrid();
            m_grids.append(m_pSingleWgt);
            m_pGridWgt->addWidget(m_pSingleWgt, i, j);
        }
    }
}

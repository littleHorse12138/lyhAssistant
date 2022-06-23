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
    m_pGridWgt->setSpacing(0);
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++){
            eachGrid *m_pSingleWgt = new eachGrid();
            m_grids.append(m_pSingleWgt);
            m_pGridWgt->addWidget(m_pSingleWgt, i, j);
        }
    }
}

void SudokuMainWgt::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.setPen(QColor(255, 0, 0));
    for(int i = 0; i < 4; i++){
        float x = m_pGridWgt->widget()->x() + i * m_singleWidth;
        float y = m_pGridWgt->widget()->y() + m_pGridWgt->widget()->height();
        painter.drawLine(QPoint(x, 0), QPoint(x, y));
    }
}

void SudokuMainWgt::resizeEvent(QResizeEvent *event)
{
    m_singleWidth = m_pGridWgt->widget()->width();
    m_singleHeight = m_pGridWgt->widget()->height();
    m_singleHeight /= 9;
    m_singleWidth /= 9;
}

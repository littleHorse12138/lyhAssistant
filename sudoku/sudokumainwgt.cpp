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
        singleWgt->setValue(i+1);
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
    QList <QList<int>> stillOk;
    for(int i = 0; i < 81; i++){
        QList <int> ok;
        if(m_grids[i]->getValue() == -1){
            for(int j = 1; j <= 9; j++){
                ok.append(j);
            }
            stillOk.append(ok);
        }else{
           ok.append(m_grids[i]->getValue());
           stillOk.append(ok);
        }
    }
    QList <QList<int>> ans = getCal(stillOk);
    if(ans.count() >= 1){
        for(int i = 0; i < 81; i++){
           m_grids[i]->setValue(ans[0][i]);
        }
    }
    OtherFunctions::giveInfoMessage("success " + QString::number(ans.count()) + " slove!");


    int endTime = OtherFunctions::getNowTimeMesc();
    qDebug() << "calOntTime" << endTime - startTime << "ms";
}

QList<QList<int>> SudokuMainWgt::getCal(QList<QList<int>> needToCal)
{
     needToCal = removeUnqualified(needToCal);

     QList <int> an;
     for(auto n:needToCal){
         if(n.count() == 1){
             an.append(n[0]);
         }else{
             an.append(-1);
         }
     }

     QList<QList<int>> ans;
     ans.append(an);
     return ans;
     if(checkIsOk(needToCal)){
         QList <int> an;
         for(auto n:needToCal){
             an.append(n[0]);
         }
         ans.append(an);
     }else{
        QList<QList<QList<int>>> seps = sepList(needToCal);
        for(auto sep: seps){
            ans += getCal(sep);
        }
     }
     return ans;
}

QList<QList<QList<int>>> SudokuMainWgt::sepList(QList<QList<int>> needToSep)
{
    QList<QList<QList<int>>> ans;
    for(int i = 0; i < 81; i++){
        if(needToSep[i].count() != 1){
            for(int j = 0; j < needToSep[i].count(); j++){
                QList<QList<int>> temp = needToSep;
                QList <int> newOne;
                newOne.append(temp[i][j]);
                temp[i] = newOne;
                ans.append(temp);
            }
            qDebug() << "__FUNCTION__" << ans.count();
            return ans;
        }
    }
}

bool SudokuMainWgt::checkIsOk(QList<QList<int> > needToCheck)
{
    for(auto list: needToCheck){
        if(list.count() != 1){
            return false;
        }
    }
    return true;
}

int SudokuMainWgt::getGridBlock(int row, int column)
{
    if(row < 3){
        if(column < 3){
            return 1;
        }else if(row < 6){
            return 2;
        }else{
            return 3;
        }
    }else if(row < 6){
        if(column < 3){
            return 4;
        }else if(row < 6){
            return 5;
        }else{
            return 6;
        }
    }else{
        if(column < 3){
            return 7;
        }else if(row < 6){
            return 8;
        }else{
            return 9;
        }
    }
}

QList<QList<int> > SudokuMainWgt::removeUnqualified(QList<QList<int> > map)
{
    bool stillCanCal = true;
    while(stillCanCal){
        stillCanCal = false;
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                int cnttBefore = i * 9 + j;
                if(map[cnttBefore].count() != 1){
                    continue;
                }
                int nowBlock = getGridBlock(i, j);
                int nowValue = map[cnttBefore][0];
                for(int k = 0; k < 9; k++){
                    for(int z = 0; z < 9; z++){
                        if(i == k && j == k){
                            continue;
                        }
                        int cnttAfter = k * 9 + z;
                        if(map[cnttAfter].count() == 1){
                            continue;
                        }
                        if(k == i || z == j || nowBlock == getGridBlock(k, z)){
                            if(map[cnttAfter].contains(nowValue)){
                                QList <int> newOk;
                                for(auto t: map[cnttAfter]){
                                    if(t != nowValue){
                                        newOk.append(t);
                                    }
                                }
                                map[cnttAfter] = newOk;
                                stillCanCal = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return map;
}

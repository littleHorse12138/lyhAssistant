#include "mainsavewgt.h"

MainSaveWgt::MainSaveWgt(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    init();
}

MainSaveWgt::~MainSaveWgt()
{

}

void MainSaveWgt::init()
{
    OtherFunctions::sendMessageToWindows("wolele");
    m_pTabWgt->setColumnCount(4);
    m_pTabWgt->setRowCount(100);
    m_pCBFinished->setChecked(true);
    m_pCBUnfinished->setChecked(true);
    m_itemWgt = new ItemWgt;
    connectSignalAndSlots();
    updateWgt();
    m_defaultSavePath = FileFunctions::getExePath() + "/cache";
    if(!FileFunctions::isDirExist(m_defaultSavePath)){
        qDebug() << ".." << FileFunctions::createDir(m_defaultSavePath);
    }
    m_defaultSavePath += "/autoSave.json";
    readDefaultData();
    autoSaveData();
}

void MainSaveWgt::connectSignalAndSlots()
{
    connect(m_pBtnAddItem, &QPushButton::clicked , this, &MainSaveWgt::slotOnBtnAddItemPressed);
    connect(m_pBtnSaveAll, &QPushButton::clicked , this, &MainSaveWgt::slotOnBtnSaveAllPressed);
    connect(m_pBtnExport, &QPushButton::clicked , this, &MainSaveWgt::slotOnBtnExportPressed);
    connect(m_pBtnImport, &QPushButton::clicked , this, &MainSaveWgt::slotOnBtnImportPressed);
    connect(m_itemWgt    , &ItemWgt::sgAddNewItem, this, &MainSaveWgt::slotOnAddNewItem);
    connect(m_itemWgt    , &ItemWgt::sgDeleteItem, this, &MainSaveWgt::slotOnDeleteItem);

    connect(m_pCBFinished   , &QCheckBox::clicked, this, &MainSaveWgt::updateWgt);
    connect(m_pCBUnfinished , &QCheckBox::clicked, this, &MainSaveWgt::updateWgt);
}

void MainSaveWgt::openItemWidget(QVariantMap data)
{
    if(m_itemWgt){
        disconnect(m_itemWgt    , &ItemWgt::sgDeleteItem, this, &MainSaveWgt::slotOnDeleteItem);
        disconnect(m_itemWgt, &ItemWgt::sgAddNewItem, this, &MainSaveWgt::slotOnAddNewItem);
        delete m_itemWgt;
    }
    m_itemWgt = new ItemWgt;
    connect(m_itemWgt, &ItemWgt::sgAddNewItem, this, &MainSaveWgt::slotOnAddNewItem);
    connect(m_itemWgt    , &ItemWgt::sgDeleteItem, this, &MainSaveWgt::slotOnDeleteItem);
    m_itemWgt->setData(data);
    m_itemWgt->show();
}

QVariantMap MainSaveWgt::getNewData()
{
    QVariantMap data;
    QDate currentTime = OtherFunctions::getCurrentDay();
    QString Uuid = StringFunctions::createUuid();
    data.insert("uuid", Uuid);
    data.insert("date", currentTime);
    return data;
}

QVariantMap MainSaveWgt::getData()
{
    QVariantMap data;
    QVariantList list;
    for(auto item: m_items){
        list.append(item);
    }
    data.insert("check", GlobalDefine::SAVE_LOG::MAIN);
    data.insert("data", list);
    data.insert("isShowFinish"  , m_pCBFinished->isChecked());
    data.insert("isShowUnfinish", m_pCBUnfinished->isChecked());
    data.insert("name",m_pLESaveNAME->text());
    return data;
}

void MainSaveWgt::setData(QVariantMap data)
{
    int check = data.value("check").toInt();
    if(check == GlobalDefine::SAVE_LOG::ITEM){
        openItemWidget(data);
        return;
    }else if(check == GlobalDefine::SAVE_LOG::MAIN){
        m_items.clear();
        QVariantList items = data.value("data").toList();
        for(auto item: items){
            m_items.append(item.toMap());
        }
        bool isShowFinish = data.value("isShowFinish").toBool();
        bool isShowUnFinish = data.value("isShowUnfinish").toBool();
        QString name = data.value("name").toString();
        m_pLESaveNAME->setText(name);
        m_pCBFinished->setChecked(isShowFinish);
        m_pCBUnfinished->setChecked(isShowUnFinish);
        m_pLESaveNAME->setText(name);
        updateWgt();
    }
}

void MainSaveWgt::autoSaveData()
{
   m_pSaveTimer = new QTimer;
   connect(m_pSaveTimer, &QTimer::timeout, this, &MainSaveWgt::slotOnSaveTimeout);
}

bool MainSaveWgt::saveData(QVariantMap data, QString path, bool isAuto)
{
    if(FileFunctions::isFileExist(path) && !isAuto){
        if(!OtherFunctions::giveQuestionMessage("目标已存在，是否继续?")){
            return false;
        }
    }
    return FileFunctions::writeJson(path, data, true);
}

QVariantMap MainSaveWgt::readData(QString filePath)
{
    return FileFunctions::readJson(filePath);
}

void MainSaveWgt::readDefaultData()
{
    setData(readData(m_defaultSavePath));
}

void MainSaveWgt::closeEvent(QCloseEvent *event)
{
    slotOnSaveTimeout();
    OtherFunctions::sendMessageToWindows("closed!");
}

bool MainSaveWgt::cmp(QVariantMap a, QVariantMap b)
{
    if(a.value("isOnTop").toBool()){
        return true;
    }else if(b.value("isOnTop").toBool()){
        return false;
    }
}

void MainSaveWgt::sortItems()
{
    qSort(m_items.begin(), m_items.end(), cmp);
}

void MainSaveWgt::updateWgt()
{
    m_pTabWgt->clear();
    m_buttons.clear();
    sortItems();
    QTableWidgetItem *Title       = new QTableWidgetItem("标题");
    QTableWidgetItem *IsFinish    = new QTableWidgetItem("isFinish");
    QTableWidgetItem *Date        = new QTableWidgetItem("date");
    m_pTabWgt->setItem(0, 0, Title);
    m_pTabWgt->setItem(0, 2, IsFinish);
    m_pTabWgt->setItem(0, 1, Date);
    int cntt = 1;
    for(int i = 0; i < m_items.count(); i++){
        QString title = m_items[i].value("title").toString();
        QString date = m_items[i].value("date").toDate().toString();
        bool isFinish = m_items[i].value("isFinish").toBool();
        QString finish;
        if(isFinish){
            finish = "yes";
        }else{
            finish = "no";
        }
        QTableWidgetItem *itemTitle       = new QTableWidgetItem(title);
        QTableWidgetItem *itemIsFinish    = new QTableWidgetItem(finish);
        QTableWidgetItem *itemDate        = new QTableWidgetItem(date);
        QPushButton *m_pBtnOpen = new QPushButton;
        m_pBtnOpen->setText("check");
        if(isFinish && m_pCBFinished->isChecked()){
            m_pTabWgt->setItem(cntt, 0, itemTitle);
            m_pTabWgt->setItem(cntt, 2, itemIsFinish);
            m_pTabWgt->setItem(cntt, 1, itemDate);
            m_pTabWgt->setCellWidget(cntt, 3, m_pBtnOpen);
            cntt++;
        }else if(!isFinish && m_pCBUnfinished->isChecked()){
            m_pTabWgt->setItem(cntt, 0, itemTitle);
            m_pTabWgt->setItem(cntt, 2, itemIsFinish);
            m_pTabWgt->setItem(cntt, 1, itemDate);
            m_pTabWgt->setCellWidget(cntt, 3, m_pBtnOpen);
            cntt++;
        }
        connect(m_pBtnOpen, &QPushButton::clicked, this, &MainSaveWgt::slotOnCheckItem);
        m_buttons.append(m_pBtnOpen);
        m_pBtnOpen->setObjectName(QString::number(i));
    }
}

void MainSaveWgt::slotOnBtnAddItemPressed()
{
    openItemWidget();
    m_itemWgt->setData(getNewData());
}

void MainSaveWgt::slotOnBtnSaveAllPressed()
{

}

void MainSaveWgt::slotOnAddNewItem(QVariantMap data)
{
    int insertIndex = -1;
    int cnt = 0;
    for(auto item: m_items){
        if(item.value("uuid").toString() == data.value("uuid").toString()){
            insertIndex = cnt;
        }
        cnt++;
    }
    if(insertIndex == -1){
        m_items.append(data);
    }else{
        m_items[insertIndex] = data;
    }
    updateWgt();
}

void MainSaveWgt::slotOnDeleteItem(QVariantMap data)
{
    QList <QVariantMap> newItems;
    for(auto item: m_items){
        if(item.value("uuid").toString() != data.value("uuid").toString()){
            newItems.append(item);
        }
    }
    m_items = newItems;
    updateWgt();
}

void MainSaveWgt::slotOnCheckItem()
{
    QPushButton *sender = dynamic_cast<QPushButton*>(QObject::sender());
    for(int i = 0; i < m_buttons.count(); i++){
        if(sender == m_buttons[i]){
            openItemWidget(m_items[i]);
            break;
        }
    }
}

void MainSaveWgt::slotOnBtnExportPressed()
{
    QString dirName = FileFunctions::getDirName();
    if(m_pLESaveNAME->text() == ""){
        dirName += "/null.json";
    }else{
        dirName += "/" + m_pLESaveNAME->text() + ".json";
    }
    if(FileFunctions::isFileExist(dirName)){
        if(!OtherFunctions::giveQuestionMessage("存档已存在，是否覆盖?")){
            return;
        }
    }else{
        FileFunctions::createFile(dirName);
    }
    qDebug() << dirName << "name!";
    FileFunctions::writeJson(dirName, getData());
}

void MainSaveWgt::slotOnBtnImportPressed()
{
    QString fileName = FileFunctions::getFileName();
    QVariantMap data = FileFunctions::readJson(fileName);
    setData(data);
}

void MainSaveWgt::slotOnSaveTimeout()
{
    qDebug() << "doSave";
    saveData(getData(), m_defaultSavePath, true);
}

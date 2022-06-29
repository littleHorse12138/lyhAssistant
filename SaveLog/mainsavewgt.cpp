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
    m_pTabWgt->setColumnCount(4);
    m_pTabWgt->setRowCount(100);
    m_pCBFinished->setChecked(true);
    m_pCBUnfinished->setChecked(true);
    m_itemWgt = new ItemWgt;
    connectSignalAndSlots();
    updateWgt();
}

void MainSaveWgt::connectSignalAndSlots()
{
    connect(m_pBtnAddItem, &QPushButton::clicked , this, &MainSaveWgt::slotOnBtnAddItemPressed);
    connect(m_pBtnSaveAll, &QPushButton::clicked , this, &MainSaveWgt::slotOnBtnSaveAllPressed);
    connect(m_pBtnExport, &QPushButton::clicked , this, &MainSaveWgt::slotOnBtnExportPressed);
    connect(m_pBtnImport, &QPushButton::clicked , this, &MainSaveWgt::slotOnBtnImportPressed);
    connect(m_itemWgt    , &ItemWgt::sgAddNewItem, this, &MainSaveWgt::slotOnAddNewItem);

    connect(m_pCBFinished   , &QCheckBox::clicked, this, &MainSaveWgt::updateWgt);
    connect(m_pCBUnfinished , &QCheckBox::clicked, this, &MainSaveWgt::updateWgt);
}

void MainSaveWgt::openItemWidget(QVariantMap data)
{
    if(m_itemWgt){
        disconnect(m_itemWgt, &ItemWgt::sgAddNewItem, this, &MainSaveWgt::slotOnAddNewItem);
        delete m_itemWgt;
    }
    m_itemWgt = new ItemWgt;
    connect(m_itemWgt, &ItemWgt::sgAddNewItem, this, &MainSaveWgt::slotOnAddNewItem);
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
    data.insert("check", GlobalDefine::SAVE_LOG::MAIN);
    data.insert("data",  QVariant::fromValue<QList<QVariantMap>>(m_items));
    data.insert("isShowFinish"  , m_pCBFinished->isChecked());
    data.insert("isShowUnfinish", m_pCBUnfinished->isChecked());
    return data;
}

void MainSaveWgt::setData(QVariantMap data)
{
    int check = data.value("check").toInt();
    if(check == GlobalDefine::SAVE_LOG::ITEM){
        openItemWidget(data);
        return;
    }else if(check == GlobalDefine::SAVE_LOG::MAIN){
        QList<QVariantMap> items = data.value("data").value<QList<QVariantMap>>();
        m_items = items;
        bool isShowFinish = data.value("isShowFinish").toBool();
        bool isShowUnFinish = data.value("isShowUnfinish").toBool();
        m_pCBFinished->setChecked(isShowFinish);
        m_pCBUnfinished->setChecked(isShowUnFinish);
        updateWgt();
    }
}

void MainSaveWgt::updateWgt()
{
    m_pTabWgt->clear();
    m_buttons.clear();
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
    m_items.append(data);
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
    QString fileName = FileFunctions::getFileName();
    FileFunctions::writeJson(fileName, getData());
}

void MainSaveWgt::slotOnBtnImportPressed()
{
    QString fileName = FileFunctions::getFileName();
    if(!FileFunctions::isFileExist(fileName))
    qDebug() << "imposs" << fileName;
    QVariantMap data = FileFunctions::readJson(fileName);
    setData(data);
}

#include "itemwgt.h"

ItemWgt::ItemWgt(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    init();
}

ItemWgt::~ItemWgt()
{

}

void ItemWgt::setUuid(QString uuid)
{
    m_uuid = uuid;
}

void ItemWgt::updateWgt()
{
    m_pLabUuid->setText(m_uuid);
}

QVariantMap ItemWgt::getData()
{
    QVariantMap data;
    data.insert("isFinish", m_pCBIsFinished->isChecked());
    data.insert("title", m_pLETitle->text());
    data.insert("text",  m_pTEMainText->toPlainText());
    data.insert("date",  m_pDEDate->date());
    data.insert("uuid", m_uuid);
    data.insert("web", m_pLENet->text());
    data.insert("isOnTop", m_pCBIsOnTop->isChecked());
    return data;
}

void ItemWgt::setData(QVariantMap data)
{
    bool isFinish = data.value("isFinish").toBool();
    bool isOnTop = data.value("isOnTop").toBool();
    QString title = data.value("title").toString();
    QString text  = data.value("text").toString();
    QDate date  = data.value("date").toDate();
    QString web = data.value("web").toString();
    m_uuid = data.value("uuid").toString();
    m_pLabUuid->setText("uuid:" + m_uuid);
    m_pLENet->setText(web);
    m_pTEMainText->setText(text);
    m_pLETitle->setText(title);
    m_pDEDate->setDate(date);
    m_pCBIsOnTop->setChecked(isOnTop);
    m_pCBIsFinished->setChecked(isFinish);
}

void ItemWgt::init()
{
    connectSignalAndSlots();
}

void ItemWgt::connectSignalAndSlots()
{
    connect(m_pBtnDelete   , &QPushButton::clicked, this, &ItemWgt::slotOnBtnClosePressed);
    connect(m_pBtnEnsureAdd, &QPushButton::clicked, this, &ItemWgt::slotOnBtnEnsurePressed);
    connect(m_pBtnEnsure   , &QPushButton::clicked, this, &ItemWgt::slotOnBtnEndPressed);
    connect(m_pBtnOpenWeb  , &QPushButton::clicked, this, &ItemWgt::slotOnOpenWebPressed);
}

void ItemWgt::slotOnBtnClosePressed()
{
    if(!OtherFunctions::giveQuestionMessage("确定删除?")){
        return;
    }
    QVariantMap data = getData();
    emit sgDeleteItem(data);
    close();
}

void ItemWgt::slotOnBtnEnsurePressed()
{
    QVariantMap data = getData();
    emit sgAddNewItem(data);
    close();
}

void ItemWgt::slotOnBtnEndPressed()
{
    QVariantMap data = getData();
    emit sgAddNewItem(data);
    close();
}

void ItemWgt::slotOnOpenWebPressed()
{
    QString path = m_pLENet->text();
    if(path == ""){
        return;
    }
    OtherFunctions::openWeb(path);
}


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
    return data;
}

void ItemWgt::setData(QVariantMap data)
{
    bool isFinish = data.value("isFinish").toBool();
    QString title = data.value("title").toString();
    QString text  = data.value("text").toString();
    QDate date  = data.value("date").toDate();
    m_uuid = data.value("uuid").toString();
    m_pLabUuid->setText("uuid:" + m_uuid);
    m_pDEDate->setDate(date);
}

void ItemWgt::init()
{
    connectSignalAndSlots();
}

void ItemWgt::connectSignalAndSlots()
{
    connect(m_pBtnDelete   , &QPushButton::clicked, this, &ItemWgt::slotOnBtnClosePressed);
    connect(m_pBtnEnsureAdd, &QPushButton::clicked, this, &ItemWgt::slotOnBtnEnsurePressed);
}

void ItemWgt::slotOnBtnClosePressed()
{
    close();
}

void ItemWgt::slotOnBtnEnsurePressed()
{
    QVariantMap data = getData();
    emit sgAddNewItem(data);
    close();
}


#ifndef ITEMWGT_H
#define ITEMWGT_H

#include <QWidget>
#include <QVariantMap>
#include <QDebug>
#include "ui_itemwgt.h"

class ItemWgt : public QWidget, public Ui_ItemWgt
{
    Q_OBJECT

public:
    explicit ItemWgt(QWidget *parent = nullptr);
    ~ItemWgt();
    void setUuid(QString uuid);
    void updateWgt();

    QVariantMap getData();
    void setData(QVariantMap data);
protected:
    void init();
    void connectSignalAndSlots();
protected slots:
    void slotOnBtnClosePressed();
    void slotOnBtnEnsurePressed();
signals:
    void sgAddNewItem(QVariantMap data);
private:
    QString m_uuid;
};

#endif // ITEMWGT_H

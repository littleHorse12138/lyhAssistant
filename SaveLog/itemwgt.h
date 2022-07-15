#ifndef ITEMWGT_H
#define ITEMWGT_H

#include <QWidget>
#include <QVariantMap>
#include <QDebug>
#include "PublicFunctions/otherfunctions.h"
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
    void slotOnBtnEndPressed();

    void slotOnOpenWebPressed();
signals:
    void sgAddNewItem(QVariantMap data);
    void sgDeleteItem(QVariantMap data);
private:
    QString m_uuid;
};

#endif // ITEMWGT_H

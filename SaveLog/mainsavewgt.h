#ifndef MAINSAVEWGT_H
#define MAINSAVEWGT_H

#include <QDebug>
#include <QWidget>
#include <QTimer>
#include <QVariant>
#include "PublicFunctions/filefunctions.h"
#include "PublicFunctions/stringfunctions.h"
#include "PublicFunctions/otherfunctions.h"
#include "PublicFunctions/globaldefine.h"
#include "ui_mainsavewgt.h"
#include "itemwgt.h"
class MainSaveWgt : public QWidget, public Ui_MainSaveWgt
{
    Q_OBJECT

public:
    explicit MainSaveWgt(QWidget *parent = nullptr);
    ~MainSaveWgt();

    void readDefaultData();
protected:
    void init();
    void connectSignalAndSlots();
    void openItemWidget(QVariantMap data = QVariantMap());

    QVariantMap getNewData(); //为某一item增加data
    QVariantMap getData();
    void setData(QVariantMap data);

    void autoSaveData();
    bool saveData(QVariantMap data, QString path, bool isAuto = false);
    QVariantMap readData(QString filePath);
    void closeEvent(QCloseEvent *event);
    void hideEvent(QHideEvent *event);
    static bool cmp(QVariantMap a, QVariantMap b);
    void sortItems();
protected slots:
    void slotOnBtnAddItemPressed();
    void slotOnBtnSaveAllPressed();
    void slotOnAddNewItem(QVariantMap data);
    void slotOnDeleteItem(QVariantMap data);
    void slotOnCheckItem();
    void slotOnBtnExportPressed();
    void slotOnBtnImportPressed();
    void slotOnSaveTimeout();
    void slotOnOpenConfigWgt();
    void updateWgt();
private:
    ItemWgt *m_itemWgt = nullptr;
    QList <QVariantMap> m_items;
    QList <QPushButton*> m_buttons;

    QString m_defaultSavePath = "";
    QTimer *m_pSaveTimer;
};

#endif // MAINSAVEWGT_H

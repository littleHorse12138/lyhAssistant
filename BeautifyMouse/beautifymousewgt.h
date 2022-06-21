#ifndef BEAUTIFYMOUSEWGT_H
#define BEAUTIFYMOUSEWGT_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QDebug>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QCursor>
#include "PublicFunctions/filefunctions.h"
#include "ui_beautifymousewgt.h"
#include "configwgt.h"
class BeautifyMouseWgt : public QWidget, public Ui_BeautifyMouseWgt
{
    Q_OBJECT

public:
    explicit BeautifyMouseWgt(QWidget *parent = nullptr);
    ~BeautifyMouseWgt();

protected:
    void init();
    void connectSignalAndSlots();
    void replaceMentMouse();

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
protected slots:
    void onBtnEnsurePressed();
    void onBtnClosePressed();
    void onBtnChoosePressed();
    void onBtnOpenConfigPressed();
private:
    QString m_curPicPath = "";
    QString m_cachePath  = "";

    ConfigWgt* m_pConfigWgt = nullptr;
};

#endif // BEAUTIFYMOUSEWGT_H

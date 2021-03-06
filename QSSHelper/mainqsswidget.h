#ifndef MAINQSSWIDGET_H
#define MAINQSSWIDGET_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QUrl>
#include "PublicFunctions/filefunctions.h"
#include "ui_mainqsswidget.h"
class MainQssWidget : public QWidget, public Ui_MainQssWidget
{
    Q_OBJECT

public:
    explicit MainQssWidget(QWidget *parent = nullptr);
    ~MainQssWidget();

    QVariantMap generateSave();
    void applySave(QVariantMap save);
protected:
    void init();
    void connectSignalAndSlots();
    void regenerateQSS();          //更新qss语句
    void updatePreviewControl();   //更显预览文件状态

    void resetWgtState();
    void updateWgtState();     //更新界面控件显隐

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
protected slots:
    void onBtnStatePressed();
    void onBtnBorderPressed();
    void onBtnBackgroundPresseed();
    void onBtnFontPressed();
    void onBtnTypePressed();
    void onBtnPreViewPressed();
    void onBtnClosePressed();
    void onBtnImportPressed();
    void onCBTypeIndexChanged(QString text);
    void onCBIsBGColorToggled();
    void onCBIsBGPicToggled();

    QString getStart();
    QString getEnd();

    QString getType();
    QString getState();
    QString getBackground();
    QString getBorder();
    QString getFont();
public slots:
    void updateAll();
private:
    bool m_bIsType = false;
    int m_type;

    bool m_bIsState = false;
    int m_state;

    bool m_bIsBorder = false;
    QColor m_borderColor;

    bool m_bIsBackgroundColor = false;
    bool m_bIsBackgroundPic   = false;
    QString m_backgroundPicPath = "";
    QColor m_backgroundColor;

    QString m_qss;
};

#endif // MAINQSSWIDGET_H

#ifndef MAIN3DENGINEWIDGET_H
#define MAIN3DENGINEWIDGET_H

#include <QWidget>
#include "ui_main3denginewidget.h"
#include "openglconfigwgt.h"
#include "addmodelwidget.h"
#include "PublicFunctions/mouseandkeymanager.h"
class Main3DEngineWidget : public QWidget, public Ui_Main3DEngineWidget
{
    Q_OBJECT

public:
    explicit Main3DEngineWidget(QWidget *parent = nullptr);
    ~Main3DEngineWidget();
protected:
    void init();
    void connectSignalAndSlots();

    void keyPressEvent(QKeyEvent *ev) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
protected slots:
    void slotOnBtnConfigPressed();
    void slotOnBtnAddModelPressed();
    void slotOnBtnExitPressed();


private:
    AddModelWidget* m_pAddModelWgt;

    QPoint m_lastMosPos;
};

#endif // MAIN3DENGINEWIDGET_H

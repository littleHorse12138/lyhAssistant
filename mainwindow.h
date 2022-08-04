#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QSystemTrayIcon>
#include "ui_mainwindow.h"
#include "ReadLocalConfiguration/readlocalconfigurationwgt.h"
#include "BeautifyMouse/beautifymousewgt.h"
#include "sudoku/sudokumainwgt.h"
#include "QSSHelper/mainqsswidget.h"
#include "SaveLog/mainsavewgt.h"
#include "UsefulFunction/mainfuncwgt.h"
#include "3DEngine/main3denginewidget.h"
class MainWindow : public QMainWindow, public Ui_MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void init();
    void connectSignalAndSlots();

    void closeEvent(QCloseEvent *event);
protected slots:
    void checkComputerConfiguration();
    void onBtnBeautifualMousePressed();
    void onBtnPlaySudoku();
    void onBtnQSSHelperOpen();
    void onBtnSavePressed();
    void onBtnMainFuncPressed();
    void onBtn3DEnginePressed();
private:
    ReadLocalConfigurationWgt* m_pReadConfigWgt = nullptr;
    BeautifyMouseWgt *m_pBeautifyMouseWgt       = nullptr;
    SudokuMainWgt *m_pSudokuWgt                 = nullptr;
    MainQssWidget *m_pQSSWidget                 = nullptr;
    MainSaveWgt *m_pMainSaveWgt                 = nullptr;
    MainFuncWgt *m_pMainFuncWgt                 = nullptr;
    QSystemTrayIcon* m_trayIcon                 = nullptr;
    Main3DEngineWidget *m_p3DEngineWgt          = nullptr;
};
#endif // MAINWINDOW_H

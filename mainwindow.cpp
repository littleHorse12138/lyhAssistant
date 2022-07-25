#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    if(m_pReadConfigWgt){
        delete m_pReadConfigWgt;
    }
    if(m_pBeautifyMouseWgt){
        delete m_pBeautifyMouseWgt;
    }
}

void MainWindow::init()
{
    connectSignalAndSlots();
    setWindowIcon(QIcon(":/logo.ico"));
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(QIcon(":/logo.ico"));
    //trayIcon->setToolTip(QStringLiteral("测试"));
    m_trayIcon->show();
}

void MainWindow::connectSignalAndSlots()
{
    connect(m_pBtnCheckConfig, &QPushButton::clicked, this, &MainWindow::checkComputerConfiguration);
    connect(m_pBtnBeautifyMouse, &QPushButton::clicked, this, &MainWindow::onBtnBeautifualMousePressed);
    connect(m_pBtnOpenSudoku, &QPushButton::clicked, this, &MainWindow::onBtnPlaySudoku);
    connect(m_pBtnQSSHelper, &QPushButton::clicked, this, &MainWindow::onBtnQSSHelperOpen);
    connect(m_pBtnAddSave, &QPushButton::clicked, this, &MainWindow::onBtnSavePressed);
    connect(m_pBtnFuncs, &QPushButton::clicked, this, &MainWindow::onBtnMainFuncPressed);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_trayIcon->isVisible())
    {
        hide(); //隐藏窗口
      //  event->ignore(); //忽略事件
    }
}

void MainWindow::checkComputerConfiguration()
{
    if(!m_pReadConfigWgt){
        m_pReadConfigWgt = new ReadLocalConfigurationWgt;
    }
    m_pReadConfigWgt->show();
}

void MainWindow::onBtnBeautifualMousePressed()
{
    if(!m_pBeautifyMouseWgt){
        m_pBeautifyMouseWgt = new BeautifyMouseWgt;
    }
    m_pBeautifyMouseWgt->show();
}

void MainWindow::onBtnPlaySudoku()
{
    if(!m_pSudokuWgt){
        m_pSudokuWgt = new SudokuMainWgt;
    }
    m_pSudokuWgt->show();
}

void MainWindow::onBtnQSSHelperOpen()
{
    if(!m_pQSSWidget){
        m_pQSSWidget = new MainQssWidget;
    }
    m_pQSSWidget->show();
}

void MainWindow::onBtnSavePressed()
{
    if(!m_pMainSaveWgt){
        m_pMainSaveWgt = new MainSaveWgt;
    }
    m_pMainSaveWgt->readDefaultData();
    m_pMainSaveWgt->show();
}

void MainWindow::onBtnMainFuncPressed()
{
    if(!m_pMainFuncWgt){
        m_pMainFuncWgt = new MainFuncWgt;
    }
    m_pMainFuncWgt->show();
}


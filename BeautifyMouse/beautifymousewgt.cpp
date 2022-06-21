#include "beautifymousewgt.h"

BeautifyMouseWgt::BeautifyMouseWgt(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    init();
}

BeautifyMouseWgt::~BeautifyMouseWgt()
{
    if(m_pConfigWgt){
        delete m_pConfigWgt;
    }
}

void BeautifyMouseWgt::init()
{
    m_cachePath = FileFunctions::getExePath();
    m_cachePath += "/Cache/mouse";
    if(!FileFunctions::isDirExist(m_cachePath)){
        FileFunctions::createDir(m_cachePath);
    }
    setAcceptDrops(true);
    connectSignalAndSlots();
}

void BeautifyMouseWgt::connectSignalAndSlots()
{
    connect(m_pBtnEnsure    , &QPushButton::clicked, this, &BeautifyMouseWgt::onBtnEnsurePressed);
    connect(m_pBtnChoosePic , &QPushButton::clicked, this, &BeautifyMouseWgt::onBtnChoosePressed);
    connect(m_pBtnClose     , &QPushButton::clicked, this, &BeautifyMouseWgt::onBtnClosePressed);
    connect(m_pBtnOpenConfig, &QPushButton::clicked, this, &BeautifyMouseWgt::onBtnOpenConfigPressed);
}

void BeautifyMouseWgt::replaceMentMouse()
{
   /* if(!FileFunctions::isFileExist(m_curPicPath)){
        return;
    }
    QString cachePath = m_cachePath;
    cachePath += m_curPicPath.split('.').last();
    if(!FileFunctions::copyFile(m_curPicPath, cachePath)){
        return;
    }*/
    QPixmap pic(m_curPicPath);
    QCursor cursor = QCursor(pic);
    setCursor(cursor);
}

void BeautifyMouseWgt::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()){
        event->acceptProposedAction();
    }else{
        event->ignore();
    }
}

void BeautifyMouseWgt::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasUrls()){
        m_curPicPath = event->mimeData()->urls().first().url();
        m_curPicPath.remove(0, 8);
        m_pLabPreView->setPic(m_curPicPath);
    }
}

void BeautifyMouseWgt::onBtnEnsurePressed()
{
    replaceMentMouse();
}

void BeautifyMouseWgt::onBtnClosePressed()
{
    this->close();
}

void BeautifyMouseWgt::onBtnChoosePressed()
{
    FileFunctions::getFileName();
}

void BeautifyMouseWgt::onBtnOpenConfigPressed()
{
    if(!m_pConfigWgt){
        m_pConfigWgt = new ConfigWgt;
    }
    m_pConfigWgt->show();
}


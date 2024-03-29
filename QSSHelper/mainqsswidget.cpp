#include "mainqsswidget.h"

MainQssWidget::MainQssWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    init();
}

MainQssWidget::~MainQssWidget()
{

}

QVariantMap MainQssWidget::generateSave()
{
    QVariantMap save;
    return save;
}

void MainQssWidget::applySave(QVariantMap save)
{

}

void MainQssWidget::init()
{
    setAcceptDrops(true);
    m_pTEQSS->setAcceptDrops(false);
    m_pTEQSS->setReadOnly(true);
    m_pCBType->addItem("QPushButton");
    m_pCBType->addItem("QLabel");
    m_pCBType->addItem("QLineEdit");
    m_pCBType->addItem("custom");

    m_pCBState->addItem("empty");
    m_pCBState->addItem("normal");
    m_pCBState->addItem("hover");
    m_pCBState->addItem("pressed");
    m_pCBState->addItem("disable");

    m_bCBBorderType->addItem("solid");

    resetWgtState();
    connectSignalAndSlots();
    
    m_pSBBorderWidth->setValue(1);
    updateAll();
}

void MainQssWidget::connectSignalAndSlots()
{
    connect(m_pBtnType            , &QPushButton::clicked         , this, &MainQssWidget::onBtnTypePressed);
    connect(m_pBtnState           , &QPushButton::clicked         , this, &MainQssWidget::onBtnStatePressed);
    connect(m_pBtnBackground      , &QPushButton::clicked         , this, &MainQssWidget::onBtnBackgroundPresseed);
    connect(m_pBtnPreview         , &QPushButton::clicked         , this, &MainQssWidget::onBtnPreViewPressed);
    connect(m_pBtnClose           , &QPushButton::clicked         , this, &MainQssWidget::onBtnClosePressed);
    connect(m_pBtnFont            , &QPushButton::clicked         , this, &MainQssWidget::onBtnFontPressed);
    connect(m_pBtnUpdate          , &QPushButton::clicked         , this, &MainQssWidget::updateAll);
    connect(m_pLECustomType       , &QLineEdit::textChanged       , this, &MainQssWidget::updateAll);
    connect(m_pLEPicPath          , &QLineEdit::textChanged       , this, &MainQssWidget::updateAll);
    connect(m_pCBState            , &QComboBox::currentTextChanged, this, &MainQssWidget::updateAll);
    connect(m_pCBType             , &QComboBox::currentTextChanged, this, &MainQssWidget::onCBTypeIndexChanged);
    connect(m_pCBIsBackgroundColor, &QCheckBox::clicked           , this, &MainQssWidget::onCBIsBGColorToggled);
    connect(m_pCBIsBackgroundPic  , &QCheckBox::clicked           , this, &MainQssWidget::onCBIsBGPicToggled);
    connect(m_pCheckBoxDQM        , &QCheckBox::clicked           , this, &MainQssWidget::updateAll);
    connect(m_pCBIsShowBorder     , &QCheckBox::clicked           , this, &MainQssWidget::updateAll);

    //边框
    connect(m_pBtnBorder          , &QPushButton::clicked         , this, &MainQssWidget::onBtnBorderPressed);
    connect(m_pLEBorderR          , &QLineEdit::textChanged       , this, &MainQssWidget::updateAll);
    connect(m_pLEBorderB          , &QLineEdit::textChanged       , this, &MainQssWidget::updateAll);
    connect(m_pLEBorderG          , &QLineEdit::textChanged       , this, &MainQssWidget::updateAll);
    connect(m_bCBBorderType       , &QComboBox::currentTextChanged, this, &MainQssWidget::updateAll);
    connect(m_pSBBorderWidth      , &QSpinBox::editingFinished    , this, &MainQssWidget::updateAll);

    //字体
    connect(m_pCBIsFont           , &QCheckBox::clicked           , this, &MainQssWidget::updateAll);
    connect(m_pLEFontR            , &QLineEdit::textChanged       , this, &MainQssWidget::updateAll);
    connect(m_pLEFontB            , &QLineEdit::textChanged       , this, &MainQssWidget::updateAll);
    connect(m_pLEFontG            , &QLineEdit::textChanged       , this, &MainQssWidget::updateAll);
    connect(m_pSBFontSize         , &QSpinBox::editingFinished    , this, &MainQssWidget::updateAll);

    //导入
    connect(m_pBtnImport          , &QPushButton::clicked         , this, &MainQssWidget::onBtnImportPressed);
}

void MainQssWidget::regenerateQSS()
{
    QString text = "";
    text += getType();
    text += getState();
    text += getStart();
    text += getBackground();
    text += getBorder();
    text += getFont();
    text += getEnd();
    m_qss = text;
    if(m_pCheckBoxDQM->isChecked()){
        QStringList textList = text.split("\n");
        text = "\"";
        for(int i = 0; i < textList.count(); i++){
            text += textList[i];
            text += "\"\n\"";
        }
        text.remove(text.count() - 1, 1);
    }
    m_pTEQSS->setText(text);
}

void MainQssWidget::updatePreviewControl()
{
    if(m_pCBType->currentText() == "QPushButton"){
        m_pPreviewStackWgt->setCurrentIndex(0);
        m_pPreviewBtn->setStyleSheet(m_qss);
    }
}

void MainQssWidget::updateAll()
{
    updateWgtState();
    regenerateQSS();
    updatePreviewControl();
}

void MainQssWidget::resetWgtState()
{
    m_pLECustomType->setVisible(false);

    m_pWgtBackgroundColor->setVisible(false);
    m_pWgtBackgroundPic->setVisible(false);
    m_pCBIsBackgroundColor->setChecked(false);
    m_pCBIsBackgroundPic->setChecked(false);

    //预览
    m_pLabPreviewError->setVisible(false);
    m_pPreviewStackWgt->setVisible(false);

    //边框
    m_pWgtBorderConfig->setVisible(false);

    //字体
    m_pWgtFont->setVisible(false);
}

void MainQssWidget::updateWgtState()
{
    resetWgtState();
    if(m_pCBType->currentText() == QStringLiteral("custom")){
        m_pLECustomType->setVisible(true);
    }

    //背景
    if(m_bIsBackgroundColor){
        m_pWgtBackgroundColor->setVisible(true);
        m_pCBIsBackgroundColor->setChecked(true);
    }
    if(m_bIsBackgroundPic){
        m_pWgtBackgroundPic->setVisible(true);
        m_pCBIsBackgroundPic->setChecked(true);
    }

    //预览
    if(m_pCBType->currentText() == "custom"){
        m_pLabPreviewError->setVisible(true);
    }else{
        m_pPreviewStackWgt->setVisible(true);
    }

    //边框
    if(m_pCBIsShowBorder->isChecked()){
        m_pWgtBorderConfig->setVisible(true);
    }

    //字体
    if(m_pCBIsFont->isChecked()){
        m_pWgtFont->setVisible(true);
    }
}

void MainQssWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls()){
        event->acceptProposedAction();
    }else{
        event->ignore();
    }
}

void MainQssWidget::dropEvent(QDropEvent *event)
{
    m_backgroundPicPath = event->mimeData()->urls()[0].path().remove(0,1);
    m_pLEPicPath->setText(m_backgroundPicPath);
    m_bIsBackgroundPic = true;
    updateAll();
}

void MainQssWidget::onBtnStatePressed()
{
    m_pMainStackedWgt->setCurrentIndex(1);
}

void MainQssWidget::onBtnBorderPressed()
{
    m_pMainStackedWgt->setCurrentIndex(2);
}

void MainQssWidget::onBtnBackgroundPresseed()
{
    m_pMainStackedWgt->setCurrentIndex(3);
}

void MainQssWidget::onBtnFontPressed()
{
    m_pMainStackedWgt->setCurrentIndex(5);
}

void MainQssWidget::onBtnTypePressed()
{
    m_pMainStackedWgt->setCurrentIndex(0);
}

void MainQssWidget::onBtnPreViewPressed()
{
    m_pMainStackedWgt->setCurrentIndex(4);
}

void MainQssWidget::onCBTypeIndexChanged(QString text)
{
    updateAll();
}

void MainQssWidget::onCBIsBGColorToggled()
{
    m_bIsBackgroundColor = m_pCBIsBackgroundColor->checkState() == Qt::Checked? true : false;
    updateAll();
}

void MainQssWidget::onCBIsBGPicToggled()
{
    m_bIsBackgroundPic = m_pCBIsBackgroundPic->checkState() == Qt::Checked? true : false;
    updateAll();
}

void MainQssWidget::onBtnClosePressed()
{
    close();
}

void MainQssWidget::onBtnImportPressed()
{
    QString pathNam = FileFunctions::getFileName();
}

QString MainQssWidget::getStart()
{
    return "{\n";
}

QString MainQssWidget::getEnd()
{
    return "}";
}

QString MainQssWidget::getType()
{
    QString temp = "";
    if(m_pCBType->currentText() == QStringLiteral("custom")){
        temp += m_pLECustomType->text();
    }else{
        temp += m_pCBType->currentText();
    }
    return temp;
}

QString MainQssWidget::getState()
{
    QString text = "";
    if(m_pCBState->currentText() == "empty"){
        return text;
    }else{
        text += ":";
        text += m_pCBState->currentText();
    }
    return text;
}

QString MainQssWidget::getBackground()
{
    QString text = "";
    if(m_bIsBackgroundColor){
        float r,g,b;
        r = m_pLEBackgroundRed->text().toFloat();
        g = m_pLEBackgroundGreen->text().toFloat();
        b = m_pLEBackgroundBlue->text().toFloat();
        text += "background-color:rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ");\n";
    }
    if(m_bIsBackgroundPic){
        text += "border-image:url(" + m_pLEPicPath->text() + ");\n";
    }
    return text;
}

QString MainQssWidget::getBorder()
{
    QString text = "";
    if(m_pCBIsShowBorder->isChecked()){
        text += "border:";
        text += QString::number(m_pSBBorderWidth->value()) + "px ";
        text += m_bCBBorderType->currentText() + " ";
        float r,g,b;
        r = m_pLEBorderR->text().toFloat();
        g = m_pLEBorderG->text().toFloat();
        b = m_pLEBorderB->text().toFloat();
        text += "rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ");\n";
    }
    return text;
}

QString MainQssWidget::getFont()
{
    QString text = "";
    if(m_pCBIsFont->isChecked()){
        text += "font:";
     //   text += QString::number(m_pSBFontSize->value()) + " pt ";
        float r,g,b;
        r = m_pLEFontR->text().toFloat();
        g = m_pLEFontG->text().toFloat();
        b = m_pLEFontB->text().toFloat();
        text += "rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ");\n";
    }
    return text;
}

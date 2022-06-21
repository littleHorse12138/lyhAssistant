#include "readlocalconfigurationwgt.h"

ReadLocalConfigurationWgt::ReadLocalConfigurationWgt(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    init();
}

ReadLocalConfigurationWgt::~ReadLocalConfigurationWgt()
{

}

void ReadLocalConfigurationWgt::init()
{
    setWindowTitle(QStringLiteral("本机配置"));
    getInfo();
    m_pLECPUName     ->setReadOnly(true);
    m_pLECPUCoreNum  ->setReadOnly(true);
    m_pLECPUThreadNum->setReadOnly(true);
    m_pLECPUThreadNum->setReadOnly(true);
}

void ReadLocalConfigurationWgt::getInfo()
{
    QString res1 = getProcessEnd("wmic cpu get name");  //cpu名称
    QString cpuName = StringFunctions::canonicalString(res1);
    cpuName = removeStringBeforeFirstSapce(cpuName);
    cpuName = StringFunctions::removeLastSpaces(cpuName);
    m_pLECPUName->setText(cpuName);

    QString res2 = getProcessEnd("wmic cpu get NumberOfCores");  //cpu核心数
    QString cpuCoreNum = StringFunctions::canonicalString(res2);
    cpuCoreNum = removeStringBeforeFirstSapce(cpuCoreNum);
    cpuCoreNum = StringFunctions::removeLastSpaces(cpuCoreNum);
    m_pLECPUCoreNum->setText(cpuCoreNum);

    QString res3 = getProcessEnd("wmic cpu get NumberOfLogicalProcessors");  //cpu线程数
    QString cpuThread = StringFunctions::canonicalString(res3);
    cpuThread = removeStringBeforeFirstSapce(cpuThread);
    cpuThread = StringFunctions::removeLastSpaces(cpuThread);
    m_pLECPUThreadNum->setText(cpuThread);

    QString res4 = getProcessEnd("wmic cpu get processorid");    //cpu序列号
    QString cpuSerial = StringFunctions::canonicalString(res4);
    cpuSerial = removeStringBeforeFirstSapce(cpuSerial);
    cpuSerial = StringFunctions::removeLastSpaces(cpuSerial);
    m_pLECPUSerialNum->setText(cpuSerial);
}

QString ReadLocalConfigurationWgt::removeStringBeforeFirstSapce(QString from)
{
    while(from[0] != ' '){
        from.remove(0, 1);
    }
    if(from.count() >= 1){
        from.remove(0, 1);
    }
    return from;
}

QString ReadLocalConfigurationWgt::getProcessEnd(QString str)
{
    QProcess p;
    p.start(str);
    p.waitForFinished();
    QString res = QString::fromLocal8Bit(p.readAllStandardOutput());
    return res;
}

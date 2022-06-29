#include "filefunctions.h"

FileFunctions::FileFunctions()
{
    init();
}

FileFunctions::~FileFunctions()
{
    /*if(FileFunctions::m_instance){
        delete FileFunctions::m_instance;
    }*/
}

bool FileFunctions::copyFile(QString from, QString to, bool isCover)
{
    if(isFileExist(from)){
        if(!isCover && isFileExist(to)){
            return false;
        }
        if(isFileExist(to)){
            removeFile(to);
        }
        return QFile::copy(from, to);
    }
    return false;
}

bool FileFunctions::isFileExist(QString filePath)
{
    QFileInfo fileInfo(filePath);
    if(fileInfo.isFile())
    {
        return true;
    }
    return false;
}

bool FileFunctions::isDirExist(QString dirPath)
{
    QDir dir(dirPath);
    if(dir.exists())
    {
      return true;
    }
    return false;
}

bool FileFunctions::createDir(QString dirPath)
{
    if(isDirExist(dirPath)){
        return false;
    }
    QDir dir(dirPath);
    return dir.mkdir(dirPath);
}

bool FileFunctions::createFile(QString filePath)
{
    if(FileFunctions::isFileExist(filePath)){
        return false;
    }
    QFile file(filePath);
    return file.open(QIODevice::ReadWrite|QIODevice::Text);
}

bool FileFunctions::removeFile(QString filePath)
{
    if(!isFileExist(filePath)){
        return false;
    }
    return QFile::remove(filePath);
}


void FileFunctions::setData(QString name, QVariant data)
{
    m_setings->setValue(name, data);
}

QVariant FileFunctions::getData(QString name)
{
    return m_setings->value(name);
}

bool FileFunctions::writeJson(QString jsonPath, QVariantMap data, bool isCreate)
{
    if(!FileFunctions::isFileExist(jsonPath)){
        if(!isCreate){
            return false;
        }else{
            if(!FileFunctions::createFile(jsonPath)){
                return false;
            }
        }
    }
    QJsonObject obj = FileFunctions::MapToJsonObject(data);
    QJsonDocument doc(obj);
    QByteArray data1=doc.toJson();
    QFile file(jsonPath);
    bool ok=file.open(QIODevice::WriteOnly);
    if(ok)
    {
        file.write(data1);
        file.close();
        return true;
    }
    return false;
}

QVariantMap FileFunctions::readJson(QString path)
{
    QVariantMap an;
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray data=file.readAll();
    file.close();
    QJsonDocument doc=QJsonDocument::fromJson(data);
    QJsonObject obj=doc.object();
    an = FileFunctions::JsonObjectToMap(obj);
    return an;
}

QVariantMap FileFunctions::JsonObjectToMap(QJsonObject from)
{
    return from.toVariantMap();
}

QJsonObject FileFunctions::MapToJsonObject(QVariantMap from)
{
    return QJsonObject(QJsonDocument::fromJson(QJsonDocument::fromVariant(QVariant(from)).toJson()).object());
}

void FileFunctions::init()
{
    m_setings = new QSettings("setting.ini",QSettings::IniFormat);
}

QString FileFunctions::getExePath()
{
    return QCoreApplication::applicationDirPath();
}

QString FileFunctions::getFileName()
{
    return QFileDialog::getOpenFileName(nullptr);
}

FileFunctions *FileFunctions::getInstance()
{
    static FileFunctions *instance = new FileFunctions;
    return instance;
}

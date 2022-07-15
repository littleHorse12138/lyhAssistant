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
    an = FileFunctions::jsonObjectToMap(obj);
    return an;
}

QVariantMap FileFunctions::jsonArrayToMap(QJsonArray array)
{
    QVariantList list = array.toVariantList();
    QVariantMap map;
    for(int i = 0; i < list.count(); i += 2){
        QString key = list[i].toString();
        map.insert(key, list[i+1]);
    }
    return map;
}

QJsonArray FileFunctions::mapToJsonArray(QVariantMap map)
{
    QVariantList QVarList;
    for(auto key:map.keys()){
        QVarList << key;
        QVarList << map[key];
    }
    QJsonArray jsonArray = QJsonArray::fromVariantList(QVarList);
    return jsonArray;
}

QVariantMap FileFunctions::jsonObjectToMap(QJsonObject from)
{
    QVariantMap map = from.toVariantMap();
    return map;
}

QJsonObject FileFunctions::MapToJsonObject(QVariantMap from)
{
   // return QJsonObject(QJsonDocument::fromJson(QJsonDocument::fromVariant(QVariant(from)).toJson()).object());
    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(from));
    QByteArray jba = doc.toJson();
    QString jsonString = QString(jba);
    QByteArray njba = jsonString.toUtf8();
    QJsonObject nobj = QJsonObject(QJsonDocument::fromJson(njba).object());
    return nobj;
}

QByteArray FileFunctions::jsonArrayToByteArray(QJsonArray from)
{
    QByteArray byte_array = QJsonDocument(from).toJson();
    return byte_array;
}

QJsonArray FileFunctions::byteArrayToJsonArray(QByteArray from)
{
     QJsonArray json_array2 = QJsonDocument::fromJson(from).array();
     return json_array2;
}

QVariantMap FileFunctions::listToMap(QVariantList list)
{
    QVariantMap map;
    for(int i = 0; i < list.count(); i+=2){
        map.insert(list[i].toString(), list[i+1]);
    }
    return map;
}

QVariantList FileFunctions::mapToList(QVariantMap map)
{
    QVariantList list;
    for(auto key: map.keys()){
        list.append(key);
        list.append(map[key]);
    }
    return list;
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

QString FileFunctions::getDirName()
{
    return QFileDialog::getExistingDirectory(nullptr, "choose path", "./");
}

FileFunctions *FileFunctions::getInstance()
{
    static FileFunctions *instance = new FileFunctions;
    return instance;
}

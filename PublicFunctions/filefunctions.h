#ifndef FILEFUNCTIONS_H
#define FILEFUNCTIONS_H

#include <QString>
#include <QDir>
#include <QFile>
#include <QCoreApplication>
#include <QFileDialog>
#include <QJsonArray>
#include <QSettings>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
class FileFunctions
{
public:
    FileFunctions();
    ~FileFunctions();
    static bool copyFile(QString from, QString to, bool isCover = true);                       //复制文件
    static bool isFileExist(QString filePath);                                                 //文件是否存在
    static bool isDirExist(QString dirPath);                                                   //文件夹是否存在
    static bool createDir(QString dirPath);                                                    //创建文件夹
    static bool createFile(QString filePath);                                                  //创建文件
    static bool removeFile(QString filePath);                                                  //删除文件
    static QString getExePath();                                                               //获取当前运行目录
    static QString getFileName();                                                              //打开一个选择文件的窗口
    static QString getDirName();                                                               //打开一个选择文件夹的窗口

    static FileFunctions* getInstance();
    void setData(QString name, QVariant data);                                                 //存读取文档
    QVariant getData(QString name);

    static bool writeJson(QString jsonPath, QVariantMap data, bool isCreate = false);
    static QVariantMap readJson(QString path);

    static QVariantMap jsonArrayToMap(QJsonArray array);
    static QJsonArray mapToJsonArray(QVariantMap map);

    static QVariantMap jsonObjectToMap(QJsonObject from);
    static QJsonObject MapToJsonObject(QVariantMap from);

    static QByteArray jsonArrayToByteArray(QJsonArray from);
    static QJsonArray byteArrayToJsonArray(QByteArray from);

    static QVariantMap listToMap(QVariantList list);
    static QVariantList mapToList(QVariantMap map);
protected:
    void init();
private:
    QSettings* m_setings;
};

#endif // FILEFUNCTIONS_H

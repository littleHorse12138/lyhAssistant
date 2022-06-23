#ifndef FILEFUNCTIONS_H
#define FILEFUNCTIONS_H

#include <QString>
#include <QDir>
#include <QFile>
#include <QCoreApplication>
#include <QFileDialog>
#include <QSettings>
#include <QJsonObject>
#include <QJsonDocument>
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
    static bool readJson(QString path, QVariantMap &data);                                     //loadjson
    static bool writeJson(QString path, QVariantMap &data, bool isCreate = false);             //writejson
    static QString getExePath();                                                               //获取当前运行目录
    static QString getFileName();                                                              //打开一个选择文件的窗口

    static FileFunctions* getInstance();
    void setData(QString name, QVariant data);                                                 //存读取文档
    QVariant getData(QString name);

    static QVariantMap JsonObjectToMap(QJsonObject from);
    static QJsonObject MapToJsonObject(QVariantMap from);
protected:
    void init();
private:
    QSettings* m_setings;
};

#endif // FILEFUNCTIONS_H

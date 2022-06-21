#ifndef FILEFUNCTIONS_H
#define FILEFUNCTIONS_H

#include <QString>
#include <QDir>
#include <QFile>
#include <QCoreApplication>
#include <QFileDialog>
#include <QSettings>
class FileFunctions
{
public:
    FileFunctions();
    ~FileFunctions();
    static bool copyFile(QString from, QString to, bool isCover = true);//复制文件
    static bool isFileExist(QString filePath);                          //文件是否存在
    static bool isDirExist(QString dirPath);                            //文件夹是否存在
    static bool createDir(QString dirPath);                             //创建文件夹
    static bool removeFile(QString filePath);                           //删除文件
    static QString getExePath();                                        //获取当前运行目录
    static QString getFileName();

    static FileFunctions* getInstance();
    void setData(QString name, QVariant data);                          //存读取文档
    QVariant getData(QString name);
protected:
    void init();
private:
    QSettings* m_setings;
};

#endif // FILEFUNCTIONS_H

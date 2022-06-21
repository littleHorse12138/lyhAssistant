#ifndef STRINGFUNCTIONS_H
#define STRINGFUNCTIONS_H
#include <QString>
#include <QDebug>
class StringFunctions
{
public:
    StringFunctions();
    static QString canonicalString(QString from); //格式化字符串，所有的/n /r变为空格且连着的空格变为一个
    static QString removeLastSpaces(QString from); //去掉字符串最后的所有空格
};

#endif // STRINGFUNCTIONS_H

#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include <QObject>

class ErrorManager : public QObject
{
    Q_OBJECT
public:
    explicit ErrorManager(QObject *parent = nullptr);

signals:

};

#endif // ERRORMANAGER_H

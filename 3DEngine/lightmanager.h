#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include <QObject>
#include "light.h"
class LightManager : public QObject
{
    Q_OBJECT
public:
    explicit LightManager(QObject *parent = nullptr);
    LightManager* getInstance();
private:
    QVector <Light*> m_lights;
    QVector <Light*> m_dirLights;
    QVector <Light*> m_spotLights;
    QVector <Light*> m_pointLights;
signals:

};

#endif // LIGHTMANAGER_H

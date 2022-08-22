#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include <QObject>
#include <QVector3D>
#include "light.h"
class LightManager : public QObject
{
    Q_OBJECT
public:
    explicit LightManager(QObject *parent = nullptr);
    static LightManager* getInstance();

    bool getIsUseLight();                         //是否打开灯光
    void setIsUseLight(bool isUseLight);

    void setIsLightChanged(bool isLightChanged);  //是否需要重新设置灯光着色器
private:
    QVector <Light*> m_lights;
    QVector <Light*> m_dirLights;
    QVector <Light*> m_spotLights;
    QVector <Light*> m_pointLights;

    bool m_bIsUseLight = false;
    bool m_bIsLightChanged = false; //为true时需要重新设置light
signals:

};

#endif // LIGHTMANAGER_H

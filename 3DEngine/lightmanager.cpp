#include "lightmanager.h"

LightManager::LightManager(QObject *parent) : QObject(parent)
{

}

LightManager *LightManager::getInstance()
{
    static LightManager* instance = nullptr;
    if(!instance){
        instance = new LightManager;
    }
    return instance;
}

bool LightManager::getIsUseLight()
{
    return getInstance()->m_bIsUseLight;
}

void LightManager::setIsUseLight(bool isUseLight)
{
    m_bIsUseLight = isUseLight;
}

void LightManager::setIsLightChanged(bool isLightChanged)
{
    m_bIsLightChanged = isLightChanged;
}

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

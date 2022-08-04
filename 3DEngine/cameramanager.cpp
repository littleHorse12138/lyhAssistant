#include "cameramanager.h"

CameraManager::CameraManager(QObject *parent) : QObject(parent)
{
    init();
}

Camera *CameraManager::getCurCamera()
{
    return m_pCurCamera;
}

void CameraManager::init()
{
    Camera* camera = new Camera;
    m_pCurCamera = camera;
    m_cameras.append(camera);
}

CameraManager *CameraManager::getInstance()
{
    static CameraManager* instance = nullptr;
    if(!instance){
        instance = new CameraManager;
    }
    return instance;
}

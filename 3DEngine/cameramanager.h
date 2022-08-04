#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QObject>
#include "camera.h"
class CameraManager : public QObject
{
    Q_OBJECT
public:
    explicit CameraManager(QObject *parent = nullptr);
    static CameraManager* getInstance();

    Camera *getCurCamera();
signals:
protected:
    void init();
private:
    Camera* m_pCurCamera = nullptr;
    QList <Camera*> m_cameras;
};

#endif // CAMERAMANAGER_H

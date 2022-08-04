#include "camera.h"

Camera::Camera(QObject *parent) : QObject(parent)
{
    init();
}

QMatrix4x4 Camera::getViewMat()
{
    return m_cameraView;
}

QMatrix4x4 Camera::getPerspectiveMat(double width, double height)
{
    QMatrix4x4 perspective;
    perspective.perspective(m_perspectiveAngle, width / height, m_nearPoint, m_farPoint);
    return perspective;
}

QVector3D Camera::getCameraPos()
{
    return m_cameraPos;
}

QVector3D Camera::getCameraDir()
{
    return m_cameraDir;
}

QVector3D Camera::getCameraRight()
{
    return m_cameraRight;
}

QVector3D Camera::getCameraUp()
{
    return m_cameraUp;
}

QVector3D Camera::getCameraTar()
{
    return m_cameraTar;
}

void Camera::setCameraPos(QVector3D cameraPos)
{
    m_cameraPos = cameraPos;
}

void Camera::setCameraTar(QVector3D cameraTar)
{
    m_cameraTar = cameraTar;
}

void Camera::init()
{
    updateData();
}

void Camera::updateData()
{
    m_cameraTar = QVector3D(0, 0, -10);
    m_cameraTar = m_bodyQuat *  m_cameraTar;
    m_cameraTar += m_cameraPos;
    QVector3D worldUp = m_headQuat * m_worldUp;
    m_cameraDir = (m_cameraPos - m_cameraTar).normalized();
    m_cameraRight = (m_worldUp.crossProduct(worldUp, m_cameraDir)).normalized();
    m_cameraUp = (worldUp.crossProduct(m_cameraDir, m_cameraRight)).normalized();
    m_cameraView = QMatrix4x4();
    m_cameraView.lookAt(m_cameraPos, m_cameraTar, m_cameraUp);
}

void Camera::wheelMoveFront()
{
    m_cameraPos -= m_cameraDir.normalized() * m_wheelSpeed;
    updateData();
}

void Camera::wheelMoveBack()
{
    m_cameraPos += m_cameraDir.normalized() * m_wheelSpeed;
    updateData();
}

void Camera::moveFront()
{
    m_cameraPos -= m_cameraDir.normalized() * m_moveSpeed;
    updateData();
}

void Camera::moveBack()
{
    m_cameraPos += m_cameraDir.normalized() * m_moveSpeed;
    updateData();
}

void Camera::moveLeft()
{
    m_cameraPos -= m_cameraRight.normalized() * m_moveSpeed;
    updateData();
}

void Camera::moveRight()
{
    m_cameraPos += m_cameraRight.normalized() * m_moveSpeed;
    updateData();
}

void Camera::moveUp()
{
    m_cameraPos += m_cameraUp.normalized() * m_moveSpeed;
    updateData();
}

void Camera::moveDown()
{
    m_cameraPos -= m_cameraUp.normalized() * m_moveSpeed;
    updateData();
}

void Camera::partialHeadLeft()
{
    QVector3D angles = m_headQuat.toEulerAngles();
    float x, y, z;
    x = angles.x();
    y = angles.y();
    z = angles.z();
    z += m_moveSpeed;
    m_headQuat = QQuaternion::fromEulerAngles(x, y, z);
    updateData();
}

void Camera::partialHeadRight()
{
    QVector3D angles = m_headQuat.toEulerAngles();
    float x, y, z;
    x = angles.x();
    y = angles.y();
    z = angles.z();
    z -= m_moveSpeed;
    m_headQuat = QQuaternion::fromEulerAngles(x, y, z);
    updateData();
}

void Camera::swivel(float screenX, float screenY)
{
    float x,y,z;
    QVector3D dir;
    dir = m_bodyQuat.toEulerAngles();
    x = dir.x();
    y = dir.y();
    z = dir.z();

    y -= screenX * m_rotSpeed;
    x -= screenY * m_rotSpeed;

    m_bodyQuat = QQuaternion::fromEulerAngles(x, y, z);
    updateData();
}

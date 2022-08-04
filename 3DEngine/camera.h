#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QMatrix4x4>
#include <QQuaternion>
class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = nullptr);
    QMatrix4x4 getViewMat();  //获取view矩阵
    QMatrix4x4 getPerspectiveMat(double width, double height); //获取透视矩阵
    QVector3D getCameraPos();
    QVector3D getCameraDir();
    QVector3D getCameraRight();
    QVector3D getCameraUp();
    QVector3D getCameraTar();

    void setCameraPos(QVector3D cameraPos);
    void setCameraTar(QVector3D cameraTar);
    void updateData();

    void wheelMoveFront();
    void wheelMoveBack();

    void moveFront();
    void moveBack();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void partialHeadLeft();
    void partialHeadRight();

    void swivel(float screenX, float screenY);
protected:
    void init();
private:
    QMatrix4x4 m_cameraView;   //摄像机矩阵

    QVector3D m_cameraPos = QVector3D(0.0f, 0.0f, 10.0f);  //摄像机位置
    QVector3D m_cameraTar = QVector3D(0.0f, 0.0f, 0.0f);   //摄像机朝点
    QVector3D m_cameraUp;                                  //摄像机上方
    QVector3D m_cameraRight;                               //摄像机右方
    QVector3D m_cameraDir = QVector3D(0.0f, 0.0f, 0.0f);   //摄像机朝向
    QVector3D m_worldUp   = QVector3D(0.0f, 1.0f, 0.0f);   //世界坐标上方

    float m_perspectiveAngle = 45.0;  //透视角
    float m_nearPoint = 0.1f;
    float m_farPoint  = 1000.0f;

    float m_moveSpeed = 0.3;
    float m_wheelSpeed = 1.3;
    float m_rotSpeed = 1.0;

    float m_seeDis = 10;//聚焦距离坐标的距离
    QQuaternion m_headQuat;
    QQuaternion m_bodyQuat;
signals:

};

#endif // CAMERA_H

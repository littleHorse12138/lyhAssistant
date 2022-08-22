#ifndef LIGHT_H
#define LIGHT_H

#include <QObject>
#include <QVector3D>
class Light : public QObject
{
    Q_OBJECT
public:
    explicit Light(QObject *parent = nullptr);
    enum LightType{
        Dir,
        Spot,
        Point
    };

private:
    QVector3D m_lightPos;
    QVector3D m_lightDir;

    //通用
    QVector3D m_lightColor = QVector3D(1.0f,  1.0f, 1.0f);
    QVector3D m_lightPos   = QVector3D(0.0f,  30.0f, 0.0f);
    QVector3D m_lightDir   = QVector3D(0.0f,  -3.0f, 0.0f);
    int m_type = FLAG_LIGHT_TYPE_POINT;

    float m_ambientStrength  = 0.1;
    float m_specularStrength = 0.7;
    float m_diffuseStrength  = 0.7;
    float m_lightStrength    = 1.0;

    QVector3D m_ambient  = QVector3D(1.0f, 1.0f, 1.0f);
    QVector3D m_specular = QVector3D(1.0f, 1.0f, 1.0f);
    QVector3D m_diffuse  = QVector3D(1.0f, 1.0f, 1.0f);


    float m_constant  = 1.0f;                                    //˥��
    float m_linear    = 0.007f;
    float m_quadratic = 0.0002f;

    float m_innerCutAngle = 12.5f;                                //���ӽǶȣ���spot����
    float m_outerCutAngle = 15.5f;
signals:

};

#endif // LIGHT_H

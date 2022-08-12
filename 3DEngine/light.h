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
signals:

};

#endif // LIGHT_H

#ifndef LYHMODEL_H
#define LYHMODEL_H

#include <QObject>
#include <QColor>
#include <QMatrix4x4>
#include <QVector2D>
#include <QOpenGLFunctions>
//#include <gl/GL.h>
class LyhModel : public QObject
{
    Q_OBJECT
public:
    explicit LyhModel(QObject *parent = nullptr);
    void calNormals(); //计算向量
    void generateData(); //生成顶点列
    void setPoints(QVector <QVector3D> points);
    void setIndicee(QVector <int> indices);
    void setTextures(QVector <QVector2D> textures);
    void setType(GLenum type);                    //要显示出一个模型，以上三个必须设置
    bool getIsShow();
    bool getIsLight();

    int getPointCount();
    int getIndicesCount();

    GLenum getModelType();
    QMatrix4x4 getModelMat();

    QVector <float> getModelData();

    QVector3D getMaterialAmbient();
    QVector3D getMaterialDiffuse();
    QVector3D getMaterialSpecluar();
    float getMaterialShininess();
protected:
    QVector3D getPoint  (int index);
    QVector3D getColor  (int index);
    QVector3D getNormal (int index);
    QVector2D getTexture(int index);
signals:
private:
    int m_id;
    QString m_name = "default";

    QVector <float> m_data;
    QVector <QVector3D> m_points;
    QVector <QVector3D> m_normals;
    QVector <int> m_indices;
    QVector <QVector3D> m_colors;
    QVector <QVector2D> m_textures;
    GLenum m_modelType;

    QMatrix4x4 m_modelMat;

    bool m_bIsLight = true;
    bool m_bIsShow  = true;

    QVector3D m_defaultPoint   = QVector3D(0 ,0 ,0);
    QVector3D m_defaultColor   = QVector3D(0, 255, 0);
    QVector3D m_defaultNormal  = QVector3D(0 ,0 ,0);
    QVector2D m_defaultTexture = QVector2D(0 ,0);

    QVector3D m_materialAmbient  = QVector3D(1, 1, 1);
    QVector3D m_materialDiffuse  = QVector3D(1, 1, 1);
    QVector3D m_materialSpecluar = QVector3D(1, 1, 1);
    float m_materialShininess      = 1.0;
};

#endif // LYHMODEL_H

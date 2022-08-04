#include "lyhmodel.h"

LyhModel::LyhModel(QObject *parent) : QObject(parent)
{

}

void LyhModel::calNormals()
{
    m_normals.clear();
    int l = m_indices.count() / 3;
    for(int i = 0; i < l; i++){
        m_normals << QVector3D(0, 0, 0);
    }
    for(int i = 0; i < l; i++){
        QVector3D p1,p2,p3;
        p1 = m_points[m_indices[i * 3 + 0]];
        p2 = m_points[m_indices[i * 3 + 1]];
        p3 = m_points[m_indices[i * 3 + 2]];

        QVector3D temp_v1, temp_v2;
        temp_v1 = p1 - p2;
        temp_v2 = p2 - p3;
        QVector3D vNormal = temp_v2.crossProduct(temp_v1, temp_v2);
        vNormal.normalize();

        m_normals[m_indices[i * 3 + 0]] += vNormal;
        m_normals[m_indices[i * 3 + 1]] += vNormal;
        m_normals[m_indices[i * 3 + 2]] += vNormal;
    }
}

void LyhModel::generateData()
{
    m_data.clear();
    for(int i = 0; i < m_indices.count(); i++){
        QVector3D point,normal,color;
        point  = getPoint (m_indices[i]);
        normal = getNormal(m_indices[i]);
        color  = getColor (m_indices[i]);
        QVector2D texture;
        texture = getTexture(i);
        m_data << point[0]  << point[1]  << point[2];
        m_data << normal[0] << normal[1] << normal[2];
        m_data << color[0]  << color[1]  << color[2];
        m_data << texture[0] << texture[1];
    }
}

void LyhModel::setPoints(QVector <QVector3D> points)
{
    m_points = points;
}

void LyhModel::setIndicee(QVector<int> indices)
{
    m_indices = indices;
}

void LyhModel::setTextures(QVector<QVector2D> textures)
{
    m_textures = textures;
}

void LyhModel::setType(GLenum type)
{
    m_modelType = type;
}

bool LyhModel::getIsShow()
{
    return m_bIsShow;
}

int LyhModel::getPointCount()
{
    return m_points.count();
}

int LyhModel::getIndicesCount()
{
    return m_indices.count();
}

GLenum LyhModel::getModelType()
{
    return m_modelType;
}

QMatrix4x4 LyhModel::getModelMat()
{
    return m_modelMat;
}

QVector<float> LyhModel::getModelData()
{
    return m_data;
}

QVector3D LyhModel::getPoint(int index)
{
    if(index >= m_points.count()){
        qDebug() << QStringLiteral("index比点数量多，模型或许有错误");
        return m_defaultPoint;
    }
    return m_points[index];
}

QVector3D LyhModel::getColor(int index)
{
    if(index >= m_colors.count()){
        return m_defaultColor;
    }
    return m_colors[index];
}

QVector3D LyhModel::getNormal(int index)
{
    if(index >= m_normals.count()){
        return m_defaultNormal;
    }
    return m_normals[index];
}

QVector2D LyhModel::getTexture(int index)
{
    if(index >= m_normals.count()){
        return m_defaultTexture;
    }
    return m_textures[index];
}


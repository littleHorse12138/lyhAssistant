#include "modelmanager.h"

ModelManager::ModelManager(QObject *parent) : QObject(parent)
{
    init();
}

ModelManager *ModelManager::getInstance()
{
    static ModelManager* instance = nullptr;
    if(!instance){
        instance = new ModelManager;
    }
    return instance;
}

void ModelManager::addCuboid(float l, float w, float h)
{
    LyhModel *cuboid = new LyhModel;
    float maxX,maxY,maxZ,minX,minY,minZ;
    GLenum modelType;
    QVector <QVector3D> vertices;
    QVector <int> indices;
    maxX = l / 2;
    maxY = h / 2;
    maxZ = w / 2;
    minX = maxX * -1;
    minY = maxY * -1;
    minZ = maxZ * -1;
    vertices << QVector3D(maxX, maxY, maxZ);
    vertices << QVector3D(maxX, maxY, minZ);
    vertices << QVector3D(maxX, minY, maxZ);
    vertices << QVector3D(maxX, minY, minZ);
    vertices << QVector3D(minX, maxY, maxZ);
    vertices << QVector3D(minX, maxY, minZ);
    vertices << QVector3D(minX, minY, maxZ);
    vertices << QVector3D(minX, minY, minZ);
    indices << 0 << 2 << 1 << 2 << 3 << 1;
    indices << 4 << 6 << 2 << 2 << 0 << 4;
    indices << 5 << 7 << 6 << 6 << 4 << 5;
    indices << 1 << 3 << 7 << 7 << 5 << 1;
    indices << 5 << 4 << 0 << 0 << 1 << 5;
    indices << 2 << 6 << 7 << 7 << 3 << 2;
    modelType = GL_TRIANGLES;

    cuboid->setPoints(vertices);
    cuboid->setIndicee(indices);
    cuboid->setType(modelType);
    cuboid->generateData();
    m_lyhModels.append(cuboid);
}

int ModelManager::getModelCount()
{
    return m_lyhModels.count();
}

LyhModel *ModelManager::getModel(int index)
{
    if(index >= m_lyhModels.count()){
        return nullptr;
    }
    return m_lyhModels[index];
}

QVector <float> ModelManager::getData()
{
    QVector <float> data;
    for(auto model: m_lyhModels){
        if(model->getIsShow()){
            data << model->getModelData();
        }
    }
    return data;
}

void ModelManager::init()
{
    addCuboid(2, 2, 2);
}

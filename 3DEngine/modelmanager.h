#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <QObject>
#include "lyhmodel.h"
class ModelManager : public QObject
{
    Q_OBJECT
public:
    explicit ModelManager(QObject *parent = nullptr);
    static ModelManager* getInstance();

    void addCuboid(float l, float w, float h);
    int getModelCount();
    LyhModel* getModel(int index);

    QVector <float> getData();
protected:
    void init();
private:
    QList <LyhModel*> m_lyhModels;
signals:

};

#endif // MODELMANAGER_H

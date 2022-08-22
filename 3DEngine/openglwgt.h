#ifndef OPENGLWGT_H
#define OPENGLWGT_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Compatibility>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QTimer>

#include "PublicFunctions/globaldefine.h"
#include "PublicFunctions/mouseandkeymanager.h"
#include "PublicFunctions/otherfunctions.h"
#include "cameramanager.h"
#include "openglconfigwgt.h"
#include "modelmanager.h"
#include "lightmanager.h"
class OpenglWgt: public QOpenGLWidget, public QOpenGLFunctions_4_3_Compatibility
{
    Q_OBJECT
public:
    explicit OpenglWgt(QWidget *parent = nullptr);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();             //opengl3固定函数

    void init();
    void connectShader(GlobalDefine::SHADER_MODE model);
    void connectSignalAndSlots();

    void renderModels();
    void setUniform();
    void setModelUniform(LyhModel* model);
    void setLight();
protected slots:
    void slotOnFlashTimerTimeout();
private:
    QOpenGLShaderProgram m_shaderProgram;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;

    QTimer *m_pFlashTimer = nullptr;

    bool m_bIsLight = false;
signals:

};

#endif // OPENGLWGT_H

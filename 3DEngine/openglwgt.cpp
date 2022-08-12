#include "openglwgt.h"

OpenglWgt::OpenglWgt(QWidget *parent)
{
    init();
}

void OpenglWgt::initializeGL()
{
    initializeOpenGLFunctions();
    connectShader(GlobalDefine::SHADER_MODE::DEFAULT);
    if(!m_shaderProgram.link()){
        OtherFunctions::giveWarningMessage(QStringLiteral("shader连接失败！！"));
    }
    m_shaderProgram.bind();
    m_shaderProgram.setUniformValue("projection", CameraManager::getInstance()->getCurCamera()->getPerspectiveMat(width(), height()));
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glEnable(GL_CULL_FACE);
}

void OpenglWgt::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    m_shaderProgram.bind();
    m_shaderProgram.setUniformValue("projection", CameraManager::getInstance()->getCurCamera()->getPerspectiveMat(width(), height()));
}

void OpenglWgt::paintGL()
{
    renderModels();

    QColor bgColor = OpenglConfigWgt::getInstance()->getBackGroundColor();
    glClearColor(((float)bgColor.red()) / 255.0, ((float)bgColor.green()) / 255.0, ((float)bgColor.blue()) / 255.0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shaderProgram.bind();
    QOpenGLVertexArrayObject::Binder vaoBind(&m_vao);
    setUniform();

    int l = ModelManager::getInstance()->getModelCount();
    int pointsCnt = 0;
    for(int i = 0; i < l; i++){
        LyhModel* model = ModelManager::getInstance()->getModel(i);
        if(!model->getIsShow()){
            continue;
        }
        setModelUniform(model);
        glDrawArrays(model->getModelType(), pointsCnt, model->getIndicesCount());
        pointsCnt += model->getIndicesCount();
    }
    m_shaderProgram.setUniformValue("model", QMatrix4x4());
}

void OpenglWgt::init()
{
    m_pFlashTimer = new QTimer(this);
    connectSignalAndSlots();
    m_pFlashTimer->start(10);
}

void OpenglWgt::connectShader(GlobalDefine::SHADER_MODE model)
{
    if(!m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex , ":/resc/Opengl/glsl/default.vert")){
        OtherFunctions::giveWarningMessage(QStringLiteral("添加vert着色器失败"));
    }
    if(!m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resc/Opengl/glsl/default.frag")){
        OtherFunctions::giveWarningMessage(QStringLiteral("添加frag着色器失败"));
    }
}

void OpenglWgt::connectSignalAndSlots()
{
    connect(m_pFlashTimer, &QTimer::timeout, this, &OpenglWgt::slotOnFlashTimerTimeout);
}

void OpenglWgt::renderModels()
{
    m_shaderProgram.bind();
    QVector <float> vertices = ModelManager::getInstance()->getData();
    QOpenGLVertexArrayObject::Binder vaoBind(&m_vao);
    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertices.data(), sizeof(float) * vertices.count());
    int attr = -1;

    attr = m_shaderProgram.attributeLocation("aPos");
    m_shaderProgram.setAttributeBuffer(attr, GL_FLOAT, 0, 3, sizeof(GLfloat) * 11);
    m_shaderProgram.enableAttributeArray(attr);

    if(m_bIsLight){
        attr = m_shaderProgram.attributeLocation("aNormal");
        m_shaderProgram.setAttributeBuffer(attr, GL_FLOAT, sizeof(GLfloat) * 3, 3, sizeof(GLfloat) * 11);
        m_shaderProgram.enableAttributeArray(attr);
    }

    attr = m_shaderProgram.attributeLocation("aFragColor");
    m_shaderProgram.setAttributeBuffer(attr, GL_FLOAT, sizeof(GLfloat) * 6, 3, sizeof(GLfloat) * 11);
    m_shaderProgram.enableAttributeArray(attr);
}

void OpenglWgt::setUniform()
{
    m_shaderProgram.setUniformValue("view", CameraManager::getInstance()->getCurCamera()->getViewMat());
}

void OpenglWgt::setModelUniform(LyhModel *model)
{
    QMatrix4x4 modelMat = model->getModelMat();
    m_shaderProgram.setUniformValue("model", modelMat);
    m_shaderProgram.setUniformValue("isUseLight", model->getIsLight());
    if(OpenglConfigWgt::getInstance()->getIsUseLight()){
        m_shaderProgram.setUniformValue("materialAmbient  ", model->getMaterialAmbient());
        m_shaderProgram.setUniformValue("materialDiffuse  ", model->getMaterialDiffuse());
        m_shaderProgram.setUniformValue("materialSpecluar ", model->getMaterialSpecluar());
        m_shaderProgram.setUniformValue("materialShininess", model->getMaterialShininess());
    }
}

void OpenglWgt::setLight()
{

}


void OpenglWgt::slotOnFlashTimerTimeout()
{
    if(MouseAndKeyManager::getInstance()->getIsKeyPressed(Qt::Key_W)){
        CameraManager::getInstance()->getCurCamera()->moveFront();
    }
    if(MouseAndKeyManager::getInstance()->getIsKeyPressed(Qt::Key_S)){
        CameraManager::getInstance()->getCurCamera()->moveBack();
    }
    if(MouseAndKeyManager::getInstance()->getIsKeyPressed(Qt::Key_A)){
        CameraManager::getInstance()->getCurCamera()->moveLeft();
    }
    if(MouseAndKeyManager::getInstance()->getIsKeyPressed(Qt::Key_D)){
        CameraManager::getInstance()->getCurCamera()->moveRight();
    }
    if(MouseAndKeyManager::getInstance()->getIsKeyPressed(Qt::Key_Q)){
        CameraManager::getInstance()->getCurCamera()->partialHeadLeft();
    }
    if(MouseAndKeyManager::getInstance()->getIsKeyPressed(Qt::Key_E)){
        CameraManager::getInstance()->getCurCamera()->partialHeadRight();
    }
    if(MouseAndKeyManager::getInstance()->getIsKeyPressed(Qt::Key_Control)){
        CameraManager::getInstance()->getCurCamera()->moveDown();
    }
    if(MouseAndKeyManager::getInstance()->getIsKeyPressed(Qt::Key_Space)){
        CameraManager::getInstance()->getCurCamera()->moveUp();
    }

    update();
}

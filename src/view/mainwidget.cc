#include "mainwidget.h"

MainWidget::~MainWidget()
{
    makeCurrent();
    delete geometries;
    doneCurrent();
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
    initShaders();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    geometries = new GeometryEngine;
    timer.start(5, this);
}

void MainWidget::initShaders()
{
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();
    if (!program.link())
        close();
    if (!program.bind())
        close();
}

void MainWidget::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.1, zFar = 1000.0, fov = 45.0;
    projection.setToIdentity();
    if (this->project_ortho) {
        QRectF orthoRectangle;
        orthoRectangle.setHeight(h);
        orthoRectangle.setWidth(w);
        projection.ortho(-aspect, aspect, -1.0, 1.0, zNear, zFar);
    } else {
        projection.perspective(fov, aspect, zNear, zFar);
    }
}

void MainWidget::paintGL()
{
    initColors();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
//    matrix.rotate(rotation);

    program.setUniformValue("mvp_matrix", projection * matrix);

    if (geometries->filepath != "") {
        if (flag_dotted) {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1, 0x00FF);
            geometries->drawCubeGeometry(&program);
            glDisable(GL_LINE_STIPPLE);
        } else {
            geometries->drawCubeGeometry(&program);
        }
        update();
    }

    if(geometries->flag_dot_vert) {
        initColorsVer();
        geometries->drawVertixGeometry(&program);
        update();
    }
}

void MainWidget::updating()
{
    update();
}

void MainWidget::initColors()
{
    glClearColor(color_back->redF(), color_back->greenF(), color_back->blueF(), 0);

    int vertexLocation = program.attributeLocation("vertex");
    int colorLocation = program.uniformLocation("color");

    program.enableAttributeArray(vertexLocation);
    program.setUniformValue(colorLocation, *color);
    program.disableAttributeArray(vertexLocation);
}

void MainWidget::initColorsVer()
{
    glClearColor(color_ver->redF(), color_ver->greenF(), color_ver->blueF(), 0);

    int vertexLocation = program.attributeLocation("vertex");
    int colorLocation = program.uniformLocation("color");

    program.enableAttributeArray(vertexLocation);
    program.setUniformValue(colorLocation, *color_ver);
    program.disableAttributeArray(vertexLocation);
}

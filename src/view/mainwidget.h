#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
// #include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
// #include <QMouseEvent>
#include <cmath>

#include "geometryengine.h"

class GeometryEngine;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    using QOpenGLWidget::QOpenGLWidget;
    ~MainWidget();
    GeometryEngine *geometries = nullptr;
    QOpenGLShaderProgram program;
    QColor *color = new QColor(0, 0, 0, 0);
    QColor *color_back = new QColor(214, 214, 214, 255);
    QColor *color_ver = new QColor(190, 30, 20, 255);
    void updating();
    void initColors();
    void initColorsVer();
    void resizeGL(int w, int h) override;
    void initializeGL() override;
    void SetFlagDotted(bool x) { flag_dotted = x; }
    void SetFlagOrtho(bool x) { project_ortho = x; }
    bool GetFlagDotted() { return flag_dotted; }
    bool GetFlagOrtho() { return project_ortho; }

protected:
    void paintGL() override;
    void initShaders();

private:
    QBasicTimer timer;
    QOpenGLTexture *texture = nullptr;
    QMatrix4x4 projection;
    bool flag_dotted = 0;
    bool project_ortho = 0;
};

#endif // MAINWIDGET_H

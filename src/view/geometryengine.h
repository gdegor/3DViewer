#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector2D>
#include <QVector3D>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QVector>
#include <QColor>
#include <QTimer>
#include <QQuaternion>

#include "../controller/controller.h"

class GeometryEngine : protected QOpenGLFunctions
{
public:
    GeometryEngine();
    virtual ~GeometryEngine();

    void drawCubeGeometry(QOpenGLShaderProgram *program);
    void drawVertixGeometry(QOpenGLShaderProgram *program);

    QString filepath = NULL;
    void initCubeGeometry();
    void initVertices();
    void initFacets();

    int vertex_label, facets_label;
    double line_width = 1.0;
    double dot_size = 1.0;
    bool flag_dot_vert = 0;
    bool flag_dot_round = 0;

    s21::Controller control;

private:

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    void DrawFrom(QOpenGLShaderProgram *program);

    GLsizei lines;

};

#endif // GEOMETRYENGINE_H

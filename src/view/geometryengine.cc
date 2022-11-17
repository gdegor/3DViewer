#include "geometryengine.h"

struct VertexData
{
    QVector3D position;
};

GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    arrayBuf.create();
    indexBuf.create();

    initCubeGeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::initCubeGeometry()
{
    QFile inputFile(filepath);
    if (!inputFile.exists()) {
        return;
    } else {
        inputFile.open(QIODevice::ReadOnly);
        int fd = inputFile.handle();
        FILE* fp = fdopen(fd, "rb");
        
		control.OpenModel(fp);

        vertex_label = control.GetVertex().size() / 3;
        facets_label = control.GetFacets().size() / 4;

        inputFile.close();

        initVertices();
        initFacets();
    }
}

void GeometryEngine::initFacets()
{
	QVector<GLuint> indices;
    std::vector<int> facets = control.GetFacets();
    for (unsigned i = 0; i < facets.size(); i++) {
        indices.push_back(facets[i]);
    }

    lines = indices.length();

    indexBuf.bind();
    indexBuf.allocate(indices.data(), sizeof(GLuint)*indices.length());
}

void GeometryEngine::initVertices()
{
    QVector<VertexData> vertices;
    std::vector<double> verts = control.GetVertex();
    for (unsigned int i = 0, j = 0; i < verts.size(); i+=3, j++) {
        VertexData tmp_vert = {QVector3D(verts[i], verts[i+1], verts[i+2])};
        vertices.push_back(tmp_vert);
    }

    arrayBuf.bind();
    arrayBuf.allocate(vertices.data(), sizeof(VertexData) * vertices.length());
}

void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    if (filepath.isEmpty()) {
        return;
    } else {
        glLineWidth(line_width);

        initVertices();
        DrawFrom(program);

        glDrawElements(GL_LINES, lines, GL_UNSIGNED_INT, nullptr);
    }
}

void GeometryEngine::drawVertixGeometry(QOpenGLShaderProgram *program)
{
    if (filepath.isEmpty()) {
        return;
    } else {
        initVertices();

        if (flag_dot_round) {
            glDisable(GL_POINT_SIZE);
            glEnable(GL_POINT_SMOOTH);
        } else {
            glDisable(GL_POINT_SMOOTH);
            glEnable(GL_POINT_SIZE);
        }

        glPointSize(dot_size);
        DrawFrom(program);

        glDrawElements(GL_POINTS, lines, GL_UNSIGNED_INT, nullptr);
    }
}

void GeometryEngine::DrawFrom(QOpenGLShaderProgram *program) {
    arrayBuf.bind();
    indexBuf.bind();
    quintptr offset = 0;

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));
}

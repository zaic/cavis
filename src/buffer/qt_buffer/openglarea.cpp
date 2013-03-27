#include "openglarea.h"

OpenGLArea::OpenGLArea(QWidget *_parent) :
    QGLWidget(_parent),
    xrot(-521),
    yrot(1757),
    zrot(-586)
{
}

void OpenGLArea::initializeGL()
{
    qglClearColor(Qt::white);
    // ?
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
}

void OpenGLArea::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#else
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void OpenGLArea::paintGL()
{
    qDebug() << "[buffer/opengl] TODO";
    // TODO
}

void OpenGLArea::mouseMoveEvent(QMouseEvent *ev)
{
    int dx = ev->x() - last_pos.x();
    int dy = ev->y() - last_pos.y();

    if (ev->buttons() & Qt::LeftButton) {
        xrot += dy;
        yrot += dx;
    } else if (ev->buttons() & Qt::RightButton) {
        xrot += dy;
        zrot += dx;
    }

    last_pos = ev->pos();
    update();
}

void OpenGLArea::mousePressEvent(QMouseEvent *ev)
{
    last_pos = ev->pos();
}

void OpenGLArea::drawDots(int _size_x, int _size_y, float *_data)
{
    size_x = _size_x;
    size_y = _size_y;
    data   = _data;
    update();
}

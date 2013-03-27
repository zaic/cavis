#include "openglarea.h"

OpenGLArea::OpenGLArea(QWidget *parent) :
    QGLWidget(parent),
    buffer_image(NULL),
    xrot(-521),
    yrot(1757),
    zrot(-586)
{
}

void OpenGLArea::paintEvent(QPaintEvent *ev)
{
    if(!buffer_image) {
        WindowEvent::get()->doRequireRepaint();
        return ;
    }
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawRect(0, 0, width() - 1, height() - 1);
    if(buffer_image) {
        painter.drawImage(this->rect(), *(this->buffer_image));
    }
    delete buffer_image;
    buffer_image = NULL;
}

void OpenGLArea::drawImage(QImage *image)
{
    buffer_image = image;
    this->update();
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

void OpenGLArea::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - last_pos.x();
    int dy = event->y() - last_pos.y();

    if (event->buttons() & Qt::LeftButton) {
        xrot += dy;
        yrot += dx;
    } else if (event->buttons() & Qt::RightButton) {
        xrot += dy;
        zrot += dx;
    }

    last_pos = event->pos();
    update();
}

void OpenGLArea::mousePressEvent(QMouseEvent *event)
{
    last_pos = event->pos();
}

#include "openglarea.h"

OpenGLArea::OpenGLArea(QWidget *_parent) :
    QGLWidget(_parent),
    xrot(521),
    yrot(-1757),
    zrot(586),
    scale(0.01f)
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
    //glViewport((width - side) / 2, (height - side) / 2, side, side);
    glViewport(0, 0, width, height);

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
    qDebug() << "[buffer/opengl] begin";
    if(data == NULL) {
        qDebug() << "[buffer/opengl] nothind to draw, exiting";
        return ;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(0.1f * xrot, 1.0, 0.0, 0.0);
    glRotatef(0.1f * yrot, 0.0, 1.0, 0.0);
    glRotatef(0.1f * zrot, 0.0, 0.0, 1.0);

    glLineWidth(1.0);
    glColor3f(0.0, 0.0, 0.0);

    qDebug() << "[buffer/opengl] scale =" << scale;
    for(int i = 0; i < size_y - 1; i++)
        for(int j = 0;j < size_x - 1; j++) {
            const int id = i * size_x + j;
            float cx = (j - size_x / 2) * scale;
            float cy = (i - size_y / 2) * scale;

#if 1
            glColor3f(0.3, 0.3, 0.3);
            glBegin(GL_LINES);

            glVertex3f(cx, cy, data[id]);
            glVertex3f(cx +scale, cy, data[id + 1]);

            glVertex3f(cx +scale, cy, data[id + 1]);
            glVertex3f(cx +scale, cy +scale, data[id + size_x + 1]);

            glVertex3f(cx +scale, cy +scale, data[id + size_x + 1]);
            glVertex3f(cx, cy +scale, data[id + size_x]);

            glVertex3f(cx, cy +scale, data[id + size_x]);
            glVertex3f(cx, cy, data[id]);

            glEnd();
#endif
#if 0
            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_POLYGON);

            glVertex3f(cx, cy, data[id]);
            glVertex3f(cx +scale, cy, data[id + 1]);
            glVertex3f(cx +scale, cy +scale, data[id + 1]);
            glVertex3f(cx, cy +scale, data[id + size_x]);
            glVertex3f(cx, cy, data[id]);

            glEnd();

            glColor3f(0.0, 1.0, 0.0);
            glBegin(GL_POLYGON);

            glVertex3f(cx, cy, data[id]);
            glVertex3f(cx, cy +scale, data[id + size_x]);
            glVertex3f(cx +scale, cy +scale, data[id + size_x + 1]);
            glVertex3f(cx +scale, cy, data[id + 1]);
            glVertex3f(cx, cy, data[id]);

            glEnd();

#endif

        }
}

void OpenGLArea::mouseMoveEvent(QMouseEvent *ev)
{
    qDebug() << "!!!";
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

void OpenGLArea::wheelEvent(QWheelEvent *ev)
{
    QPoint num_pixels  = ev->pixelDelta();
    QPoint num_degrees = ev->angleDelta() / 8;

    if (!num_pixels.isNull()) {
        //qDebug() << "[buffer/opengl]" << num_pixels;
        if(num_pixels.y() > 0)
            scale *= num_pixels.y();
        else
            scale /= num_pixels.y();
    } else if (!num_degrees.isNull()) {
        qDebug() << "[buffer/opengl] scroll" << num_degrees;
        if(num_degrees.y() > 0)
            scale *= abs(num_degrees.y() / 10.0);
        else
            scale /= abs(num_degrees.y() / 10.0);
        qDebug() << scale;
    }

    WindowEvent::get()->doRequireRepaint();
}

void OpenGLArea::drawDots(int _size_x, int _size_y, float *_data)
{
    size_x = _size_x;
    size_y = _size_y;
    data   = _data;
    update();
}

#pragma once

#include <QtCore>
#include <QtOpenGL>
#include "windowevent.h"

class OpenGLArea : public QGLWidget
{
    Q_OBJECT

    // RendererAreay compatibility
    QImage *buffer_image;

    // rotation
    QPoint last_pos;
    int xrot, yrot, zrot;

protected:
    void paintEvent(QPaintEvent *ev);

public:
    explicit OpenGLArea(QWidget *parent = 0);

    /*
     *  Compatibility with simple RendererArea
     */
    void drawImage(QImage *image);

    /*
     *  OpenGL support
     */
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    
signals:
    
public slots:
    
};

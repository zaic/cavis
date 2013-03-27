#pragma once

#include <QtCore>
#include <QtOpenGL>
#include "windowevent.h"

class OpenGLArea : public QGLWidget
{
    Q_OBJECT

    // rotation
    QPoint last_pos;
    int xrot, yrot, zrot;

    // data
    int size_x, size_y;
    float *data;

public:
    explicit OpenGLArea(QWidget *_parent = 0);

    /*
     *  Renderer functions
     */
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

    /*
     *  Rotation functions
     */
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);

    /*
     *  Temporary (?) function to set data
     */
    void drawDots(int _size_x, int _size_y, float *_data);
    
signals:
    
public slots:
    
};

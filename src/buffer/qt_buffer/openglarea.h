#pragma once

#include <QtCore>
#include <QtOpenGL>
#include <cmath>
#include "windowevent.h"

using std::abs;

class OpenGLArea : public QGLWidget
{
    Q_OBJECT

    // view
    QPoint last_pos;
    int xrot, yrot, zrot;
    float scale;

    // data
    int size_x, size_y;
    float *data;

public:
    explicit OpenGLArea(QWidget *_parent = 0);

    /*
     *  Renderer functions
     */
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    /*
     *  View functions
     */
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void wheelEvent(QWheelEvent *ev);

    /*
     *  Temporary (?) function to set data
     */
    void drawDots(int _size_x, int _size_y, float *_data);
    
signals:
    
public slots:
    
};

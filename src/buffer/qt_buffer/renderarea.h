#pragma once

#include <QtWidgets>
#include "../../windowevent.h"

class RenderArea : public QWidget
{
    Q_OBJECT

    QImage *buffer_image;

protected:
    void paintEvent(QPaintEvent* );
    void resizeEvent(QResizeEvent *);

public:
    explicit RenderArea(QWidget *_parent = 0);
    void drawImage(QImage *image);

signals:


public slots:

};

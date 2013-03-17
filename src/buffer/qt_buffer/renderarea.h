#pragma once

#include <QWidget>
#include <QPainter>
#include "../../windowevent.h"

class RenderArea : public QWidget
{
    Q_OBJECT

    QImage *buffer_image;

protected:
    void paintEvent(QPaintEvent* );

public:
    explicit RenderArea(QWidget *_parent = 0);
    void drawImage(QImage *image);

signals:


public slots:

};
